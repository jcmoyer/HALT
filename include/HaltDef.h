// ============================================================================
// Copyright (c) 2011-2012 J.C. Moyer
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ============================================================================

// HALT SOURCE FILES THAT EXPORT FUNCTIONS SHOULD INCLUDE THIS FILE
// DIRECTLY INSTEAD OF HALT.H.
#ifndef HALT_HALTDEF_H
#define HALT_HALTDEF_H

// Figure out whether or not we should use declspec.
// WARNING: Be wary of declspec. This definitely needs to be revisited ASAP.
// This caused some weird bugs when building HALT as a static library under
// mingw. Activating __declspec for Visual Studio only is a high priority for
// the near future.
#if (defined(LINUX)) || (defined(linux)) || (defined(__linux)) || (defined(__GNUC__))
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
