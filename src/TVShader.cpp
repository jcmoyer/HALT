#include "TVShader.h"
#include "TerminalRenderer.h"
#include <glew/glew.h>

namespace halt {
	const char* TVGLSLShaderSource =
		"#version 150                                                           \n"
		"uniform mat4 tvs_Projection;                                           \n"
		"uniform mat4 tvs_ModelView;                                            \n"
		"                                                                       \n"
		"in vec2 tvs_TexCoord;                                                  \n"
		"in vec4 tvs_Vertex;                                                    \n"
		"in vec4 tvs_Color;                                                     \n"
		"                                                                       \n"
		"out vec2 tfs_TexCoord;                                                 \n"
		"out vec4 tfs_Color;                                                    \n"
		"                                                                       \n"
		"void main() {                                                          \n"
		"    gl_Position  = tvs_Projection * tvs_ModelView * tvs_Vertex;        \n"
		"    tfs_TexCoord = tvs_TexCoord;                                       \n"
		"    tfs_Color    = tvs_Color;                                          \n"
		"}                                                                      \n";

	const char* TVS_PROJECTION_MAT = "tvs_Projection";
	const char* TVS_MODEL_VIEW_MAT = "tvs_ModelView";

	const int VERTEX_ATTRIBUTE_ID = 0;
	const char* VERTEX_ATTRIBUTE_NAME = "tvs_Vertex";

	const int TEXCOORD_ATTRIBUTE_ID = 1;
	const char* TEXCOORD_ATTRIBUTE_NAME = "tvs_TexCoord";

	const int   COLOR_ATTRIBUTE_ID   = 2;
	const char* COLOR_ATTRIBUTE_NAME = "tvs_Color";

	TVShader::TVShader() {
		handle = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(handle, 1, &TVGLSLShaderSource, 0);
		glCompileShader(handle);
	}

	TVShader::~TVShader() {
		if (handle) glDeleteShader(handle);
	}

	void TVShader::Enable(bool state) {
		if (state) {
			glEnableVertexAttribArray(VERTEX_ATTRIBUTE_ID);
			glVertexAttribPointer(VERTEX_ATTRIBUTE_ID, 2, GL_UNSIGNED_SHORT, 0, sizeof(TerminalVertex), (void*)0);
			glEnableVertexAttribArray(TEXCOORD_ATTRIBUTE_ID);
			glVertexAttribPointer(TEXCOORD_ATTRIBUTE_ID, 2, GL_FLOAT, 0, sizeof(TerminalVertex), (void*)4);
			glEnableVertexAttribArray(COLOR_ATTRIBUTE_ID);
			glVertexAttribPointer(COLOR_ATTRIBUTE_ID, 4, GL_UNSIGNED_BYTE, 1, sizeof(TerminalVertex), (void*)12);
		} else {
			glDisableVertexAttribArray(VERTEX_ATTRIBUTE_ID);
			glDisableVertexAttribArray(TEXCOORD_ATTRIBUTE_ID);
			glDisableVertexAttribArray(COLOR_ATTRIBUTE_ID);
		}
	}
}