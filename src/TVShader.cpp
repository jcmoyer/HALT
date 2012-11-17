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

#include "TVShader.h"
#include "TerminalRenderer.h"
#include "TProgram.h"
#include <GL/glew.h>

namespace halt {
	const char* TVGLSLShaderSource =
		"#version 120                                                           \n"
		"uniform mat4 tvs_Projection;                                           \n"
		"                                                                       \n"
		"attribute vec2 tvs_TexCoord;                                           \n"
		"attribute vec4 tvs_Vertex;                                             \n"
		"attribute vec4 tvs_Color;                                              \n"
		"                                                                       \n"
		"varying vec2 tfs_TexCoord;                                             \n"
		"varying vec4 tfs_Color;                                                \n"
		"                                                                       \n"
		"void main() {                                                          \n"
		"    gl_Position  = tvs_Projection * tvs_Vertex;                        \n"
		"    tfs_TexCoord = tvs_TexCoord;                                       \n"
		"    tfs_Color    = tvs_Color;                                          \n"
		"}                                                                      \n";

	const char* TVS_PROJECTION_MAT = "tvs_Projection";

	const char* VERTEX_ATTRIBUTE_NAME = "tvs_Vertex";
	const char* TEXCOORD_ATTRIBUTE_NAME = "tvs_TexCoord";
	const char* COLOR_ATTRIBUTE_NAME = "tvs_Color";

	TVShader::TVShader(TProgram* owner) {
		handle = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(handle, 1, &TVGLSLShaderSource, 0);
		glCompileShader(handle);
	}

	TVShader::~TVShader() {
		if (handle) glDeleteShader(handle);
	}

	void TVShader::Enable(bool state, unsigned int vertex_attrib, unsigned int tex_coord_atrrib, unsigned int color_attrib) {
		if (state) {
			glEnableVertexAttribArray(vertex_attrib);
			glVertexAttribPointer(vertex_attrib, 2, GL_UNSIGNED_SHORT, 0, sizeof(TerminalVertex), (void*)0);
			glEnableVertexAttribArray(tex_coord_atrrib);
			glVertexAttribPointer(tex_coord_atrrib, 2, GL_FLOAT, 0, sizeof(TerminalVertex), (void*)4);
			glEnableVertexAttribArray(color_attrib);
			glVertexAttribPointer(color_attrib, 4, GL_UNSIGNED_BYTE, 1, sizeof(TerminalVertex), (void*)12);
		} else {
			glDisableVertexAttribArray(vertex_attrib);
			glDisableVertexAttribArray(tex_coord_atrrib);
			glDisableVertexAttribArray(color_attrib);
		}
	}
}
