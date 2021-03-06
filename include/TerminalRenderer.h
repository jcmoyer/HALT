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

#ifndef HALT_TERMINALRENDERER_H
#define HALT_TERMINALRENDERER_H

// Dependencies
#include "Character.h"

// Forward declarations
namespace halt {
	class CharacterBuffer;
	class TProgram;
}

namespace halt {
	/// Represents a vertex used to render the terminal.
	struct TerminalVertex {
		/// X coordinate of the vertex, in pixels.
		short x;
		/// Y coordinate of the vertex, in pixels.
		short y;
		/// U value of the texture coordinate. 0.0f is the left side of the
		/// texture, and 1.0f is the right side of the texture.
		float u;
		/// V value of the texture coordinate. 0.0f is the top side of the
		/// texture, and 1.0f is the bottom side of the texture.
		float v;
		/// Color of the vertex.
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
