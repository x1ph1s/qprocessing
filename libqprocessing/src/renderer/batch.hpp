#pragma once

#include "const.hpp"

namespace qprocessing::renderer::batch {
	void add(const Vertex* vertices, size_t vertexCount, const uint32_t* indices, uint32_t indexCount);
	void flush();

	void init(void* window);
	void shutdown();
}
