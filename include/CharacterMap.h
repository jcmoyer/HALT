#ifndef HALT_CHARACTERMAP_H
#define HALT_CHARACTERMAP_H

#include "Character.h"

// Forward declarations
namespace halt {
	struct TerminalVertex;
}

namespace halt {
	// Abstract class for mapping character values to UV coordinates.
	class CharacterMap {
	public:
		int tx_width, tx_height;
		CharacterMap(int texw, int texh);
		virtual void Map(int value, TerminalVertex* base) const = 0;
	};

	// Default character map. With this map, the number of characters is limited
	// to 256. The significant parts of a character value consists of the least
	// significant byte. Given this byte, the most significant four bits represent
	// the Y value of the character given a texture. The least significant four
	// bits represent the X value of the character. This allows for a character
	// texture consisting of of 16x16 (256) characters arranged in a grid. For
	// example, the value 0x48 would take the 8th character from the left and
	// 4th character from the top, selecting the 72nd character in the texture.
	// These positions are zero-based. Here is a visual representation, where X
	// is the character that will be selected:
	//  _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	// |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
	// |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
	// |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
	// |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
	// |_|_|_|_|_|_|_|_|X|_|_|_|_|_|_|_|
	// |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
	// |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
	// |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
	// |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
	// |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
	// |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
	// |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
	// |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
	// |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
	// |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
	// |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|
	//
	class DefaultCharacterMap : public CharacterMap {
		CharacterSize ch_size;
	public:
		DefaultCharacterMap(int texw, int texh, CharacterSize charsize);
		void Map(int value, TerminalVertex* base) const;
	};
}

#endif