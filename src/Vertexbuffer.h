#pragma once
class Vertexbuffer
{
private:
    /* data */
    unsigned int m_RendererID;
public:
    Vertexbuffer(const void* data,unsigned int size);
    ~Vertexbuffer();
    void Bind() const;
    void Unbind() const;
};

