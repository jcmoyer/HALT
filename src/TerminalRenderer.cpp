#include "TerminalRenderer.h"
#include "Character.h"
#include "TProgram.h"
#include <glew/glew.h>

namespace halt {
	TerminalRenderer::TerminalRenderer(int cellsw, int cellsh, int cellsd, const CharacterSize& cdim)
		: width(cellsw), height(cellsh), depth(cellsd), ch_size(cdim) {
		glGenBuffers(1, &vb_handle);
		glGenBuffers(1, &ib_handle);

		// Allocate enough vertices to hold all of the cells in the terminal on all layers.
		cells = width * height * depth;
		vertices = new TerminalVertex[cells * sizeof(TerminalVertex) * 4];

		this->BuildVertices(cdim);
		this->BuildIndices();

		program = new TProgram();
		program->SetOutputSize(width * ch_size.width, height * ch_size.height);
	}

	TerminalRenderer::~TerminalRenderer() {
		if (vb_handle) glDeleteBuffers(1, &vb_handle);
		if (ib_handle) glDeleteBuffers(1, &ib_handle);
		if (vertices) delete[] vertices;
		if (program) delete program;
	}

	void TerminalRenderer::SetTexture(unsigned int handle) {
		program->SetTexture(handle);
	}

	void TerminalRenderer::Draw() {
		this->BindVBO(true);
		this->BindIBO(true);
		program->Enable(true);

		for (int z = 0; z < depth; z++) {
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, 4 * width * height * sizeof(TerminalVertex),
				(vertices + width * height * 4 * z), GL_STREAM_DRAW_ARB);

			glDrawRangeElements(
				GL_TRIANGLES,
				6 * width * height * z,
				6 * width * height * z + 6 * width * height,
				6 * width * height,
				GL_UNSIGNED_SHORT,
				0);

			// Request a new block of memory so we don't block while waiting to draw.
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, 0, 0, GL_STREAM_DRAW_ARB);
		}
		
		this->BindVBO(false);
		this->BindIBO(false);
		program->Enable(false);
	}

	void TerminalRenderer::BindVBO(bool state) {
		if (state) {
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, vb_handle);
		} else {
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
		}
	}

	void TerminalRenderer::BindIBO(bool state) {
		if (state) {
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, ib_handle);
		} else {
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
		}
	}

	void TerminalRenderer::BuildVertices(const CharacterSize& cdim) {
		// Preset the vertex positions so we only have to update texture coordinates
		// and colors. Note that this does not send the vertices to the GPU yet.
		for (int z = 0; z < depth; z++) {
			int page_offset = z * width * height;
			for (int i = 0; i < width * height; i++) {
				vertices[(page_offset + i) * 4 + 0].x = cdim.width  * (i % width);
				vertices[(page_offset + i) * 4 + 0].y = cdim.height * (i / width);
				vertices[(page_offset + i) * 4 + 1].x = cdim.width  * (i % width) + cdim.width;
				vertices[(page_offset + i) * 4 + 1].y = cdim.height * (i / width);
				vertices[(page_offset + i) * 4 + 2].x = cdim.width  * (i % width);
				vertices[(page_offset + i) * 4 + 2].y = cdim.height * (i / width) + cdim.height;
				vertices[(page_offset + i) * 4 + 3].x = cdim.width  * (i % width) + cdim.width;
				vertices[(page_offset + i) * 4 + 3].y = cdim.height * (i / width) + cdim.height;
			}
		}
	}

	void TerminalRenderer::BuildIndices() {
		// Build the index buffer. This will never change. Note that this DOES send
		// the indices to the GPU.
		unsigned short* buffer = new unsigned short[cells * 6];
		for (int i = 0; i < cells; i++) {
			buffer[i * 6 + 0] = i * 4 + 0;
			buffer[i * 6 + 1] = i * 4 + 1;
			buffer[i * 6 + 2] = i * 4 + 2;
			buffer[i * 6 + 3] = i * 4 + 2;
			buffer[i * 6 + 4] = i * 4 + 3;
			buffer[i * 6 + 5] = i * 4 + 1;
		}

		// Write indices to GPU.
		this->BindIBO(true);
		glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, cells * 6 * sizeof(unsigned short),
			buffer, GL_STATIC_DRAW_ARB);
		this->BindIBO(false);

		delete[] buffer;
	}

	TerminalVertex* TerminalRenderer::GetBaseVertex(int x, int y, int z) {
		if (x >= 0 && x < width && y >= 0 && y < height && z >= 0 && z < depth) {
			int page_offset = z * width * height;
			return &vertices[(page_offset + y * width + x) * 4];
		} else {
			return 0;
		}
	}
}