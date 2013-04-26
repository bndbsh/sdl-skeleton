#ifndef _SILVER_UTIL_LOCATIONS_HH_
#define _SILVER_UTIL_LOCATIONS_HH_

#include <string>

namespace silver {
namespace util {

typedef enum {
	Config,
	Cache,
	Home
} DesktopLocation;

std::string GetLocation(DesktopLocation location, const std::string& postfix = "");

}
}

#endif
