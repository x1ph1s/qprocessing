#include "qprocessing.h"

#include <cmath>
#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>

#include "renderer/renderer.hpp"

#define QPR_EXTRACT_COLOR(color) red(color) / 255.0f, green(color) / 255.0f, blue(color) / 255.0f, alpha(color) / 255.0f

namespace {
	using namespace qprocessing;

	struct vec3 {
		float x, y, z;
	};
	qprocessing::color currentColor{255, 255, 255};

	GLFWwindow* window;
	void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
}

int main(){
	glfwInit();
	window = glfwCreateWindow(1, 1, "", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	renderer::init(window);

	renderer::clear();
	setup();
	glfwSwapBuffers(window);
	renderer::clear();
	setup();

	while(!glfwWindowShouldClose(window)) {
		renderer::clear();

		draw();

		renderer::flush();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	renderer::shutdown();
	glfwTerminate();
}

namespace qprocessing {
	void size(int width, int heigth) {
		glfwSetWindowSize(window, width, heigth);
	}

	void background(color c) {
		renderer::clearColor(QPR_EXTRACT_COLOR(c));
		renderer::clear();
	}
	void background(color c, int alpha) {
		renderer::clearColor(red(c) / 255.0f, green(c) / 255.0f, blue(c) / 255.0f, alpha / 255.0f);
		renderer::clear();
	}
	void background(int gray, int alpha) {
		renderer::clearColor(gray / 255.0f, gray / 255.0f, gray / 255.0f, alpha / 255.0f);
		renderer::clear();
	}
	void background(int v1, int v2, int v3, int a) {
		renderer::clearColor(v1 / 255.0f, v2 / 255.0f, v3 / 255.0f, a / 255.0f);
		renderer::clear();
	}

	void circle(float xPos, float yPos, float r) {
		ellipse(xPos, yPos, r, r);
	}

	void ellipse(float xPos, float yPos, float w, float h) {
		std::vector<renderer::Vertex> circleVertices;
		constexpr int numPoints = 200;

		circleVertices.reserve(numPoints + 1);
		circleVertices.emplace_back(xPos, yPos, 0, QPR_EXTRACT_COLOR(currentColor));

		for(int i = 0; i < numPoints; i++) {
			float a = (float)i / numPoints;
			float x = std::cos(a * M_PI * 2) * w + xPos;
			float y = std::sin(a * M_PI * 2) * h + yPos;
			circleVertices.emplace_back(x, y, 0, QPR_EXTRACT_COLOR(currentColor));
		}
		std::vector<uint32_t> circleIndices;
		circleIndices.reserve(numPoints * 3);
		for(int i = 1; i < numPoints; i++) {
			circleIndices.push_back(0);
			circleIndices.push_back(i);
			circleIndices.push_back(i + 1);
		}

		circleIndices.push_back(0);
		circleIndices.push_back(numPoints);
		circleIndices.push_back(1);

		renderer::add(circleVertices.data(), circleVertices.size(), circleIndices.data(), circleIndices.size());
	}
	void line(float x1, float y1, float x2, float y2) {
		constexpr float thickness = 0.0001;
		float vx						  = x2 - x1;
		float vy						  = y2 - y1;
		float len					  = std::sqrt(vx * vx + vy * vy);
		vx /= len;
		vy /= len;
		float temp = vx;
		vx			  = -vy;
		vy			  = temp;
		vx *= thickness;
		vy *= thickness;

		std::vector<renderer::Vertex> lineVertices{
			renderer::Vertex{
				x1 + vx, y1 + vy, QPR_EXTRACT_COLOR(currentColor)},
			renderer::Vertex{
				x1 - vx, y1 - vy, QPR_EXTRACT_COLOR(currentColor)
			},
			renderer::Vertex{
				x2 + vx, y2 + vy, QPR_EXTRACT_COLOR(currentColor)},
			renderer::Vertex{
				x2 - vx, y2 - vy, QPR_EXTRACT_COLOR(currentColor)

			}};
		std::vector<uint32_t> lineIndices{
			0, 1, 2,
			2, 3, 1};

		renderer::add(lineVertices.data(), lineVertices.size(), lineIndices.data(), lineIndices.size());
	}
	void point(float x, float y) {
		circle(x, y, 0.005);
	}
	void rect(float x, float y, float w, float h) {
		float halfw = w / 2;
		float halfh = h / 2;

		vec3 topLeft{x - halfw, y + halfh, 0};
		vec3 topRight{x + halfw, y + halfh, 0};
		vec3 bottonleft{x - halfw, y - halfh, 0};
		vec3 bottonRight{x + halfw, y - halfh, 0};

		std::vector<renderer::Vertex> rectVertices{
			renderer::Vertex{
				topLeft.x, topLeft.y, 0, QPR_EXTRACT_COLOR(currentColor)},
			renderer::Vertex{
				topRight.x, topRight.y, 0, QPR_EXTRACT_COLOR(currentColor)

			},
			renderer::Vertex{
				bottonleft.x, bottonleft.y, 0, QPR_EXTRACT_COLOR(currentColor)

			},
			renderer::Vertex{
				bottonRight.x, bottonRight.y, 0, QPR_EXTRACT_COLOR(currentColor)

			}};
		std::vector<uint32_t> rectIndices{
			0, 1, 2,
			2, 3, 1};

		renderer::add(rectVertices.data(), rectVertices.size(), rectIndices.data(), rectIndices.size());
	}
	void square(float x, float y, float e) {
		rect(x, y, e, e);
	}

	void fill(color c) {
		currentColor = c;
	}
	void fill(color c, int alpha) {
		currentColor = color(red(c), green(c), blue(c), alpha);
	}
	void fill(int gray, int a) {
		currentColor = color(gray, a);
	}
	void fill(int v1, int v2, int v3, int a) {
		currentColor = color(v1, v2, v3, a);
	}

	void terminate() {
		glfwSetWindowShouldClose(window, true);
	}
}
