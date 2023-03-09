#include"renderer.h"
#include"Vertexbuffer.h"
Vertexbuffer::Vertexbuffer(const void* data,unsigned int size){
    GLCALL(glGenBuffers(1, &m_RendererID);)
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size/*in bytes*/, data, GL_STATIC_DRAW));
}
Vertexbuffer::~Vertexbuffer(){
    GLCALL(glDeleteBuffers(1,&m_RendererID));
}
void Vertexbuffer::Bind() const{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void Vertexbuffer::Unbind() const{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}