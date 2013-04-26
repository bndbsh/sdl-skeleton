
#include "sdlwidget.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "skeleton.hh"

#ifdef UNIX
#include <sys/time.h>
#include <time.h>
#endif

#include <iostream>

const unsigned int SDLWidget::FPS = 60;
const unsigned int SDLWidget::FrameTime = (1.0/FPS)*1000000000;

SDLWidget::SDLWidget(bool b, Skeleton* skel) : done(false), fps(0), lastFrameTime(0), frameTime(0), timeCounter(0), frameCounter(0), 
                               timeToKill(0), lastLoop(0), startTime(0), endTime(0), accumulator(0), accumThreshold(0) {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	if (!b) flags |= SDL_WINDOW_BORDERLESS;
	window = SDL_CreateWindow("dat xflight", 0, 0, 1600, 900, flags);
	context = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);
}

SDLWidget::~SDLWidget() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

void SDLWidget::setSize(int width, int height) {
	SDL_SetWindowSize(window, width, height);
	skeleton->resize(width, height);
	this->width = width;
	this->height = height;
}

void SDLWidget::setPosition(int x, int y) {
	SDL_SetWindowPosition(window, x, y);
}

void SDLWidget::getPosition(int& x, int& y) {
	SDL_GetWindowPosition(window, &x, &y);
}

void SDLWidget::warpCursor(int x, int y) {
	if (x == -1) {
		x = width / 2;
		y = height / 2;
	}
	SDL_WarpMouseInWindow(window, x, height-y);
}

void SDLWidget::getCursor(int& x, int& y) {
	SDL_GetMouseState(&x, &y);
	y = height - y;
}

void SDLWidget::showCursor(int show) {
	SDL_ShowCursor(show);
}

void SDLWidget::update() {
	skeleton->update(frameTime);
	SDL_GL_SwapWindow(window);
}

struct timespec tsSubtract (struct timespec time1, struct timespec time2) {
	struct timespec result ;
	if ((time1.tv_sec < time2.tv_sec) || ((time1.tv_sec == time2.tv_sec) && (time1.tv_nsec <= time2.tv_nsec))) {
		result.tv_sec = result.tv_nsec = 0;
	} else {
		result.tv_sec = time1.tv_sec - time2.tv_sec ;
		if (time1.tv_nsec < time2.tv_nsec) {
			result.tv_nsec = time1.tv_nsec + 1000000000L - time2.tv_nsec;
			result.tv_sec--;
		} else {
			result.tv_nsec = time1.tv_nsec - time2.tv_nsec;
		}
	}
	return result;
}

void SDLWidget::startLoop() {
	while (!done) {
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					done = true;
					break;
				default:
					break;
			}
		}
		accumThreshold = 0.032*1000000000;
		if (timeToKill <= 0) {
			struct timespec ts_start;
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_start);
			startTime = (ts_start.tv_sec * 1000000000) + ts_start.tv_nsec;
			update();
			if (done) break;
			struct timespec ts_end;
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_end);
			endTime = (ts_end.tv_sec * 1000000000) + ts_end.tv_nsec;
			
			frameTime = endTime - startTime;
			if (frameTime > accumThreshold) {
				accumulator += frameTime - accumThreshold;
				frameTime = accumThreshold;
			} else if (accumulator > 0) {
				long t = accumThreshold - frameTime;
				if (accumulator > t) t = accumulator;
				accumulator -= t;
				frameTime += t;
			}
			timeToKill = FrameTime - frameTime;
			lastLoop = endTime;
			lastFrameTime = timeToKill;
		} else {
			struct timespec ts;
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
			long t1 = (ts.tv_sec * 1000000000) + ts.tv_nsec;
			timeToKill -= t1 - lastLoop;
			lastLoop = t1;
		}
	}
}

void SDLWidget::makeContextCurrent() {

}


void SDLWidget::takeScreenShot(const std::string& path) {

}
