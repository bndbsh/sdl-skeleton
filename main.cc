
#ifndef UNIX
#include <Windows.h>
#endif

#include "skeleton.hh"

#ifdef UNIX
int main(int argc, char *argv[]) {
	Skeleton s;
	return s.start();
}
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR pCmdLine, int nCmdShow) {
	Skeleton s;
	return s.start();
}
