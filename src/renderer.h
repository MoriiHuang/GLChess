#pragma once
#include <iostream>
#include<GL/glew.h>
#include<vector>
#include<unordered_map>
class VertexArray;
class indexBuffer;
class shader;
#define ASSERT(x) if (!(x)) __builtin_trap() ;
#define GLCALL(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x,__FILE__,__LINE__));
#define trans_for_glm 180.0f/3.1415926535897932384626433832795f
#define Chess_Row 13
#define Chess_Col 13
#define x_margin 36.82
#define y_margin 36.72
#define Chess_Size 56.27
using namespace std;
void GLClearError();
bool GLLogCall(string function, string file, int line);
class Renderer{
    public:
    void Draw(const VertexArray& va, const indexBuffer& ib, const shader& sd);
    void Draw(const VertexArray& va, const shader& sd);
    void Clear() const{
        GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }
    void Clear(float v1,float v2, float v3,float v4) const{
        GLCALL(glClearColor(v1,v2,v3,v4));
    }
};
std::vector<std::vector<int> > Init_Chess();