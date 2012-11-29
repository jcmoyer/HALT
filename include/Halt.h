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

#ifndef HALT_HALT_H
#define HALT_HALT_H

#include "HaltDef.h"
#include "Terminal.h"
#include "Character.h"

namespace halt {
	/// Initializes HALT. This should be called after an OpenGL context has
	/// been created and is available on the current thread.
	/// @return HALT_OK on success; otherwise returns a code that you can pass
	///         to halt::GetErrorString(int) for a description of what went
	///         wrong.
	/// @see GetErrorString
	HALT_API int Initialize();

	/// Looks up the error string associated with an error code.
	/// @return The error string associated with the given error code.
	HALT_API const char* GetErrorString(int error);
}

#endif