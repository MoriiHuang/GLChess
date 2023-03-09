#include"vertexArrayLayout.h"
template<>
void vertexArrayLayout::Push<float>(unsigned int count){
    vertexArrayElement ve;
    ve.count=count; ve.normalized=GL_FALSE;ve.type=GL_FLOAT;
    m_Stride+=count*sizeof(GLfloat);
    m_Element.push_back(ve);
}
template<>
void vertexArrayLayout::Push<unsigned int>(unsigned int count){
    vertexArrayElement ve;
    ve.count=count; ve.normalized=GL_FALSE;ve.type=GL_UNSIGNED_INT;
    m_Element.push_back(ve);
    m_Stride+=count*sizeof(GLuint);
}
template<>
void vertexArrayLayout::Push<unsigned char>(unsigned int count){
    vertexArrayElement ve;
    ve.count=count; ve.normalized=GL_TRUE;ve.type=GL_UNSIGNED_BYTE;
    m_Element.push_back(ve);
    m_Stride+=count*sizeof(GLbyte);
}