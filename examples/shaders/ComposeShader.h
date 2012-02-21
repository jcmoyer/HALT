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