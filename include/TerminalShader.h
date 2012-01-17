#ifndef HALT_TERMINALSHADER_H
#define HALT_TERMINALSHADER_H

namespace halt {
	struct TerminalShaderInput {
		int x, y, z;
		int color;
	};

	struct TerminalShaderOutput {
		int x, y, z;
		int color;
	};

	class TerminalShader {
	public:
		virtual void Transform(const TerminalShaderInput& input, TerminalShaderOutput& output) = 0;
	};
}

#endif
