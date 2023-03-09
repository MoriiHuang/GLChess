#include"VertexArray.h"
VertexArray::VertexArray(/* args */)
{
    GLCALL(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    GLCALL(glDeleteVertexArrays(1,&m_RendererID));
}
void VertexArray::Bind() const{
    GLCALL(glBindVertexArray(m_RendererID));
}
void VertexArray::Unbind() const{
    GLCALL(glBindVertexArray(0));
}
void VertexArray::Addbuffer(const Vertexbuffer& vb, const vertexArrayLayout& layout){
        Bind();
        vb.Bind();
        const auto& elements = layout.get_Element();
        unsigned int offset=0;
        for(int i=0;i<elements.size();i++){
            const auto& element = elements[i]; 
            GLCALL(glEnableVertexAttribArray(i));
            // cout<<i<<" "<<element.count<<" "<<element.type<<" "<<element.normalized<<" "<<layout.get_Stride()<<" "<<offset<<endl;
            GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized,layout.get_Stride(), (const void*) offset));
            offset+=element.count*vertexArrayElement::GetSizeOfType(element.type);
        }
    }