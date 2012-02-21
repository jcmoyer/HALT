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

#include "CharacterMap.h"
#include "TerminalRenderer.h"

namespace halt {
	CharacterMap::CharacterMap(int texw, int texh) : tx_width(texw), tx_height(texh) {
	}

	DefaultCharacterMap::DefaultCharacterMap(int texw, int texh, CharacterSize charsize) : CharacterMap(texw, texh), ch_size(charsize) {
	}

	void DefaultCharacterMap::Map(int value, TerminalVertex* base) const {
		if (!base) return;
		const float scale_x = ch_size.width  / static_cast<float>(tx_width);
		const float scale_y = ch_size.height / static_cast<float>(tx_height);
		const float src_x   = (value & 0x0F)        * scale_x;
		const float src_y   = ((value >> 4) & 0x0F) * scale_y;
		base[0].u = src_x;
		base[0].v = src_y;
		base[1].u = src_x + scale_x;
		base[1].v = src_y;
		base[2].u = src_x;
		base[2].v = src_y + scale_y;
		base[3].u = src_x + scale_x;
		base[3].v = src_y + scale_y;
	}
}