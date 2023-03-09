// modified,shader.h,Chess.cpp,Chess.h,Man.h,Ai.h
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<fstream>
#include<sstream>
#include<string>
#include"renderer.h"
#include"indexBuffer.h"
#include"VertexArray.h"
#include"shader.h"
#include<cmath>
#include"Texture.h"
#include"glCamera.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include"Man.h"
#include"AI.h"
int initial(){
	if (!glfwInit())
		return -1;
	/* Create a windowed mode window and its OpenGL context */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // for Mac OS X
	return 1;
}
int main(void)
{	
	if (!initial()){ return -1;}
	GLFWwindow* window = glfwCreateWindow(750, 750, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwWindowHint(GLFW_REFRESH_RATE, 60);
    glewExperimental = GL_TRUE;
	glewInit();
	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;
	cout << glGetString(GL_VERSION) <<endl;
	/* Initialize the library */
	float positions[] = {
		-1.0f, -1.0f,1.0f,0.0f,0.0f,
         1.0f, -1.0f,1.0f, 1.0f,0.0f,
		 1.0f, 1.0f,0.0f, 1.0f,1.0f,
         -1.0f, 1.0f,0.0f, 0.0f,1.0f
	}; 
	float Chess_Position[]={
		-0.045f, -0.045f,0.1f,0.0f,0.0f,
         0.045f, -0.045f,0.1f, 1.0f,0.0f,
		 0.045f, 0.045f,0.0f, 1.0f,1.0f,
         -0.045f, 0.045f,0.0f, 0.0f,1.0f
	};
	GLint indices[]={
		0,1,2,
		2,3,0
	};
	glEnable(GL_BLEND);
	GLCALL(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));
	VertexArray va;
	Vertexbuffer vb(positions,sizeof(positions));
	vertexArrayLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	va.Addbuffer(vb,layout);
	VertexArray chessva;
	Vertexbuffer chessvb(Chess_Position,sizeof(Chess_Position));
	vertexArrayLayout Chesslayout;
	Chesslayout.Push<float>(3);
	Chesslayout.Push<float>(2);
	chessva.Addbuffer(chessvb,Chesslayout);
	indexBuffer ib(indices,6);
	GLCALL(shader sd("/Users/lucifer/Desktop/大二下/wuziqi/res/shaders/chess.shader"));
	GLCALL(sd.SetUniform4f("u_Color",0.2f,0.3f,0.8f,1.0f));
	GLCALL(Texture texture("/Users/lucifer/Desktop/大二下/wuziqi/res/textures/10.jpg"));
	GLCALL(Texture texture2("/Users/lucifer/Desktop/大二下/wuziqi/res/textures/12.jpg"));
	GLCALL(Texture texture3("/Users/lucifer/Desktop/大二下/wuziqi/res/textures/11.jpg"));
	GLCALL(Texture texture4("/Users/lucifer/Desktop/大二下/wuziqi/res/textures/甘雨伞.jpg"));
	float r=0.0f;
	float increament =0.05f;
	Renderer renderer;
	Man man(window);
	AI ai;
	glEnable(GL_DEPTH_TEST);
	GLCALL(sd.SetUniform3f("iResolution",750,750,750*750));
	float time=0;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		// renderer.Clear(0.2f, 0.3f, 0.3f, 1.0f);
		renderer.Clear();
		if(time<1 and start_switch==1){
		time+=0.01;}
		sd.SetUniform1f("iTime",time);
		camera.processInput(window);
		GLCALL(texture.Bind());
		GLCALL(texture2.Bind(1));
		GLCALL(texture3.Bind(2));
		GLCALL(texture4.Bind(3));
		GLCALL(sd.SetUniform1i("u_Texture",0));
		GLCALL(sd.SetUniform1i("u_Chess_Black",1));
		GLCALL(sd.SetUniform1i("u_Chess_White",2));
		GLCALL(sd.SetUniform1i("u_Texture_2",3));
		glm::mat4 model;
		sd.SetUniform1i("flag",0);
		sd.SetUniformMat4("u_MVP",model);
		GLCALL(renderer.Draw(va,ib,sd));
		bool flag =1;
		man.go(chessva,ib,sd,renderer);
		if(man_win){
			man_win=0;
			ai_win=0;
			flag_man=0;
			flag_ai=0;
			sd.SetUniform1i("flag",0);
			start_switch=0;
			for(int i=0;i<Chess_Col;i++){
            for(int j=0;j<Chess_Row;j++){
                Chess_Map[i][j]=0;
            }
        }   
		}
		ai.go(chessva,ib,sd,renderer);
		if(ai_win){
			man_win=0;
			ai_win=0;
			flag_man=0;
			flag_ai=0;
			sd.SetUniform1i("flag",0);
			start_switch=0;
			for(int i=0;i<Chess_Col;i++){
            for(int j=0;j<Chess_Row;j++){
                Chess_Map[i][j]=0;
            }
        }   
		}
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		// /* Poll for and process events */
		glfwPollEvents();
	}
 
	glfwTerminate();
	return 0;
	
}
