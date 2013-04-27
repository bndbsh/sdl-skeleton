#ifndef _SKELETON_HH_
#define _SKELETON_HH_

#include "gfx/sdlwidget.hh"

class Skeleton {
private:
	SDLWidget* widget;
public:
	Skeleton();
	~Skeleton();

	void resize(int width, int height);

	void update(double frameTime);

	int start();
};

#endif
