#include "Controls.h"

Controls::Controls() {}

Controls::~Controls() {}

/*
Wrapper function for a "pressed" key (i.e. the key is held down)
*/
bool Controls::press(const int &key) const
{
	return Component::getHge()->Input_GetKeyState(key);
}

/*
Adapter for "key down". User has downed a key in prev. frame
*/
bool Controls::down(const int &key) const
{
	return Component::getHge()->Input_KeyDown(key);
}

/*
Adapter for "key up". User has released a key in prev. frame.
*/
bool Controls::up(const int &key) const
{
	return Component::getHge()->Input_KeyUp(key);
}

/*
Any key combination is released.
*/
bool Controls::release(const int& pressedKey, const int& downedKey) const
{
	return !combined(pressedKey, downedKey);
}

/*
Alias for up (key)
*/
bool Controls::release(const int& key) const
{
	return up(key);
}

/*
Enables key combinations, or shortcuts. "CTRL + A"
*/
bool Controls::shortcut(const char& pressedKey, const char& downKey) const
{
	return (press(pressedKey) && down(downKey));
}

/*
Enables triple key shortcuts. "CTRL + A + B"
*/
bool Controls::triple(const char& pressedKey, const char& downKey1, const char& downKey2) const
{
	return (shortcut(pressedKey, downKey1) && press(downKey2));
}

/*
Either combination of a shortcut is accepted. Both "CTRL + A" and "A + CTRL" is valid
*/
bool Controls::combined(const int& pressedKey, const int& downKey) const
{
	return (shortcut(pressedKey, downKey) || shortcut(downKey, pressedKey));
}