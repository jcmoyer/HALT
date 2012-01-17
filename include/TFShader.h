#ifndef HALT_TFSHADER_H
#define HALT_TFSHADER_H

namespace halt {
	extern const char* TFGLSLShaderSource;

	extern const char* SAMPLER_NAME;

	extern const char* TFS_TEXCOORD;
	extern const char* TFS_COLOR;

	class TFShader {
		unsigned int handle;
	public:
		TFShader();
		~TFShader();
		inline unsigned int GetHandle() const;
	};

	// Inline functions
	inline unsigned int TFShader::GetHandle() const {
		return handle;
	}
}

#endif