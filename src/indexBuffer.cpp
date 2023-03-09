#include"renderer.h"
#include"indexBuffer.h"
indexBuffer::indexBuffer(const void* data,unsigned int count){
    m_count=count;
    GLCALL(glGenBuffers(1, &m_RendererID);)
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLint)/*in bytes*/, data, GL_STATIC_DRAW));
}
indexBuffer::~indexBuffer(){
    GLCALL(glDeleteBuffers(1,&m_RendererID));
}
void indexBuffer::Bind() const{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}
void indexBuffer::Unbind() const{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}