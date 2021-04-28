#pragma once

#include <fstream>
#include <sstream>

#include "gl.h"

namespace qprocessing::core {
	class Shader {
		GLuint shaderId;

	public:
		Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
		~Shader();

		void bind();
		GLuint getShaderId();
	};
}
