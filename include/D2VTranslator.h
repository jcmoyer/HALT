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