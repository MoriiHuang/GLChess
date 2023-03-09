#include"renderer.h"
#include"VertexArray.h"
#include"shader.h"
#include"indexBuffer.h"
void GLClearError(){
	while(glGetError()!=GL_NO_ERROR);
}
bool GLLogCall(string function, string file, int line){
	while(GLenum error =glGetError()){
		cout<<"[OpenGL error] ("<<error<<")"<<" "<<function<<" "<<file<<" "<<line<<endl;
		return false;
	}
	return true;
}
void Renderer::Draw(const VertexArray& va, const indexBuffer& ib, const shader& sd){
	va.Bind();
    ib.Bind();
    sd.Bind();
	GLCALL(glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr));
}
void Renderer::Draw(const VertexArray& va, const shader& sd){
	va.Bind();
    sd.Bind();
	GLCALL(glDrawArrays(GL_TRIANGLES, 0, 36));
}
