#include "vertex_buffer.h"

#include <utility>

namespace qprocessing::core {
	VertexBuffer::VertexBuffer(renderer::Vertex vertices[], size_t numVertices) :
		vertexBuffer{vertices, sizeof(renderer::Vertex) * numVertices} {
		glGenVertexArrays(1, &vao);
		bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(renderer::Vertex), (void*)offsetof(renderer::Vertex, x));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(renderer::Vertex), (void*)offsetof(renderer::Vertex, r));
	}
	VertexBuffer::VertexBuffer(size_t size) :
		vertexBuffer{size * sizeof(Vertex)} {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		vertexBuffer.bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(renderer::Vertex), (void*)offsetof(renderer::Vertex, x));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(renderer::Vertex), (void*)offsetof(renderer::Vertex, r));
	}
	void VertexBuffer::setData(const void* data, size_t dataCount) {
		vertexBuffer.setData(data, dataCount * sizeof(renderer::Vertex));
	}
	VertexBuffer::~VertexBuffer() {
		glDeleteVertexArrays(1, &vao);
	}
	VertexBuffer::VertexBuffer(VertexBuffer&& v) :
		vertexBuffer{std::move(v.vertexBuffer)} {
		if(&v != this) {
			glDeleteVertexArrays(1, &vao);
			vao	= v.vao;
			v.vao = 0;
		}
	}
	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& v) {
		if(&v != this) {
			vertexBuffer = std::move(v.vertexBuffer);
			glDeleteVertexArrays(1, &vao);
			vao	= v.vao;
			v.vao = 0;
		}
		return *this;
	}
	void VertexBuffer::bind() {
		glBindVertexArray(vao);
	}
}
