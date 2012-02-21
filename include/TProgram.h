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