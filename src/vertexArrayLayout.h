#pragma once
#include<GL/glew.h>
#include<vector>
#include"renderer.h"
#include"Vertexbuffer.h"
struct vertexArrayElement
{
    /* data */
    unsigned int type;
    unsigned int count;
    bool normalized;
    static unsigned int GetSizeOfType(unsigned int type){
        switch (type)
        {
        case GL_FLOAT: return 4; 
        case GL_UNSIGNED_BYTE: return 4; 
        case GL_UNSIGNED_INT: return 4;      
        }
        ASSERT(false);
        return 0;
    }
};
class vertexArrayLayout
{
private:
    /* data */
    std::vector<vertexArrayElement> m_Element;
    unsigned int m_Stride;
public:
    vertexArrayLayout():m_Stride(0){};
    template<typename T> 
    void Push(unsigned int count){
        cout<<"false"<<endl;
    }
    inline unsigned int get_Stride() const{return m_Stride;}
    inline const std::vector<vertexArrayElement> get_Element() const {return m_Element;} 
};
