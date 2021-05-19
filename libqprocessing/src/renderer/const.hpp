#pragma once

#include <cinttypes>
#include <cstddef>

namespace qprocessing::renderer{
	struct Vertex {
		float x = 0;
		float y = 0;
		float z = 0;

		float r = 1;
		float g = 1;
		float b = 1;
		float a = 1;
	};
}
