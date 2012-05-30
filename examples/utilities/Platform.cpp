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

#include "Platform.h"
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

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
