#ifndef _SILVER_CORE_SDLWIDGET_HH_
#define _SILVER_CORE_SDLWIDGET_HH_

#include <string>

#include <SDL.h>

class Skeleton;

class SDLWidget {
public:
	SDLWidget(bool border, Skeleton* skel);
	virtual ~SDLWidget();
	void setSize(int width, int height);
	
	void warpCursor(int x = -1, int y = -1);
	
	void getCursor(int& x, int& y);
	
	void showCursor(int show);
	
	void startLoop();
	
	void setPosition(int x, int y);
	
	void getPosition(int& x, int& y);
	
	bool done;
	
	double fps;
private:
	Skeleton* skeleton;
	int width;
	int height;
	SDL_Window* window;
	SDL_GLContext context;
	
	double lastFrameTime;
	double frameTime;
	double timeCounter;
	int frameCounter;
	int timeToKill;
	long lastLoop;
	long startTime;
	long endTime;
	long accumulator;
	long accumThreshold;
	static const unsigned int FPS;
	static const unsigned int FrameTime;
	
	void update();
};


#endif
