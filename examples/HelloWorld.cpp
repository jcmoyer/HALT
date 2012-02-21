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

#ifdef _WIN32
#include <windows.h>
#endif

#include <sdl/sdl.h>
#include <sdl/SDL_opengl.h>
#include <cmath>
#include <Halt.h>
#include <TerminalShader.h>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include "utilities/Imaging.h"
#include "utilities/Platform.h"

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
#	define RGBA32(r, g, b, a) a<<24 | b<<16 | g<<8 | r
#else
#	define RGBA32(r, g, b, a) r<<24 | g<<16 | b<<8 | a
#endif

struct ApplicationState {
	bool running;
};

// Simple self-contained function to calculate FPS.
int GetFPS() {
	static int store_fps = 0;
	static int fps = 0;
	static double accumulator = 0;
	static clock_t last = clock();
	clock_t now = clock();
	accumulator += (now - last) / (double)CLOCKS_PER_SEC;
	last = now;
	if (accumulator > 1) {
		store_fps = fps;
		fps = 0;
		accumulator = 0;
	}
	fps++;
	return store_fps;
}

// Function for clamping a numeric value between two values.
template<typename T>
inline T clamp(T val, T min, T max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

// Terminal shader that colors characters rendered based on
// their position and the current time.
class BGShader : public halt::TerminalShader {
	void Transform(const halt::TerminalShaderInput& input, halt::TerminalShaderOutput& output) {
		double now = clock() / (double)CLOCKS_PER_SEC;

		// Output position should be the same as input position.
		output.x = input.x;
		output.y = input.y;
		output.z = input.z;

		// Color the resulting character.
		int r = clamp(static_cast<int>((input.x / 80.0f) * 128) + 
			static_cast<int>((sin(now) * 96.0) + 32.0), 0, 255);
		int g = clamp(static_cast<int>((input.y / 25.0f) * 128) +
			static_cast<int>((cos(0.8 * now) * 96.0) + 32.0), 0, 255);
		int b = clamp(static_cast<int>(((input.x + input.y) / 105.0f) * 128) + 
			static_cast<int>((cos(0.6 * now) * 128.0) + 128.0), 0, 255);
		output.color = RGBA32(r, g, b, 255);
	}
};

// Handles events and mutates application state.
void HandleEvents(ApplicationState& state) {
	SDL_Event eve;
	while (SDL_PollEvent(&eve)) {
		if (eve.type == SDL_QUIT) {
			state.running = false;
		}
		if (eve.type == SDL_KEYDOWN && eve.key.keysym.sym == SDLK_ESCAPE) {
			state.running = false;
		}
	}
}

#ifdef _WIN32
BOOL WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
#else
int main(int argc, char** argv) {
#endif
	// Initialize SDL.
	if (!halt::InitSDL()) {
		return EXIT_FAILURE;
	}

	// Set up some general OpenGL states.
	halt::InitStaticStates();

	// Initialize Halt.
	halt::Initialize();

	// Size of cells in the terminal, in pixels.
	halt::CharacterSize size;
	size.width  = 8;
	size.height = 12;

	// Create the actual terminal. It is 80 cells wide, 25 cells
	// high, and 2 cells deep.
	halt::Terminal* term = new halt::Terminal(80, 25, 2, size);

	// Load the actual terminal character map.
	GLuint texture = halt::LoadTexture("res/default.png");

	// Tell HALT to use the loaded texture.
	term->SetTexture(texture);

	// Write some text to the terminal. Writes are buffered, so changes won't
	// appear until halt::Terminal::Draw is called.
	term->PutString("Hello World!", RGBA32(0, 255, 0, 255), 0, 0, 0);

	// Terminal shader used for the background effect.
	BGShader bg_shader;

	// Simple object for keeping track of application state.
	ApplicationState state;
	state.running = true;

	// String stream that contains the FPS string.
	std::stringstream fps_stream;

	// Main loop.
	while (state.running) {
		HandleEvents(state);

		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT);

		// Clear the FPS string stream and write the current FPS to it.
		fps_stream.str(std::string());
		fps_stream<<"FPS: "<<GetFPS();

		// Activate the background shader.
		term->SetShader(&bg_shader);
		// Clear the bottom-most page of the terminal (depth 0). Remember
		// that the terminal has two pages of cells.
		term->Clear(0);

		// Disable shaders.
		term->SetShader(0);
		// Clear the top-most page of the terminal.
		term->Clear(1);
		// Write the FPS string to the middle of the screen, on the top-most
		// page.
		term->PutString(fps_stream.str().c_str(), 0xFFFFFFFF, 36, 12, 1);

		// Actually render the terminal.
		term->Draw();

		// Present the contents of the backbuffer to the user.
		SDL_GL_SwapBuffers();
	}

	// Clean up resources that we used.
	delete term;
	glDeleteTextures(1, &texture);

	return EXIT_SUCCESS;
}