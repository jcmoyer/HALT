#include "Terminal.h"
#include "Character.h"
#include "TerminalRenderer.h"
#include "D2VTranslator.h"
#include "TerminalShader.h"
#include "CharacterMap.h"
#include <cstring>

namespace halt {
	Terminal::Terminal(int width, int height, int depth, const CharacterSize& cdim)
		: width(width), height(height), depth(depth), size(cdim), shader(0) {
		renderer   = new TerminalRenderer(width, height, depth, cdim);
		default_cm = new DefaultCharacterMap(1.0f, 1.0f, cdim);
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
	}

	void Terminal::SetTextureSize(int width, int height) {
		this->translator->SetTextureSize(width, height);
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
}