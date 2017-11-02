#pragma once

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
