#pragma once

#include <cinttypes>
#include <cstddef>

namespace qprocessing::core{
    inline namespace renderer{
        struct Vertex{
            float x=0;
            float y=0;
            float z=0;

            float r=1;
            float g=1;
            float b=1;
            float a=1;
        };

        void add(const Vertex* vertices,size_t vertexCount,const uint32_t* indices,uint32_t indexCount);
        void flush();

        void clearColor(float r,float g,float b,float a);
        void clear();

        void init(void* window);
        void shutdown();
    }
}
