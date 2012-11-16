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

#include "TProgram.h"
#include "TVShader.h"
#include "TFShader.h"
#include "Matrix.h"
#include <GL/glew.h>

namespace halt {
	TProgram::TProgram() {
		vs = new TVShader(this);
		fs = new TFShader();
		handle = glCreateProgram();
		glAttachShader(handle, vs->GetHandle());
		glAttachShader(handle, fs->GetHandle());

		glLinkProgram(handle);
		this->BindAttributes();

		this->GetUniformHandles();
		this->GetAttributeIndices();
	}

	TProgram::~TProgram() {
		if (vs) delete vs;
		if (fs) delete fs;
		if (handle) glDeleteProgram(handle);
	}

	void TProgram::Enable(bool state) {
		vs->Enable(state, vs_vertex_attrib, vs_tex_coord_attrib, vs_color_attrib);
		if (state) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_handle);
			glUseProgram(handle);

			Mat4 identity;
			Mat4::Identity(identity);

			Mat4 ortho;
			Mat4::Ortho(ortho, 0, 0, (float)width, (float)height, 0, 1);

			Mat4 proj_matrix;
			identity.Multiply(proj_matrix, ortho);
			
			// The input texture should be on sampler 0.
			glUniform1i(shader_tex_handle, GL_TEXTURE0);
			glUniformMatrix4fv(shader_mat_proj_handle, 1, false, (float*)&proj_matrix);
			glUniformMatrix4fv(shader_mat_mv_handle, 1, false, (float*)&identity);
		} else {
			glBindTexture(GL_TEXTURE_2D, 0);
			glUseProgram(0);
		}
	}

	void TProgram::GetUniformHandles() {
		glUseProgram(handle);
		shader_mat_proj_handle = glGetUniformLocation(handle, TVS_PROJECTION_MAT);
		shader_tex_handle      = glGetUniformLocation(handle, SAMPLER_NAME);
		shader_mat_mv_handle   = glGetUniformLocation(handle, TVS_MODEL_VIEW_MAT);
	}

	void TProgram::GetAttributeIndices() {
		vs_vertex_attrib = glGetAttribLocation(handle, VERTEX_ATTRIBUTE_NAME);
		vs_tex_coord_attrib = glGetAttribLocation(handle, TEXCOORD_ATTRIBUTE_NAME);
		vs_color_attrib = glGetAttribLocation(handle, COLOR_ATTRIBUTE_NAME);
	}

	void TProgram::BindAttributes() {
		glBindAttribLocation(handle, vs_vertex_attrib, VERTEX_ATTRIBUTE_NAME);
		glBindAttribLocation(handle, vs_tex_coord_attrib, TEXCOORD_ATTRIBUTE_NAME);
		glBindAttribLocation(handle, vs_color_attrib, COLOR_ATTRIBUTE_NAME);
	}
}
