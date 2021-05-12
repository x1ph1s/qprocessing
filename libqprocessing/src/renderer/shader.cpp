#include "shader.hpp"

#include <iostream>

#include "gl.hpp"

namespace {
	GLuint compile(const char* shaderSource, GLenum type) {
		GLuint id = glCreateShader(type);

		glShaderSource(id, 1, &shaderSource, 0);
		glCompileShader(id);

#ifdef DEBUG
		int err = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &err);
		if(err != GL_TRUE) {
			int length = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char buffer[length];
			glGetShaderInfoLog(id, length, &length, buffer);

			std::cerr << "[Shadererror]" << buffer << "\n";
		}
#endif

		return id;
	}
}

namespace qprocessing::renderer {
	unsigned createShader(const char* vertexShaderSource, const char* fragmentShaderSource) {
		GLuint program = glCreateProgram();

		GLuint vs = compile(vertexShaderSource, GL_VERTEX_SHADER);
		GLuint fs = compile(fragmentShaderSource, GL_FRAGMENT_SHADER);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);

#ifdef RELEASE
		glDetachShader(program, vs);
		glDetachShader(program, fs);
		glDeleteShader(vs);
		glDeleteShader(fs);
#endif

		return program;
	}
}
