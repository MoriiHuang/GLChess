#pragma once
#include<GL/glew.h>
// #include"renderer.h"
#include"vertexArrayLayout.h"
class VertexArray
{
private:
    /* data */
    unsigned int m_RendererID;
public:
    VertexArray(/* args */);
    ~VertexArray();
    void Addbuffer(const Vertexbuffer& vb, const vertexArrayLayout& layout);
    void Bind() const;
    void Unbind() const;
};
