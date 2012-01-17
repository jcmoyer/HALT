#ifndef HALT_TERMINALSURFACE_H
#define HALT_TERMINALSURFACE_H

namespace halt {
	class TerminalSurface {
		unsigned int fb_handle;
		unsigned int tx_handle;
	public:
		TerminalSurface(int width, int height);
		~TerminalSurface();
		void Bind(bool state);
	};
}

#endif
