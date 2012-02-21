#include "Imaging.h"
#include "stb_image.h"

namespace halt {
	GLuint LoadTexture(const char* filename) {
		GLuint texture = 0;
		int x, y, n;
		void* ptr = stbi_load(filename, &x, &y, &n, 4);
		if (ptr) {
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr);
		}
		stbi_image_free(ptr);
		return texture;
	}
}
