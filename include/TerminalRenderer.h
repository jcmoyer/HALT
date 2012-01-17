#ifndef HALT_TERMINALRENDERER_H
#define HALT_TERMINALRENDERER_H

// Dependencies
#include "Character.h"

// Forward declarations
namespace halt {
	class  CharacterBuffer;
	class  TProgram;
}

namespace halt {
	struct TerminalVertex {
		short x, y;
		float u, v;
		int color;
	};

	class TerminalRenderer {
		unsigned int vb_handle;
		unsigned int ib_handle;
		TerminalVertex* vertices;
		int cells;
		int width, height, depth;
		TProgram* program;
		CharacterSize ch_size;
	public:
		TerminalRenderer(int cellsw, int cellsh, int cellsd, const CharacterSize& cdim);
		~TerminalRenderer();
		void SetTexture(unsigned int handle);
		void Draw();
	private:
		void BindVBO(bool state);
		void BindIBO(bool state);
		void BuildVertices(const CharacterSize& cdim);
		void BuildIndices();
		TerminalVertex* GetBaseVertex(int x, int y, int z);

		friend class D2VTranslator;
	};
}

#endif
