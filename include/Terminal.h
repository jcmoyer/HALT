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

#ifndef HALT_TERMINAL_H
#define HALT_TERMINAL_H

// Dependencies
#include "HaltDef.h"
#include "Character.h"

// Forward declarations
namespace halt {
	class TerminalRenderer;
	class D2VTranslator;
	class TerminalShader;
	class CharacterMap;
	class DefaultCharacterMap;
}

namespace halt {
	class Terminal {
		const int width, height, depth;
		CharacterSize        size;
		TerminalRenderer*    renderer;
		D2VTranslator*       translator;
		TerminalShader*      shader;
		DefaultCharacterMap* default_cm;
	public:
		HALT_API Terminal(int width, int height, int depth, const CharacterSize& cdim);
		HALT_API ~Terminal();
		HALT_API void Clear(int z);
		HALT_API void Fill(int value, int color, int x1, int y1, int x2, int y2, int z);
		HALT_API void Put(int value, int color, int x, int y, int z);
		HALT_API void PutString(const char* value, int color, int x, int y, int z);
		HALT_API void Draw();
		HALT_API void SetTexture(unsigned int handle);
		HALT_API void SetShader(TerminalShader* shader);
		HALT_API void SetCharacterMap(CharacterMap* map);
	private:
		// Internal use only.
		void SetTextureSize(int width, int height);
	};
}

#endif
