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