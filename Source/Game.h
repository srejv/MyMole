#pragma once

class Game {
public:
  Game() : state() {
    resetGameState(state);
  }

  void update(float dt) {
    updateMoles();
    checkNoMoles();
    updateTimers(dt);
    checkRestartGame();
  }

  GameState& getGameState() {
      return state;
  }

private:
  void updateMoles() {
    // What's up, moles?
    for(auto& m : state.moles) {
      updateMole(m);
    }
  }

  void updateMole(Mole& m) {
    if(GameHelpers::isKeyDown(m.keyHit)) {
      if(pressedMap[m.keyHit.getKeyCode()]) {
        return;
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

  void checkNoMoles() {
    // Hm. No moles showing?
    bool noMoles = areAllMolesHidden(state);
    if(noMoles) {
      makeMoleAppear(state);
    }
  }

  void updateTimers(float dt) {
    // Increase time spent
    state.timeSpent += dt;
  }

  void checkRestartGame() {
    // Restart game
    if(GameHelpers::isKeyDown(state.restartGame)) {
      resetGameState(state);
    }
  }

//=======================================
  GameState state;
  map<int, bool> pressedMap;
};
