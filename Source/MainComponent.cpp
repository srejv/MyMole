/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "GameHelpers.h"
#include <algorithm>
#include <map>
#include <deque>

using namespace std;

struct Mole {
    // Internal Type
    enum class State : int { Hidden = 0, Showing = 1, Animating = 2};
    
    // Data
    Rectangle<float> body{0, 0, 0, 0};
    KeyPress keyHit{'q'};
    State state = State::Hidden;
    bool isUp = false;
};

struct GameState {
    // Game Objects
    vector<Mole> moles;
    
    // Data
    int score = 0;
    int combo = 0;
    float timeSpent = 0.0f;
    
    KeyPress restartGame{KeyPress::F5Key};
};


void resetGameState(GameState& state) {
    // Reload the moles
    state.moles.clear();
    
    // Yes i wrote the coords by hand because yeah... KeyPress...?
    // Y U NO LOAD FROM FILE?
    // ... y?
    state.moles.push_back({ {0,  0, 64, 64}, KeyPress('q') });
    state.moles.push_back({ {72, 0, 64, 64}, KeyPress('w') });
    state.moles.push_back({ {144,0, 64, 64}, KeyPress('e') });
    state.moles.push_back({ {216,0, 64, 64}, KeyPress('r') });
    
    state.moles.push_back({ {0,  72, 64, 64}, KeyPress('a') });
    state.moles.push_back({ {72, 72, 64, 64}, KeyPress('s') });
    state.moles.push_back({ {144,72, 64, 64}, KeyPress('d') });
    state.moles.push_back({ {216,72, 64, 64}, KeyPress('f') });
    
    state.moles.push_back({ {0,  144, 64, 64}, KeyPress('z') });
    state.moles.push_back({ {72, 144, 64, 64}, KeyPress('x') });
    state.moles.push_back({ {144,144, 64, 64}, KeyPress('c') });
    state.moles.push_back({ {216,144, 64, 64}, KeyPress('v') });
    
    // Reset game data
    state.score = 0;
    state.combo = 0;
    state.timeSpent = 0.0f;
}

bool areAllMolesHidden(GameState& state) {
    return all_of(state.moles.begin(), state.moles.end(), [](Mole& m) {
        return m.state == Mole::State::Hidden;
    });
}

void makeMoleAppear(GameState& state) {
    int randIndex = GameHelpers::getRandom() * 12;
    state.moles[randIndex].state = Mole::State::Showing;
}

void moleHit(Mole& m, GameState& state) {
    state.combo += 1;
    state.score += 100 * state.combo;
    m.state = Mole::State::Hidden;
}

void moleMiss(Mole& mole, GameState& state) {
    state.combo = 0;
    // Maybe mark the mole as being missed or something.
}

class Game
{
public:
    Game() : state() {
        resetGameState(state);
    }

    void update(float dt) {
        // What's up, moles?
        for(auto& m : state.moles) {
            if(GameHelpers::isKeyDown(m.keyHit)) {
                if(pressedMap[m.keyHit.getKeyCode()]) {
                    continue;
                }
                
                if(m.state == Mole::State::Hidden) {
                    moleMiss(m, state);
                } else {
                    moleHit(m, state);
                }
                
                // Gotta set this after or else there will be: 
                //   _no input_ or an _input loop_
                //  which makes it impossible to play
                pressedMap[m.keyHit.getKeyCode()] = true;
            } else {
                pressedMap[m.keyHit.getKeyCode()] = false;
            }
        }
        
        // Hm. No moles showing?
        bool noMoles = areAllMolesHidden(state);
        if(noMoles) {
            makeMoleAppear(state);
        }
        
        // Increase time spent
        state.timeSpent += dt;
        
        // Restart game
        if(GameHelpers::isKeyDown(state.restartGame)) {
            resetGameState(state);
        }
    }
    
    GameState& getGameState() {
        return state;
    }
    
private:

    GameState state;
    map<int, bool> pressedMap;
};


class GameUI : public Component
{
public:
	GameUI(GameState& gameState) : gameState(gameState) {}
	
	void paint(Graphics& g) override {
	    // Paint the game first. 
	    paintGame(g);
	    
	    // Paint UI after for it to get on top, just like a real canvas. 
	    paintHUD(g);
	    
	}
	
	void paintGame(Graphics& g) {
        // Clear. 
        g.fillAll (Colour(30,30,30));
        g.setColour(Colour(240,240,240));
        
        // Weird calculation in this one. Manual. 
        auto middle(getLocalBounds().withSizeKeepingCentre(64*4 + 8*3, 64*3 + 8*2));
        
        // Center drawing area.
        g.saveState();
        g.addTransform(AffineTransform::translation(middle.getPosition()));
        
        // Draw ze moles
        for(auto& m : gameState.moles) {
            if(m.state == Mole::State::Hidden) {
                g.setColour(Colour(40,40,40));
            }
            if(m.state == Mole::State::Showing) {
                g.setColour(Colour(200,30,30));
            }
            if(m.state == Mole::State::Animating) {
                g.setColour(Colour(240,240,240));
            }
            g.fillRect(m.body);
        }
        g.restoreState();
    }
    
    void paintHUD(Graphics& g) {
        // Data we want to draw
        String strTimeSpent(roundToInt(gameState.timeSpent));
	    String strScore(gameState.score);
		String strCombo(gameState.combo);
		
		// Setup HUD backgroup
		auto row(getLocalBounds().removeFromTop(32));
		g.setColour(Colour(30,30,30));
		g.fillRect(row); 
        
		// Draw some information text
		g.setColour(Colour(240, 240, 240));
		g.drawText(strTimeSpent, row.removeFromLeft(200).withTrimmedLeft(8), Justification::centredLeft);
		g.drawText(strCombo, row.removeFromRight(200).withTrimmedRight(8), Justification::centredRight);
		g.drawText(strScore, row, Justification::centred);
    }

private:
	GameState& gameState;
};



// Main component
class MainContentComponent   : public AnimatedAppComponent
{
public:
    //==============================================================================
    MainContentComponent() : game(), gameUI(game.getGameState()) {
        addAndMakeVisible(gameUI);
        setSize (WINDOW_WIDTH, WINDOW_HEIGHT);
        setFramesPerSecond (60);
    }

    ~MainContentComponent() {}

    void update() override
    {
        float dt = 1.0f/60.0f;
        // TODO: There should be a get time since last update for better dt values
        game.update(dt);
    }

    void paint (Graphics& g) override {}

    void resized() override {
        gameUI.setBounds(getLocalBounds());
    }


private:
    //==============================================================================
    Game game;
    GameUI gameUI;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()    { return new MainContentComponent(); }
