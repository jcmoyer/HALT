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

#ifndef HALT_TERMINALSHADER_H
#define HALT_TERMINALSHADER_H

namespace halt {
	/// Represents a cell that is currently being written to the terminal
	/// buffer. Contains position and color information.
	struct TerminalShaderInput {
		/// The X coordinate of the cell being written in cell space.
		int x;
		/// The Y coordinate of the cell being written in cell space.
		int y;
		/// The Z coordinate of the cell being written in cell space.
		int z;
		/// Color of the cell being written.
		int color;
	};

	/// Represents the result of a terminal shader transformation. Contains
	/// transformed position and color information.
	struct TerminalShaderOutput {
		/// The X coordinate of the transformed cell in cell space.
		int x;
		/// The Y coordinate of the transformed cell in cell space.
		int y;
		/// The Z coordinate of the transformed cell in cell space.
		int z;
		/// The color of the transformed cell in cell space.
		int color;
	};

	/// Terminal shader object. Terminal shaders are responsible for transforming
	/// an input value to an output value. They are used to intercept cells
	/// as they are being written to the terminal buffer. Because of this, they
	/// are able to inject special effects like waves and colors.
	class TerminalShader {
	public:
		/// Transforms an input value into an output value.
		/// @param input Cell that is currently being written to the terminal
		///        buffer.
		/// @param output The modified cell to write to the terminal buffer.
		/// @see TerminalShaderInput
		/// @see TerminalShaderOutput
		virtual void Transform(const TerminalShaderInput& input, TerminalShaderOutput& output) = 0;
	};
}

#endif
