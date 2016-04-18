#ifndef _GAMEOBJECT_H__
#define _GAMEOBJECT_H__
#include <hge.h>

class GameObject
{
	public:
		virtual ~GameObject () {}
		virtual int update () = 0;
		virtual void render () = 0;
		

		friend class HgeWrapper;
	protected:
		static HGE *hge;
};

#endif // _GAMEOBJECT_H__