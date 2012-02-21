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