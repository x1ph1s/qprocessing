#pragma once

#include "gl.h"

namespace qprocessing::core {
	template<GLenum bufferType>
	class Buffer {
		GLuint bufferId;

	public:
		Buffer(const void* data, size_t dataSize) {
			glGenBuffers(1, &bufferId);
			bind();
			glBufferData(bufferType, dataSize, data, GL_STATIC_DRAW);
		}
		Buffer(size_t size) {
			glGenBuffers(1, &bufferId);
			bind();
			glBufferData(bufferType, size, nullptr, GL_DYNAMIC_DRAW);
		}
		~Buffer() {
			glDeleteBuffers(1, &bufferId);
		}

		Buffer(const Buffer& i) = delete;
		Buffer& operator=(const Buffer& i) = delete;
		Buffer(Buffer&& i) {
			if(&i != this) {
				glDeleteBuffers(1, &bufferId);
				bufferId	  = i.bufferId;
				i.bufferId = 0;
			}
		}
		Buffer& operator=(Buffer&& i) {
			if(&i != this) {
				glDeleteBuffers(1, &bufferId);
				bufferId	  = i.bufferId;
				i.bufferId = 0;
			}
			return *this;
		}

		void bind() {
			glBindBuffer(bufferType, bufferId);
		}
		void setData(const void* data, size_t dataSize) {
			bind();
			glBufferSubData(bufferType, 0, dataSize, data);
		}
	};
}
