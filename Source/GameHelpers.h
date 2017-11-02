/*
  ==============================================================================

    GameHelpers.h
    Created: 30 Oct 2017 8:57:16pm
    Author:  srejv

  ==============================================================================
*/

#pragma once

// Yeah.... This is not bery boog
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 1024

#define WINDOW_HEIGHTF 600.0f
#define WINDOW_WIDTHF 1024.0f

namespace GameHelpers
{
	// Clamp a rectangle to window vertically
	void clampVertical(Rectangle<float>& r) { // ( Improvement: sending in a rect to clamp to )
		float oldY = r.getY();
		r = r.withY(jlimit<float>(0.0f, WINDOW_HEIGHTF - r.getHeight(), oldY));
	}

	// Clamp a rectangle to window horizontally ( Improvement: sending in a rect to clamp to )
	void clampHorizontal(Rectangle<float>& r) {
		float oldX = r.getX();
		r = r.withX(jlimit<float>(0.0f, WINDOW_WIDTHF - r.getWidth(), oldX));
	}

	// Move with a vector. Kinda. Added it for completeness?
	void move(Rectangle<float>& r, const Point<float>& amount) {
	    r = r.withX(r.getX() + amount.getX())
	         .withY(r.getY() + amount.getY());
	}

	// Move a rectangle horizontally
	void moveHorizontal(Rectangle<float>& r, const float amount) {
		r = r.withX(r.getX() + amount);
	}

	// Move a rectangle vertically
	void moveVertical(Rectangle<float>& r, const float amount) {
		r = r.withY(r.getY() + amount);
	}

	// When a rectangle is just touching outside the screen vertically
	bool isOutsideVertically(Rectangle<float>& r) {
		if (r.getY() < 0) return true;
		if (r.getY() >= (WINDOW_HEIGHTF - r.getHeight())) return true;

		return false;
	}

	// When a rectangle IS wholly outside the screen horizontally
	bool isOutsideHorizontally(Rectangle<float> &r) {
		if (r.getX() < -r.getWidth()) return true;
		if (r.getX() >= (WINDOW_WIDTHF + r.getWidth())) return true;

		return false;
	}

	// Is a keypress active
	bool isKeyDown(const KeyPress& k) {
		return KeyPress::isKeyCurrentlyDown(k.getKeyCode());
	}

	// Get a "random" number between 0.0f and 1.0f inclusive
	float getRandom() {
		return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	}

	// Get a "Random" colour
	Colour getRandomColour() {
		return Colour::fromHSV(getRandom(), getRandom() * 0.2f + 0.80f, getRandom() * 0.1f + 0.9f, 1.0f);
	}
};
