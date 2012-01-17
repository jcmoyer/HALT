#include "D2VTranslator.h"
#include "TerminalRenderer.h"
#include <memory>

namespace halt {
	D2VTranslator::D2VTranslator(TerminalRenderer& renderer) : renderer(renderer), tx_width(1.0f), tx_height(1.0f) {
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
		tx_width  = static_cast<float>(width);
		tx_height = static_cast<float>(height);
	}

	void D2VTranslator::MapVertex(TerminalVertex* base, int value) {
		if (base == 0) return;
		float scale_x = renderer.ch_size.width  / tx_width;
		float scale_y = renderer.ch_size.height / tx_height;
		float src_x   = (value & 0x0F)        * scale_x;
		float src_y   = ((value >> 4) & 0x0F) * scale_y;
		base[0].u = src_x;
		base[0].v = src_y;
		base[1].u = src_x + scale_x;
		base[1].v = src_y;
		base[2].u = src_x;
		base[2].v = src_y + scale_y;
		base[3].u = src_x + scale_x;
		base[3].v = src_y + scale_y;
	}

	void D2VTranslator::MapVertex(TerminalVertex* base, int value, int color) {
		if (base == 0) return;
		float scale_x = renderer.ch_size.width  / tx_width;
		float scale_y = renderer.ch_size.height / tx_height;
		float src_x   = (value & 0x0F)        * scale_x;
		float src_y   = ((value >> 4) & 0x0F) * scale_y;
		base[0].u = src_x;
		base[0].v = src_y;
		base[0].color = color;
		base[1].u = src_x + scale_x;
		base[1].v = src_y;
		base[1].color = color;
		base[2].u = src_x;
		base[2].v = src_y + scale_y;
		base[2].color = color;
		base[3].u = src_x + scale_x;
		base[3].v = src_y + scale_y;
		base[3].color = color;
	}
}