#include "TerminalRenderer.h"
#include "Character.h"
#include "TProgram.h"
#include <glew/glew.h>

namespace halt {
	const int VERTICES_PER_CELL = 4;
	const int INDICES_PER_CELL = 6;

	TerminalRenderer::TerminalRenderer(int cellsw, int cellsh, int cellsd, const CharacterSize& cdim)
		: width(cellsw), height(cellsh), depth(cellsd), ch_size(cdim) {
		glGenBuffers(1, &vb_handle);
		glGenBuffers(1, &ib_handle);

		// Allocate enough vertices to hold all of the cells in the terminal on all layers.
		cells = width * height * depth;
		vertices = new TerminalVertex[cells * sizeof(TerminalVertex) * VERTICES_PER_CELL];

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
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, VERTICES_PER_CELL * width * height * sizeof(TerminalVertex),
				(vertices + width * height * VERTICES_PER_CELL * z), GL_STREAM_DRAW_ARB);

			glDrawRangeElements(
				GL_TRIANGLES,
				INDICES_PER_CELL * width * height * z,
				INDICES_PER_CELL * width * height * z + INDICES_PER_CELL * width * height,
				INDICES_PER_CELL * width * height,
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
				vertices[(page_offset + i) * VERTICES_PER_CELL + 0].x = cdim.width  * (i % width);
				vertices[(page_offset + i) * VERTICES_PER_CELL + 0].y = cdim.height * (i / width);
				vertices[(page_offset + i) * VERTICES_PER_CELL + 1].x = cdim.width  * (i % width) + cdim.width;
				vertices[(page_offset + i) * VERTICES_PER_CELL + 1].y = cdim.height * (i / width);
				vertices[(page_offset + i) * VERTICES_PER_CELL + 2].x = cdim.width  * (i % width);
				vertices[(page_offset + i) * VERTICES_PER_CELL + 2].y = cdim.height * (i / width) + cdim.height;
				vertices[(page_offset + i) * VERTICES_PER_CELL + 3].x = cdim.width  * (i % width) + cdim.width;
				vertices[(page_offset + i) * VERTICES_PER_CELL + 3].y = cdim.height * (i / width) + cdim.height;
			}
		}
	}

	void TerminalRenderer::BuildIndices() {
		// Build the index buffer. This will never change. Note that this DOES send
		// the indices to the GPU.
		unsigned short* buffer = new unsigned short[cells * INDICES_PER_CELL];
		for (int i = 0; i < cells; i++) {
			buffer[i * INDICES_PER_CELL + 0] = i * VERTICES_PER_CELL + 0;
			buffer[i * INDICES_PER_CELL + 1] = i * VERTICES_PER_CELL + 1;
			buffer[i * INDICES_PER_CELL + 2] = i * VERTICES_PER_CELL + 2;
			buffer[i * INDICES_PER_CELL + 3] = i * VERTICES_PER_CELL + 2;
			buffer[i * INDICES_PER_CELL + 4] = i * VERTICES_PER_CELL + 3;
			buffer[i * INDICES_PER_CELL + 5] = i * VERTICES_PER_CELL + 1;
		}

		// Write indices to GPU.
		this->BindIBO(true);
		glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, cells * INDICES_PER_CELL * sizeof(unsigned short),
			buffer, GL_STATIC_DRAW_ARB);
		this->BindIBO(false);

		delete[] buffer;
	}

	TerminalVertex* TerminalRenderer::GetBaseVertex(int x, int y, int z) {
		if (x >= 0 && x < width && y >= 0 && y < height && z >= 0 && z < depth) {
			int page_offset = z * width * height;
			return &vertices[(page_offset + y * width + x) * VERTICES_PER_CELL];
		} else {
			return 0;
		}
	}
}