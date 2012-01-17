// HALT SOURCE FILES THAT EXPORT FUNCTIONS SHOULD INCLUDE THIS FILE
// DIRECTLY INSTEAD OF HALT.H.
#ifndef HALT_HALTDEF_H
#define HALT_HALTDEF_H

// Figure out whether or not we should use declspec.
#ifdef LINUX
// TODO: Figure out if this is how you export symbols in gcc.
#	define HALT_API __attribute__((__visibility__("default")))
#else
#	ifdef HALT_BUILD_LIBRARY
#		define HALT_API __declspec(dllexport)
#	else
#		define HALT_API __declspec(dllimport)
#	endif
#endif

#endif