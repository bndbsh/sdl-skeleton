
#include <silver/util/locations.hh>

#if !defined(UNIX)
#include <shlobj.h>
#else
#include <stdlib.h>
#endif

namespace silver {
namespace util {

std::string GetLocation(DesktopLocation location, const std::string& postfix) {
#if !defined (UNIX)

#else
	switch (location) {
		case Home:
			return getenv("HOME");
			break;
		case Config:
			if (getenv("XDG_CONFIG_HOME")) return std::string(getenv("XDG_CONFIG_HOME")) + "/" + postfix;
			return std::string(getenv("HOME")) + "/.config/" + postfix;
			break;
		case Cache:
			if (getenv("XDG_CACHE_HOME")) return std::string(getenv("XDG_CACHE_HOME")) + "/" + postfix;
			return std::string(getenv("HOME")) + "/.cache/" + postfix;
			break;
		default:
			return "";
			break;
	}
	return "";
#endif
}

}
}
