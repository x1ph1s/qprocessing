#pragma once
#include "buffer.h"

#include "gl.h"

namespace qprocessing::core{
    class IndexBuffer : private Buffer<GL_ELEMENT_ARRAY_BUFFER>{
        uint32_t numIndices;
    public:
        IndexBuffer(uint32_t indices[],uint32_t nunIndices);
        IndexBuffer(size_t count);

        IndexBuffer(const IndexBuffer& i) = delete;
        IndexBuffer& operator= (const IndexBuffer& i) = delete;
        IndexBuffer(IndexBuffer&& i);
        IndexBuffer& operator= (IndexBuffer&& i);

        void bind();
        void setData(const uint32_t* data,size_t count);

        uint32_t getIndices();
    };
}
