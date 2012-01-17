#ifndef HALT_MATRIX_H
#define HALT_MATRIX_H

// Dependencies
#include <memory>

namespace halt {
	class Mat4 {
	public:
		float v[4][4];
	public:
		Mat4();
		void Multiply(Mat4& out, const Mat4& other);
		static void Identity(Mat4& out);
		static void Ortho(Mat4& out, float left, float top, float right, float bottom, float znear, float zfar);
		inline static void Clear(Mat4& out);
	};

	inline void Mat4::Clear(Mat4& out) {
		memset(&out, 0, sizeof(float) * 16);
	}
}

#endif