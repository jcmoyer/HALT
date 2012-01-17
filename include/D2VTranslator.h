#ifndef HALT_D2VTRANSLATOR_H
#define HALT_D2VTRANSLATOR_H

// Forward declarations
namespace halt {
	struct TerminalVertex;
	class  TerminalRenderer;
}

namespace halt {
	class D2VTranslator {
		float tx_width, tx_height;
		TerminalRenderer& renderer;
	public:
		D2VTranslator(TerminalRenderer& renderer);
		void QFill(int z);
		void Fill(int value, int color, int x, int y, int x2, int y2, int z);
		void Put(int value, int color, int x, int y, int z);
		void SetTextureSize(int width, int height);
	private:
		void MapVertex(TerminalVertex* base, int value);
		void MapVertex(TerminalVertex* base, int value, int color);
	};
}

#endif