#ifndef HALT_TERMINAL_H
#define HALT_TERMINAL_H

// Dependencies
#include "HaltDef.h"
#include "Character.h"

// Forward declarations
namespace halt {
	class  TerminalRenderer;
	class  D2VTranslator;
	class  TerminalShader;
}

namespace halt {
	class Terminal {
		const int width, height, depth;
		CharacterSize     size;
		TerminalRenderer* renderer;
		D2VTranslator*    translator;
		TerminalShader*   shader;
	public:
		HALT_API Terminal(int width, int height, int depth, const CharacterSize& cdim);
		HALT_API ~Terminal();
		HALT_API void Clear(int z);
		HALT_API void Fill(int value, int color, int x1, int y1, int x2, int y2, int z);
		HALT_API void Put(int value, int color, int x, int y, int z);
		HALT_API void PutString(const char* value, int color, int x, int y, int z);
		HALT_API void Draw();
		HALT_API void SetTexture(unsigned int handle);
		HALT_API void SetTextureSize(int width, int height);
		HALT_API void SetShader(TerminalShader* shader);
	};
}

#endif
