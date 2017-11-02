/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include <algorithm>
#include <map>

using namespace std;

#include "GameHelpers.h"

#include "DataModel.h"
#include "MoleHelpers.h"

#include "Game.h"
#include "GameUI.h"

// Main component
class MainContentComponent   : public AnimatedAppComponent {
public:
  //==============================================================================
  MainContentComponent() : game(), gameUI(game.getGameState()) {
    addAndMakeVisible(gameUI);
    setSize (WINDOW_WIDTH, WINDOW_HEIGHT);
    setFramesPerSecond (60);
  }

  ~MainContentComponent() {}

  void update() override {
    game.update(getMillisecondsSinceLastUpdate() / 1000.0f);
  }

  void paint(Graphics& g) override { ignoreUnused(g); }

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
