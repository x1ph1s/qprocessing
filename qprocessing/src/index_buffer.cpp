#include "index_buffer.h"

#include <iostream>
#include <vector>

namespace qprocessing::core {
	IndexBuffer::IndexBuffer(uint32_t indices[], uint32_t numIndices) :
		numIndices{numIndices}, Buffer{indices, numIndices * sizeof(uint32_t)} {}
	IndexBuffer::IndexBuffer(size_t count) :
		Buffer{count * sizeof(uint32_t)} {
	}
	IndexBuffer::IndexBuffer(IndexBuffer&& i) :
		Buffer{std::move(i)} {
		if(&i != this) {
			numIndices = i.numIndices;
		}
	}
	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& i) {
		if(&i != this) {
			numIndices = i.numIndices;
		}
		return *this;
	}

	void IndexBuffer::bind() {
		Buffer::bind();
	}
	void IndexBuffer::setData(const uint32_t* data, size_t count) {
		Buffer::setData(data, count * sizeof(uint32_t));
	}

	uint32_t IndexBuffer::getIndices() {
		return numIndices;
	}
}
