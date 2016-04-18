#ifndef _HGEWRAPPER_H__
#define _HGEWRAPPER_H__

// Includes
#include "GameObject.h"
#include <hge.h>
#include <string>

// Macro for main
#define main() WINAPI WinMain ( HINSTANCE, HINSTANCE, LPSTR, int )

class HgeWrapper
{
	public:
		// Will initialize hge and return true if successful
		static bool initiate ( std::string title = "HgeApplication", int width = 800, int height = 600, int fps = 60 );

		// Start hge with an object derived from GameObject
		static void startHge ( GameObject *_game );

	private:
		static bool update ();
		static bool render ();
		static int (GameObject::*updateFunc)();
		static void (GameObject::*renderFunc)();
		static GameObject *game;
		static HGE *hge;
};

#endif // _HGEWRAPPER_H__