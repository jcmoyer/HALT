#ifndef HALT_TPROGRAM_H
#define HALT_TPROGRAM_H

// Forward declarations
namespace halt {
	class TVShader;
	class TFShader;
}

namespace halt {
	class TProgram {
		unsigned int handle;
		TVShader* vs;
		TFShader* fs;
		int width, height;
		unsigned int tex_handle;
		unsigned int shader_tex_handle;
		unsigned int shader_mat_proj_handle;
		unsigned int shader_mat_mv_handle;
	public:
		TProgram();
		~TProgram();
		void Enable(bool state);
		inline void SetTexture(unsigned int tx_handle);
		inline void SetOutputSize(int width, int height);
	private:
		void GetUniformHandles();
		void BindAttributes();
	};

	// Inline functions
	inline void TProgram::SetTexture(unsigned int handle) {
		tex_handle = handle;
	}

	inline void TProgram::SetOutputSize(int width, int height) {
		this->width  = width;
		this->height = height;
	}
}

#endif