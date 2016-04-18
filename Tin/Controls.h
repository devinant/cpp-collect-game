#ifndef CONTROLS_H
#define CONTROLS_H

#include <hge.h>
#include "Component.h"

/*
Wrapper class for Get_Input* functions.
*/
class Controls : public Component
{
	public:
		Controls();
		virtual ~Controls();
		
		// Different key events.
		bool press(const int &key) const;
		bool down(const int &key) const;
		bool up(const int &key) const;

		bool release(const int& pressedKey, const int& downKey) const;
		bool release(const int& pressedKey) const;

		// Combinations and shortcuts (CTRL + A, CTRL + A + B, etc.)
		bool shortcut(const char& pressedKey, const char& downKey) const;
		bool triple(const char& pressedKey, const char& downKey1, const char& downKey2) const;
		bool combined(const int& pressedKey, const int& downKey) const;

		void update()
		{
		}
};
#endif