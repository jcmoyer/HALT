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

#include "D2VTranslator.h"
#include "TerminalRenderer.h"
#include "CharacterMap.h"
#include <memory>

namespace halt {
	D2VTranslator::D2VTranslator(TerminalRenderer& renderer, CharacterMap& cmap) : renderer(renderer), cmap(cmap) {

	}

	void D2VTranslator::QFill(int z) {
		TerminalVertex* base = renderer.GetBaseVertex(0, 0, z);
		for (int i = 0; i < renderer.width * renderer.height; i++) {
			base[i].u     = 0.0f;
			base[i].v     = 0.0f;
			base[i].color = 0;
		}
	}

	void D2VTranslator::Fill(int value, int color, int x, int y, int x2, int y2, int z) {
		for (int i = x; i <= x2; i++) {
			for (int j = y; j <= y2; j++) {
				this->Put(value, color, i, j, z);
			}
		}
	}

	void D2VTranslator::Put(int value, int color, int x, int y, int z) {
		MapVertex(renderer.GetBaseVertex(x, y, z), value, color);
	}

	void D2VTranslator::SetTextureSize(int width, int height) {
		this->cmap.tx_width  = width;
		this->cmap.tx_height = height;
	}

	void D2VTranslator::SetCharacterMap(CharacterMap& cmap) {
		this->cmap = cmap;
	}

	void D2VTranslator::MapVertex(TerminalVertex* base, int value) {
		if (!base) return;
		cmap.Map(value, base);
	}

	void D2VTranslator::MapVertex(TerminalVertex* base, int value, int color) {
		if (!base) return;
		cmap.Map(value, base);
		base[0].color = color;
		base[1].color = color;
		base[2].color = color;
		base[3].color = color;
	}
}