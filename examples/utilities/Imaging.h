#ifndef HALT_IMAGING_H
#define HALT_IMAGING_H

#include <sdl/SDL_opengl.h>

// Simple function to load textures using stb_image.
namespace halt {
	GLuint LoadTexture(const char* filename);
}

#endif