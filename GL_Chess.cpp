#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<fstream>
#include<sstream>
#include<string>
#include"renderer.h"
#include"indexBuffer.h"
#include"VertexArray.h"
#include"shader.h"
#include"Texture.h"
#include"glCamera.h"
#include"skybox.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#define trans_for_glm 180.0f/3.1415926535897932384626433832795f
Camera camera(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0f, 1.0f, 0.0f));
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
	camera.ProcessMouseMovement(window,xpos,ypos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	camera.ProcessMouseScroll(window,yoffset);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
static void mouse_callback(GLFWwindow* window,int button,int action,int mods){
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		double x;
		double y;
		glfwGetCursorPos(window,&x,&y);
		
		break;
	
	default:
		break;
	}

}
int initial(){
	if (!glfwInit())
		return -1;
	/* Create a windowed mode window and its OpenGL context */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // for Mac OS X
	return 1;
}
int main(void)
{	
	if (!initial()){ return -1;}
	GLFWwindow* window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window,mouse_callback);
    glfwSetScrollCallback(window,scroll_callback);
	// glfwSetMouseButtonCallback(window,mouse_callback);
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwWindowHint(GLFW_REFRESH_RATE, 60);
	glfwSwapInterval(1);
    glewExperimental = GL_TRUE;
	glewInit();
	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;
	cout << glGetString(GL_VERSION) <<endl;
	/* Initialize the library */
	// float positions[] = {
	// 	-0.5f, -0.5f,0.0f,0.0f,0.0f,
    //      0.5f, -0.5f,0.0f, 1.0f,0.0f,
	// 	 0.5f, 0.5f,0.0f, 1.0f,1.0f,
    //      -0.5f, 0.5f,0.0f, 0.0f,1.0f
	// }; 
	float positions[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f};
	float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

	// GLint indices[]={
	// 	0,1,2,
	// 	2,3,0
	// }
	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f), 
		glm::vec3( 2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
		glm::vec3(-3.8f, -2.0f, -12.3f),  
		glm::vec3( 2.4f, -0.4f, -3.5f),  
		glm::vec3(-1.7f,  3.0f, -7.5f),  
		glm::vec3( 1.3f, -2.0f, -2.5f),  
		glm::vec3( 1.5f,  2.0f, -2.5f), 
		glm::vec3( 1.5f,  0.2f, -1.5f), 
		glm::vec3(-1.3f,  1.0f, -1.5f)  
};
	string tmp[]={"right.jpg","left.jpg","top.jpg","bottom.jpg","front.jpg","back.jpg"};
	vector<string> faces(tmp,tmp+6);
	glEnable(GL_BLEND);
	GLCALL(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));
	unsigned int cubemapTexture = loadCubemap(faces);
	VertexArray skyboxvao;
	Vertexbuffer skyboxvb(skyboxVertices,sizeof(skyboxVertices));
	vertexArrayLayout skyboxlayout;
	skyboxlayout.Push<float>(3);
	skyboxvao.Addbuffer(skyboxvb,skyboxlayout);
	VertexArray va;
	Vertexbuffer vb(positions,sizeof(positions));
	vertexArrayLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	va.Addbuffer(vb,layout);
	// indexBuffer ib(indices,6);
	GLCALL(shader sd("/Users/lucifer/Desktop/大二下/wuziqi/res/shaders/basic.shader"));

	sd.SetUniform4f("u_Color",0.2f,0.3f,0.8f,1.0f);
	GLCALL(Texture texture("/Users/lucifer/Desktop/大二下/wuziqi/res/textures/11.jpg"));
	GLCALL(Texture texture2("/Users/lucifer/Desktop/大二下/wuziqi/res/textures/12.jpg"));
	float r=0.0f;
	float increament =0.05f;
	Renderer renderer;
	glm::mat4 proj=glm::mat4(1.0f);
	proj = glm::rotate(proj, glm::radians(-55.0f*trans_for_glm), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view;
	// view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projection;
	glEnable(GL_DEPTH_TEST);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		// renderer.Clear(0.2f, 0.3f, 0.3f, 1.0f);
		renderer.Clear();
		camera.processInput(window);
		view=camera.LookAt();
		texture.Bind();
		sd.SetUniform1i("u_Texture",0);
		texture2.Bind(1);
		sd.SetUniform1i("u_Texture1",1);
		GLCALL(glActiveTexture(GL_TEXTURE0+2));
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		sd.SetUniform1i("skybox",2);
		sd.SetUniform1i("flag",0);
		projection = glm::perspective(glm::radians(camera.getZoom()*trans_for_glm),(float) 800 / 800, 0.1f, 100.0f);
		sd.SetUniform4f("u_Color",r,0.3f,0.8f,1.0f);
		sd.SetUniformMat4("u_View",view);
		sd.SetUniformMat4("u_Projection",projection);
		sd.SetUniformMat4("u_MVP",proj);
		for(unsigned int i = 1; i < 11; i++)
		{
		glm::mat4 model;
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i; 
		model = glm::rotate(model, (float)glfwGetTime()*glm::radians(angle)*trans_for_glm/10, glm::vec3(1.0f, 0.3f, 0.5f));
		sd.SetUniformMat4("u_MVP",model);
		if (i>5){
			sd.SetUniform1i("flag",1);
		}
		renderer.Draw(va,sd);
		}
		glDepthMask(GL_FALSE);
		sd.SetUniform1i("flag",2);
		{
		glm::mat4 model;
		model = glm::scale(model,glm::vec3(40.0f,40.f,40.f));
		sd.SetUniformMat4("u_MVP",model);
		renderer.Draw(skyboxvao,sd);
		}
		// // glBindVertexArray(0);
		glDepthMask(GL_TRUE);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		// /* Poll for and process events */
		glfwPollEvents();
	}
 
	glfwTerminate();
	return 0;
	
}
