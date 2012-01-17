#include "TFShader.h"
#include <glew/glew.h>

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
		handle = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
		glShaderSourceARB(handle, 1, &TFGLSLShaderSource, 0);
		glCompileShaderARB(handle);
	}

	TFShader::~TFShader() {
		if (handle) glDeleteShader(handle);
	}
}