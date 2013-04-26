
#include "skeleton.hh"

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

#ifndef UNIX
#include <windows.h>
#endif
#include "gfx/glew.h"

class GLError : std::exception {
	std::string data;
public:
	GLError(const std::string& data) : data(data) {}
	virtual ~GLError() throw() {}
	inline virtual const char* what() const throw() { return data.c_str(); }
};

int main(int argc, char *argv[]) {
	Skeleton bul(argc, argv);
	return bul.start();
}

Skeleton::Skeleton(int& argc, char** argv) {}

Skeleton::~Skeleton() {
	delete widget;
}

int Skeleton::start() {
	load();
	widget->startLoop();
	return 0;
}

void Skeleton::resize(int width, int height) {
	glViewport(0, 0, width, height);
	return;
}

void Skeleton::load() {
	widget = new SDLWidget(true, this);
	
	int errg = glewInit();
	if (errg != GLEW_OK) {
		char errbuff[50];
		memset(errbuff, 0, 50);
		sprintf(errbuff, "%s", glewGetErrorString(errg));
		throw GLError(std::string("Failed to initialize GLEW: ") + errbuff);
	}
	
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Skeleton::update(double frametime) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

