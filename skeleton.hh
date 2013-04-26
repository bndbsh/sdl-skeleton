#ifndef _SKELETON_HH_
#define _SKELETON_HH_

#include "gfx/sdlwidget.hh"

class Skeleton {
private:
	SDLWidget* widget;
public:
	Skeleton(int& argc, char** argv);
	~Skeleton();

	void resize(int width, int height);

	void update(double frameTime);

	void load();

	int start();
};

#endif
