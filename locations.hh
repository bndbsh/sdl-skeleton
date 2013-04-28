#ifndef _SKELETON_LOCATIONS_HH_
#define _SKELETON_LOCATIONS_HH_

#include <string>

typedef enum {
	Config,
	Cache,
	Home
} DesktopLocation;

std::string GetLocation(DesktopLocation location, const std::string& postfix = "");

#endif
