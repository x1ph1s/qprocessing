#include "renderer.h"

#include <array>
#include <cstring>

#include "gl.h"
#include "shader.h"
#include "shadercode.h"

constexpr size_t maxVertices = 10000;
constexpr size_t maxIndices  = size_t(maxVertices * 1.5);

namespace {
	using namespace qprocessing::core;

	std::array<Vertex, maxVertices> vertices;
	Vertex* verticesPtr = vertices.data();

	std::array<uint32_t, maxIndices> indices;
	uint32_t* indicesPtr = indices.data();

	uint32_t currentIndex = 0;
	uint32_t numIndices	 = 0;

	unsigned ibo;
	unsigned vbo;
	unsigned vao;

#ifdef DEBUG
	void _glMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		std::cout << message << "\n";
	}
#endif
}
namespace qprocessing::core {
	void renderer::init(void* window) {
		GLenum err = glewInit();
#ifdef DEBUG
		if(err != GLEW_OK) {
			std::cerr << "Error with glew: " << glewGetErrorString(err) << "\n";
			return;
		}
#endif

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

#ifdef DEBUG
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(_glMessageCallback, nullptr);
#endif

		glClearColor(0.1, 0.1, 0.1, 1);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Shader shader{vertexShaderSourceString, fragmantShaderSourceString};
		shader.bind();
	}

	void renderer::shutdown() {
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);
	}

	void renderer::add(const Vertex* vertices_, size_t vertexCount, const uint32_t* indices_, uint32_t indexCount) {
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
	void renderer::flush() {
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, numIndices * sizeof(uint32_t), indices.data());
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);

		currentIndex = 0;
		numIndices	 = 0;
		indicesPtr	 = indices.data();
		verticesPtr	 = vertices.data();
	}

	void renderer::clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void renderer::clearColor(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}
}
