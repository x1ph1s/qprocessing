#include "batch.hpp"

#include <array>
#include <cstring>

#include "gl.hpp"

constexpr size_t maxVertices = 10000;
constexpr size_t maxIndices  = size_t(maxVertices * 1.5);

namespace {
	using namespace qprocessing::renderer;
	using namespace qprocessing::renderer::batch;

	std::array<Vertex, maxVertices> vertices;
	Vertex* verticesPtr = vertices.data();

	std::array<uint32_t, maxIndices> indices;
	uint32_t* indicesPtr = indices.data();

	uint32_t currentIndex = 0;
	uint32_t numIndices	 = 0;

	unsigned ibo;
	unsigned vbo;
	unsigned vao;
}
namespace qprocessing::renderer {
	void batch::init(void* window) {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxIndices * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, maxVertices * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, r));
	}

	void batch::shutdown() {
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);
	}

	void batch::add(const Vertex* vertices_, size_t vertexCount, const uint32_t* indices_, uint32_t indexCount) {
		numIndices += indexCount;
		if(numIndices > maxIndices || (currentIndex + vertexCount) > maxVertices) {
			numIndices -= indexCount;
			flush();
			numIndices += indexCount;
		}

		std::memcpy(verticesPtr, vertices_, vertexCount * sizeof(Vertex));
		verticesPtr += vertexCount;

		std::memcpy(indicesPtr, indices_, indexCount * sizeof(uint32_t));
		for(size_t i = 0; i < indexCount; ++i) {
			*(indicesPtr + i) += currentIndex;
		}

		indicesPtr += indexCount;
		currentIndex += vertexCount;
	}
	void batch::flush() {
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, numIndices * sizeof(uint32_t), indices.data());
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);

		currentIndex = 0;
		numIndices	 = 0;
		indicesPtr	 = indices.data();
		verticesPtr	 = vertices.data();
	}
}
