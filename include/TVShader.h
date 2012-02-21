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

#ifndef HALT_TVSHADER_H
#define HALT_TVSHADER_H

namespace halt {
	extern const char* TVGLSLShaderSource;

	extern const char* TVS_PROJECTION_MAT;
	extern const char* TVS_MODEL_VIEW_MAT;

	extern const int   VERTEX_ATTRIBUTE_ID;
	extern const char* VERTEX_ATTRIBUTE_NAME;
	extern const int   TEXCOORD_ATTRIBUTE_ID;
	extern const char* TEXCOORD_ATTRIBUTE_NAME;
	extern const int   COLOR_ATTRIBUTE_ID;
	extern const char* COLOR_ATTRIBUTE_NAME;

	class TVShader {
		unsigned int handle;
	public:
		TVShader();
		~TVShader();
		void Enable(bool state);
		inline unsigned int GetHandle() const;
	};

	// Inline functions
	inline unsigned int TVShader::GetHandle() const {
		return handle;
	}
}

#endif