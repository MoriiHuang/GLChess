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
#define trans_for_glm 180.0f/3.1415926535897932384626433832795f
#define Chess_Row 13
#define Chess_Col 13
#define x_margin 36.82
#define y_margin 36.72
#define Chess_Size 56.27
// std::vector<std::vector<int> > Init_Chess(){
// 	std::vector<std::vector<int> > Chess_Map;
// 	for(int i=0;i<Chess_Col;i++){
// 		vector<int> Row;
// 		for(int i=0;i<Chess_Row;i++){
// 			Row.push_back(0);
// 		}
// 		Chess_Map.push_back(Row);
// 	}
// 	return Chess_Map;
// }
// std::vector<pair<double,double> > Chess_transform; 
// std::vector<std::vector<int> > Chess_Map=Init_Chess();

// Camera camera(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0f, 1.0f, 0.0f));
// void mouse_callback(GLFWwindow* window, double xpos, double ypos){
// 	camera.ProcessMouseMovement(window,xpos,ypos);
// }
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
// 	camera.ProcessMouseScroll(window,yoffset);
// }
// void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// static void mouse_Click_callback(GLFWwindow* window,int button,int action,int mods){
// 	if (action == GLFW_PRESS) switch (button)
// 	{
// 	case GLFW_MOUSE_BUTTON_LEFT:
// 		double x;
// 		double y;
// 		glfwGetCursorPos(window,&x,&y);
// 		int col =(x-x_margin)/Chess_Size;
// 		int row = (y-y_margin)/Chess_Size;
// 		int leftTopPosX = x_margin + Chess_Size*col;
// 		int leftTopPosY = y_margin + Chess_Size*row;
// 		int offset = Chess_Size *0.4;

// 		int distance = sqrt((x-leftTopPosX)*(x-leftTopPosX)+(y-leftTopPosY)*(y-leftTopPosY));
// 		if (distance < offset){
// 		if (Chess_Map[row][col]==0){
// 		pair<double,double>s(leftTopPosX,leftTopPosY);
// 		Chess_Map[row][col]=1;
// 		Chess_transform.push_back(s);}
// 		}
// 		int x2=leftTopPosX;
// 		int y2=leftTopPosY+Chess_Size;
// 		distance =	sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
// 		if (distance < offset){
// 		if (Chess_Map[row+1][col]==0){
// 		pair<double,double>s(x2,y2);
// 		Chess_Map[row+1][col]=1;
// 		Chess_transform.push_back(s);}
// 		}
// 		int x3=leftTopPosX+Chess_Size;
// 		int y3=leftTopPosY;
// 		distance =	sqrt((x-x3)*(x-x3)+(y-y3)*(y-y3));
// 		if (distance < offset){
// 		if (Chess_Map[row][col+1]==0){
// 		pair<double,double>s(x3,y3);
// 		Chess_Map[row][col+1]=1;
// 		Chess_transform.push_back(s);}
// 		}
// 		int x4=leftTopPosX+Chess_Size;
// 		int y4=leftTopPosY+Chess_Size;
// 		distance =	sqrt((x-x4)*(x-x4)+(y-y4)*(y-y4));
// 		if (distance < offset){
// 		if (Chess_Map[row+1][col+1]==0){
// 		pair<double,double>s(x4,y4);
// 		Chess_Map[row+1][col+1]=1;
// 		Chess_transform.push_back(s);}
// 		}
// 		break;
// 	}

// }
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
	// glfwSetCursorPosCallback(window,mouse_callback);
    // glfwSetScrollCallback(window,scroll_callback);
	// glfwSetMouseButtonCallback(window,mouse_Click_callback);
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
	GLCALL(Texture texture2("/Users/lucifer/Desktop/大二下/wuziqi/res/textures/12.jpg"))
	float r=0.0f;
	float increament =0.05f;
	Renderer renderer;
	Man man(window,chessva,sd,renderer);
	glEnable(GL_DEPTH_TEST);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		// renderer.Clear(0.2f, 0.3f, 0.3f, 1.0f);
		renderer.Clear();
		camera.processInput(window);
		GLCALL(texture.Bind());
		GLCALL(texture2.Bind(1));
		GLCALL(sd.SetUniform1i("u_Texture",0));
		GLCALL(sd.SetUniform1i("u_Chess_Black",1));
		glm::mat4 model;
		sd.SetUniform1i("flag",0);
		sd.SetUniformMat4("u_MVP",model);
		GLCALL(renderer.Draw(va,ib,sd));

		for(int i=0;i<Chess_transform.size();i++){
			model=glm::mat4(1);
			double x=2*Chess_transform[i].first/750 -1;
			double y=1-(2*Chess_transform[i].second/750);
			glm::vec3 move=glm::vec3(x,y,0.0f);
			model = glm::translate(model,move);
			sd.SetUniform1i("flag",1);
			sd.SetUniformMat4("u_MVP",model);
			GLCALL(renderer.Draw(chessva,ib,sd));
		}
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		// /* Poll for and process events */
		glfwPollEvents();
	}
 
	glfwTerminate();
	return 0;
	
}
