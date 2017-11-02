#pragma once

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
  int randIndex = roundToInt(floor(GameHelpers::getRandom() * 12));
  state.moles[randIndex].state = Mole::State::Showing;
}

void moleHit(Mole& m, GameState& state) {
    state.combo += 1;
    state.score += 100 * state.combo;
    m.state = Mole::State::Hidden;
}

void moleMiss(Mole& m, GameState& state) {
    state.combo = 0;
	m.state = Mole::State::Hidden; // Or miss?
    // Maybe mark the mole as being missed or something.
}
