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

#include "TFShader.h"
#include <GL/glew.h>

namespace halt {
	const char* TFGLSLShaderSource =
		"#version 150                                                           \n"
		"uniform sampler2D tfs_Sampler0;                                        \n"
		"                                                                       \n"
		"in  vec2 tfs_TexCoord;                                                 \n"
		"in  vec4 tfs_Color;                                                    \n"
		"                                                                       \n"
		"out vec4 tfs_Output;                                                   \n"
		"                                                                       \n"
		"void main() {                                                          \n"
		"    tfs_Output = texture(tfs_Sampler0, tfs_TexCoord) * tfs_Color;      \n"
		"}                                                                      \n";

	const char* SAMPLER_NAME = "tfs_Sampler0";
	const char* TFS_TEXCOORD = "tfs_TexCoord";
	const char* TFS_COLOR    = "tfs_Color";

	TFShader::TFShader() {
		handle = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(handle, 1, &TFGLSLShaderSource, 0);
		glCompileShader(handle);
	}

	TFShader::~TFShader() {
		if (handle) glDeleteShader(handle);
	}
}
