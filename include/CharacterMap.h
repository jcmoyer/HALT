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

#ifndef HALT_CHARACTERMAP_H
#define HALT_CHARACTERMAP_H

#include "Character.h"

// Forward declarations
namespace halt {
	struct TerminalVertex;
}

namespace halt {
	/// Abstract class for mapping character values to UV coordinates.
	class CharacterMap {
	public:
		/// Width of the texture used to render the terminal.
		int tx_width;
		/// Height of the texture used to render the terminal.
		int tx_height;
		/// Creates a CharacterMap given a texture's width and height.
		/// @param texw Texture width.
		/// @param texh Texture height.
		CharacterMap(int texw, int texh);

		/// Maps a cell value to UV coordinates.
		/// @param value Cell value to map.
		/// @param base Pointer to the vertices that need to be modified. It
		///        is safe to modify four vertices starting from this pointer.
		/// @see TerminalVertex
		virtual void Map(int value, TerminalVertex* base) const = 0;
	};

	/// Default character map. Only supports up to 256 characters (values are
	/// limited to the range of a single byte). Cell values are translated to
	/// UV coordinates based on their upper and lower 4 bits. The least
	/// significant four bits represent the number of cells into the texture
	/// from the left side that UV coordinates will be used from. Likewise,
	/// the most significant four bits represent the number of cells into
	/// the texture from the top side.
	class DefaultCharacterMap : public CharacterMap {
		CharacterSize ch_size;
	public:
		/// Creates a DefaultCharacterMap given a texture's width, height,
		/// and the size of cells in the terminal.
		/// @param texw Texture width.
		/// @param texh Texture height.
		/// @param charsize Cell size.
		DefaultCharacterMap(int texw, int texh, CharacterSize charsize);
		void Map(int value, TerminalVertex* base) const;
	};
}

#endif