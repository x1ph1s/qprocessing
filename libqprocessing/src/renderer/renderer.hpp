#pragma once

#include <vector>

#include "const.hpp"

namespace qprocessing::renderer {
	class RenderCall {};

	class MeshCall : public RenderCall {
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

	public:
		MeshCall(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) :
			vertices{std::move(vertices)}, indices{std::move(indices)} {}

		friend void render();
	};

	class BackgroundCall : public RenderCall {
		float r, g, b, a;

	public:
		BackgroundCall(float r, float g, float b, float a) :
			r{r}, g{g}, b{b}, a{a} {}

		friend void render();
	};

	void submit(MeshCall call);
	void submit(BackgroundCall call);

	void render();

	void init(void* window);
	void shutdown();
}
