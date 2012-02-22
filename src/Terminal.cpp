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

#include "Terminal.h"
#include "Character.h"
#include "TerminalRenderer.h"
#include "D2VTranslator.h"
#include "TerminalShader.h"
#include "CharacterMap.h"
#include <cstring>
#include <glew/glew.h>

namespace halt {
	Terminal::Terminal(int width, int height, int depth, const CharacterSize& cdim)
		: width(width), height(height), depth(depth), size(cdim), shader(0) {
		renderer   = new TerminalRenderer(width, height, depth, cdim);
		default_cm = new DefaultCharacterMap(1, 1, cdim);
		translator = new D2VTranslator(*renderer, *default_cm);
	}

	Terminal::~Terminal() {
		if (renderer) delete renderer;
		if (default_cm) delete default_cm;
		if (translator) delete translator;
	}

	void Terminal::Clear(int z) {
		if (shader) {
			for (int i = 0; i < width * height; i++) {
				TerminalShaderInput  input;
				TerminalShaderOutput output;
				input.x     = i % width;
				input.y     = i / width;
				input.z     = z;
				input.color = 0;
				shader->Transform(input, output);
				translator->Put(0xDB, output.color, output.x, output.y, output.z);
			}
		} else {
			translator->QFill(z);
		}
	}

	void Terminal::Fill(int value, int color, int x1, int y1, int x2, int y2, int z) {
		if (shader) {
			for (int x = x1; x <= x2; x++) {
				for (int y = y1; y <= y2; y++) {
					TerminalShaderInput  input;
					TerminalShaderOutput output;
					input.x     = x;
					input.y     = y;
					input.z     = z;
					input.color = color;
					shader->Transform(input, output);
					translator->Put(value, output.color, output.x, output.y, output.z);
				}
			}
		} else {
			translator->Fill(value, color, x1, y1, x2, y2, z);
		}
	}

	void Terminal::Put(int value, int color, int x, int y, int z) {
		if (shader) {
			TerminalShaderInput  input;
			TerminalShaderOutput output;
			input.x     = x;
			input.y     = y;
			input.z     = z;
			input.color = color;
			shader->Transform(input, output);
			translator->Put(value, output.color, output.x, output.y, output.z);
		} else {
			translator->Put(value, color, x, y, z);
		}
	}

	void Terminal::PutString(const char* value, int color, int x, int y, int z) {
		if (shader) {
			TerminalShaderInput  input;
			TerminalShaderOutput output;
			for (size_t i = 0; i < strlen(value); i++) {
				input.x     = x + i;
				input.y     = y;
				input.z     = z;
				input.color = color;
				shader->Transform(input, output);
				translator->Put(value[i], output.color, output.x, output.y, output.z);
			}
		} else {
			for (size_t i = 0; i < strlen(value); i++) {
				translator->Put(value[i], color, x + i, y, z);
			}
		}
	}

	void Terminal::Draw() {
		this->renderer->Draw();
	}

	void Terminal::SetTexture(unsigned int handle) {
		this->renderer->SetTexture(handle);

		// Figure out the size of the texture and pass it on to
		// components that need it.
		int width, height;
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH,  &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
		this->SetTextureSize(width, height);
	}

	void Terminal::SetShader(TerminalShader* shader) {
		this->shader = shader;
	}

	void Terminal::SetCharacterMap(CharacterMap* map) {
		// If a map is provided, use that. Otherwise, revert to the
		// default map.
		if (map) {
			this->translator->SetCharacterMap(*map);
		} else {
			this->translator->SetCharacterMap(*default_cm);
		}
	}

	void Terminal::SetTextureSize(int width, int height) {
		this->translator->SetTextureSize(width, height); 
	}
}