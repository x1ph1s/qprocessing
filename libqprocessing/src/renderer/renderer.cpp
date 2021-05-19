#include "renderer.hpp"

#include <iostream>
#include <memory>
#include <vector>

#include "batch.hpp"
#include "gl.hpp"
#include "shader.hpp"
#include "shadercode.hpp"

namespace {
	using namespace qprocessing::renderer;

	unsigned shader;

#ifdef DEBUG
	void _glMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		std::cout << message << "\n";
	}
#endif

	std::vector<MeshCall> meshCalls;
	std::unique_ptr<BackgroundCall> backgroundCall{nullptr};
}

namespace qprocessing {
	void renderer::init(void* window) {
		GLenum err = glewInit();
#ifdef DEBUG
		if(err != GLEW_OK) {
			std::cerr << "Error with glew: " << glewGetErrorString(err) << "\n";
			return;
		}
#endif

#ifdef DEBUG
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(_glMessageCallback, nullptr);
#endif

		glClearColor(0, 0, 0, 1);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		shader = createShader(vertexShaderSource, fragmentShaderSource);
		glUseProgram(shader);

		batch::init(window);
	}

	void renderer::shutdown() {
		glDeleteProgram(shader);
		batch::shutdown();
	}

	void renderer::submit(MeshCall call) {
		meshCalls.push_back(call);
	}
	void renderer::submit(BackgroundCall call) {
		meshCalls.clear();
		backgroundCall = std::make_unique<BackgroundCall>(call);
	}

	void renderer::copyRenderQueue(renderer::CopyRenderQueueOption option) {
		static std::unique_ptr<BackgroundCall> backgroundCallBackup{nullptr};
		static std::vector<MeshCall> meshCallsBackup;
		if(option == CopyRenderQueueOption::QUEUE_TO_BACKUP) {
			if(backgroundCall) {
				backgroundCallBackup = std::make_unique<BackgroundCall>(*backgroundCall);
			}
			meshCallsBackup = meshCalls;
		}
		else if(option == CopyRenderQueueOption::BACKUP_TO_QUEUE) {
			backgroundCall = std::move(backgroundCallBackup);
			meshCalls		= std::move(meshCallsBackup);
		}
	}

	void renderer::render() {
		glClear(GL_COLOR_BUFFER_BIT);
		if(backgroundCall) {
			glClearColor(backgroundCall->r, backgroundCall->g, backgroundCall->b, backgroundCall->a);
		}

		for(auto& i : meshCalls) {
			batch::add(i.vertices.data(), i.vertices.size(), i.indices.data(), i.indices.size());
		}

		batch::flush();
	}
}
