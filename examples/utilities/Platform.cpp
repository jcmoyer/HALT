#include "Platform.h"
#include <sdl/SDL.h>
#include <sdl/SDL_opengl.h>

namespace halt {
	bool InitSDL() {
		// Make sure SDL_Quit is called when we exit.
		atexit(SDL_Quit);

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			return false;
		}

		SDL_WM_SetCaption("halt2: hardware accelerated terminal", NULL);
		SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 0);

		// The surface returned here is freed by SDL_Quit. Since we don't use it,
		// it's safe to let it go.
		SDL_Surface* screen = SDL_SetVideoMode(8 * 80, 12 * 25, 32, SDL_OPENGL);
		if (!screen) {
			return false;
		}

		return true;
	}

	void InitStaticStates() {
		glClearColor(0, 0, 0, 1);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}
