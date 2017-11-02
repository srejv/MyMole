#pragma once


class GameUI : public Component {
public:
  GameUI(GameState& gameState) : gameState(gameState) {}

  void paint(Graphics& g) override {
    paintBackground(g);
    paintGame(g);
    paintHUD(g);
  }

  void paintBackground(Graphics& g) {
    // Clear.
    g.fillAll (Colour(30,30,30));
    g.setColour(Colour(240,240,240));
  }

  void paintGame(Graphics& g) {
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
