#pragma once

#include "buffer.h"
#include "gl.h"
#include "renderer.h"

namespace qprocessing::core {
	class VertexBuffer {
		Buffer<GL_ARRAY_BUFFER> vertexBuffer;
		GLuint vao;

	public:
		VertexBuffer(renderer::Vertex vertices[], size_t numVertices);
		VertexBuffer(size_t maxVertices);
		void bind();
		void setData(const void* data, size_t dataCount);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer& v) = delete;
		VertexBuffer& operator=(const VertexBuffer& v) = delete;
		VertexBuffer(VertexBuffer&& v);
		VertexBuffer& operator=(VertexBuffer&& v);
	};
}
