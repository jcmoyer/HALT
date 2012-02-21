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

#ifndef HALT_COMPOSESHADER_H
#define HALT_COMPOSESHADER_H

#include <TerminalShader.h>

namespace halt {
	// TShader that combines two TShaders by passing the output
	// from the first TShader into the input of the second TShader.
	template<typename S1, typename S2>
	class ComposeShader : public halt::TerminalShader {
		S1& sh1;
		S2& sh2;
	public:
		ComposeShader(S1& s1, S2& s2) : sh1(s1), sh2(s2) {
		}

		void Transform(const halt::TerminalShaderInput& input, halt::TerminalShaderOutput& output) {
			sh1.Transform(input, output);
			halt::TerminalShaderInput input2;
			input2.x     = output.x;
			input2.y     = output.y;
			input2.z     = output.z;
			input2.color = output.color;
			sh2.Transform(input2, output);
		}
	};
}

#endif