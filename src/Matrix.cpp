#include "Matrix.h"

namespace halt {
	Mat4::Mat4() {
		Mat4::Clear(*this);
	}

	void Mat4::Multiply(Mat4& out, const Mat4& other) {
		Mat4::Clear(out);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					out.v[i][j] += this->v[i][k] * other.v[k][j];
				}
			}
		}
	}

	void Mat4::Identity(Mat4& out) {
		Mat4::Clear(out);
		out.v[0][0] = 1.0f;
		out.v[1][1] = 1.0f;
		out.v[2][2] = 1.0f;
		out.v[3][3] = 1.0f;
	}

	void Mat4::Ortho(Mat4& out, float left, float top, float right, float bottom, float znear, float zfar) {
		Mat4::Clear(out);
		out.v[0][0] = 2  / (right - left);
		out.v[1][1] = 2  / (top - bottom);
		out.v[2][2] = -2 / (zfar - znear);
		out.v[3][3] = 1.0f;
		out.v[3][0] = -(right + left) / (right - left);
		out.v[3][1] = -(top + bottom) / (top - bottom);
		out.v[3][2] = -(zfar + znear) / (zfar - znear);
	}
}