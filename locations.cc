
#include "locations.hh"

#if !defined(UNIX)
#include <shlobj.h>
#include <comdef.h>
#else
#include <stdlib.h>
#endif

#include <sstream>

std::string GetLocation(DesktopLocation location, const std::string& postfix) {
#if !defined (UNIX)
	PWSTR path;
	std::stringstream result;
	switch (location) {
		case Home: {
			SHGetKnownFolderPath(FOLDERID_Profile, 0, 0, &path);
			_bstr_t bstrPath(path);
			result<<bstrPath;
			CoTaskMemFree(static_cast<void*>(path));
			return result.str();
		}
		case Config: {
			SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, 0, &path);
			_bstr_t bstrPath(path);
			result<<bstrPath<<postfix;
			CoTaskMemFree(static_cast<void*>(path));
			return result.str();
		}
		case Cache: {
			SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, 0, &path);
			_bstr_t bstrPath(path);
			result<<bstrPath<<postfix;
			CoTaskMemFree(static_cast<void*>(path));
			return result.str();
		}
	}
	return "";
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

