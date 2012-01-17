#include "TProgram.h"
#include "TVShader.h"
#include "TFShader.h"
#include "Matrix.h"
#include <glew/glew.h>

namespace halt {
	TProgram::TProgram() {
		vs = new TVShader();
		fs = new TFShader();

		handle = glCreateProgramObjectARB();
		glAttachShader(handle, vs->GetHandle());
		glAttachShader(handle, fs->GetHandle());

		this->BindAttributes();

		glLinkProgram(handle);

		this->GetUniformHandles();
	}

	TProgram::~TProgram() {
		if (vs) delete vs;
		if (fs) delete fs;
		if (handle) glDeleteProgram(handle);
	}

	void TProgram::Enable(bool state) {
		vs->Enable(state);
		if (state) {
			glBindTexture(GL_TEXTURE_2D, tex_handle);
			glUseProgram(handle);

			Mat4 identity;
			Mat4::Identity(identity);

			Mat4 ortho;
			Mat4::Ortho(ortho, 0, 0, (float)width, (float)height, 0, 1);

			Mat4 proj_matrix;
			identity.Multiply(proj_matrix, ortho);
			
			// The input texture should be on sampler 0.
			glUniform1i(shader_tex_handle, 0);
			glUniformMatrix4fv(shader_mat_proj_handle, 1, false, (float*)&proj_matrix);
			glUniformMatrix4fv(shader_mat_mv_handle, 1, false, (float*)&identity);
		} else {
			glBindTexture(GL_TEXTURE_2D, 0);
			glUseProgram(0);
		}
	}

	void TProgram::GetUniformHandles() {
		shader_tex_handle      = glGetUniformLocation(handle, SAMPLER_NAME);
		shader_mat_proj_handle = glGetUniformLocation(handle, TVS_PROJECTION_MAT);
		shader_mat_mv_handle   = glGetUniformLocation(handle, TVS_MODEL_VIEW_MAT);
	}

	void TProgram::BindAttributes() {
		glBindAttribLocation(handle, VERTEX_ATTRIBUTE_ID, VERTEX_ATTRIBUTE_NAME);
		glBindAttribLocation(handle, TEXCOORD_ATTRIBUTE_ID, TEXCOORD_ATTRIBUTE_NAME);
		glBindAttribLocation(handle, COLOR_ATTRIBUTE_ID, COLOR_ATTRIBUTE_NAME);
	}
}