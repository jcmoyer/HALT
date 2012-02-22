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

#ifndef HALT_TERMINAL_H
#define HALT_TERMINAL_H

// Dependencies
#include "HaltDef.h"
#include "Character.h"

// Forward declarations
namespace halt {
	class TerminalRenderer;
	class D2VTranslator;
	class TerminalShader;
	class CharacterMap;
	class DefaultCharacterMap;
}

namespace halt {
	/// Terminal emulator object. This object is responsible for the creation and
	/// management of Halt objects that in turn create and manage OpenGL resources
	/// directly.
	class Terminal {
		const int width, height, depth;
		CharacterSize        size;
		TerminalRenderer*    renderer;
		D2VTranslator*       translator;
		TerminalShader*      shader;
		DefaultCharacterMap* default_cm;
	public:
		/// Creates a terminal object.
		/// @param width Width of the terminal in cells.
		/// @param height Height of the terminal in cells.
		/// @param depth Depth of the terminal in cells.
		/// @param cdim Dimension of a cell in pixels.
		HALT_API Terminal(int width, int height, int depth, const CharacterSize& cdim);
		HALT_API ~Terminal();

		/// Clears an entire layer to null. This uses cell value 0.
		/// @param z Layer to clear.
		HALT_API void Clear(int z);

		/// Writes a rectangle to the terminal buffer.
		/// @param value Cell value to use in the fill process.
		/// @param color Color of the cell.
		/// @param x1 Top left corner of the fill area on the X-axis.
		/// @param y1 Top left corner of the fill area on the Y-axis.
		/// @param x2 Bottom right corner of the fill area on the X-axis.
		/// @param y2 Bottom right corner of the fill area on the Y-axis.
		/// @param z Layer to perform the fill operation on.
		HALT_API void Fill(int value, int color, int x1, int y1, int x2, int y2, int z);

		/// Writes a single character to the terminal buffer.
		/// @param value Cell value to write.
		/// @param color Color of the cell.
		/// @param x Where to write the character on the X-axis.
		/// @param y Where to write the character on the Y-axis.
		/// @param z Which layer to write the character to.
		HALT_API void Put(int value, int color, int x, int y, int z);

		/// Writes an entire string to the terminal buffer, starting at the point
		/// denoted by x and y.
		/// @param value String to write. The cell values used are determined by
		///        the current character map.
		/// @param color Color of the cells to write.
		/// @param x Where to start writing the string on the X-axis.
		/// @param y Where to start writing the string on the Y-axis.
		/// @param z Which layer to write the character to.
		HALT_API void PutString(const char* value, int color, int x, int y, int z);

		/// Renders the terminal buffer.
		HALT_API void Draw();

		/// Sets the texture used to render cell values from.
		/// @param handle OpenGL texture handle of the texture to use.
		HALT_API void SetTexture(unsigned int handle);

		/// Sets the currently active terminal shader.
		/// @param shader Pointer to the shader to be used. To disable terminal
		///        shaders, use NULL or 0.
		/// @see TerminalShader
		HALT_API void SetShader(TerminalShader* shader);

		/// Sets the character map to use when translating cell values to texture
		/// coordinates.
		/// @param map Pointer to the character map to be used.
		/// @see CharacterMap
		HALT_API void SetCharacterMap(CharacterMap* map);

		/// Gets the width of the terminal in cells.
		/// @return The width of the terminal in cells.
		HALT_API inline int GetWidth() const;

		/// Gets the height of the terminal in cells.
		/// @return The height of the terminal in cells.
		HALT_API inline int GetHeight() const;

		/// Gets the depth of the terminal in cells.
		/// @return The depth of the terminal in cells.
		HALT_API inline int GetDepth() const;
	private:
		/// Internal use only. Configures the vertex translator to use
		/// the specified width and height when calculating UV coordinates.
		/// @param width Width of the current texture in pixels.
		/// @param height Height of the current texture in pixels.
		void SetTextureSize(int width, int height);
	};

	// Inline functions
	inline int Terminal::GetWidth() const {
		return width;
	}

	inline int Terminal::GetHeight() const {
		return height;
	}

	inline int Terminal::GetDepth() const {
		return depth;
	}
}

#endif
