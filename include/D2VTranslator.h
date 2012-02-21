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

#ifndef HALT_D2VTRANSLATOR_H
#define HALT_D2VTRANSLATOR_H

// Forward declarations
namespace halt {
	struct TerminalVertex;
	class  TerminalRenderer;
	class  CharacterMap;
}

namespace halt {
	class D2VTranslator {
		// Associated renderer.
		TerminalRenderer& renderer;
		// Character map for translating values to UV coordinates.
		CharacterMap& cmap;
	public:
		D2VTranslator(TerminalRenderer& renderer, CharacterMap& cmap);
		void QFill(int z);
		void Fill(int value, int color, int x, int y, int x2, int y2, int z);
		void Put(int value, int color, int x, int y, int z);
		void SetTextureSize(int width, int height);
		void SetCharacterMap(CharacterMap& cmap);
	private:
		void MapVertex(TerminalVertex* base, int value);
		void MapVertex(TerminalVertex* base, int value, int color);
	};
}

#endif