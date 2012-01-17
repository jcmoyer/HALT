#include "TerminalSurface.h"
#include <glew/glew.h>

namespace halt {
	TerminalSurface::TerminalSurface(int width, int height) {
		// Generate OpenGL handles: one FBO and one texture to attach to it.
		glGenFramebuffers(1, &fb_handle);
		glGenTextures(1, &tx_handle);

		// Bind the FBO and texture so we can perform operations on them.
		this->Bind(true);

		// Attach the texture to the FBO at COLOR_ATTACHMENT0.
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tx_handle, 0);

		// Prevent accidental use of the FBO.
		this->Bind(false);

		// TODO:
		// glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	}

	TerminalSurface::~TerminalSurface() {
		// Release our acquired handles.
		glDeleteFramebuffers(1, &fb_handle);
		glDeleteTextures(1, &tx_handle);
	}

	void TerminalSurface::Bind(bool state) {
		if (state) {
			glBindFramebuffer(GL_FRAMEBUFFER, fb_handle);
			glBindTexture(GL_TEXTURE_2D, tx_handle);
		} else {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}