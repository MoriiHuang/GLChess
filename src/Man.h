#include<string>
#include"renderer.h"
#include"indexBuffer.h"
#include"shader.h"
#include"renderer.h"
#include"VertexArray.h"
#include<cmath>
#include"Texture.h"
#include"glCamera.h"
#include"Chess.h"
#define trans_for_glm 180.0f/3.1415926535897932384626433832795f
#define Chess_Row 13
#define Chess_Col 13
#define x_margin 36.82
#define y_margin 36.72
#define Chess_Size 56.27
std::vector<pair<double,double> > Chess_transform; 
Camera camera(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0f, 1.0f, 0.0f));
bool Check_win(int col,int row){
        for (int i=0;i<5;i++){
            if (col-i>=0 && col-i+4<=Chess_Col && Chess_Map[col][row]==1
            && Chess_Map[row][col-i]==Chess_Map[row][col-i+1]
            && Chess_Map[row][col-i]==Chess_Map[row][col-i+2]
            && Chess_Map[row][col-i]==Chess_Map[row][col-i+3]
            && Chess_Map[row][col-i]==Chess_Map[row][col-i+4]
            ){
                return true;
            }
        }
        for (int i=0;i<5;i++){
            if (row-i>=0 && row-i+4<=Chess_Row && Chess_Map[col][row]==1
            && Chess_Map[row-i][col]==Chess_Map[row-i+1][col]
            && Chess_Map[row-i][col]==Chess_Map[row-i+2][col]
            && Chess_Map[row-i][col]==Chess_Map[row-i+3][col]
            && Chess_Map[row-i][col]==Chess_Map[row-i+4][col]
            ){
                return true;
            }
        }
        for (int i=0;i<5;i++){ 
            if (row+i<Chess_Row && row+i-4>=0 && col-i>=0 && col-i+4<=Chess_Col 
            && Chess_Map[row+i][col-i]==Chess_Map[row+i-1][col-i+1]
            && Chess_Map[row+i][col-i]==Chess_Map[row+i-2][col-i+2]
            && Chess_Map[row+i][col-i]==Chess_Map[row+i-3][col-i+3]
            && Chess_Map[row+i][col-i]==Chess_Map[row+i-4][col-i+4]
            ){
                return true;
            }
        }
        for (int i=0;i<5;i++){
            if (col+i<Chess_Col && col+i-4>=0 && row-i>=0 && row-i+4<=Chess_Row
            && Chess_Map[row-i][col+i]==Chess_Map[row-i+1][col+i-1]
            && Chess_Map[row-i][col+i]==Chess_Map[row-i+2][col+i-2]
            && Chess_Map[row-i][col+i]==Chess_Map[row-i+3][col+i-3]
            && Chess_Map[row-i][col+i]==Chess_Map[row-i+4][col+i-4]
            ){
                return true;
            }
        }
        return false;
    }
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
	camera.ProcessMouseMovement(window,xpos,ypos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	camera.ProcessMouseScroll(window,yoffset);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
static void mouse_Click_callback(GLFWwindow* window,int button,int action,int mods){
	if (action == GLFW_PRESS) switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		if(start_switch==0){
			start_switch=1;
		}
		else{
		double x;
		double y;
		glfwGetCursorPos(window,&x,&y);
		cout<<x<<","<<y<<endl;
		int col =(x-x_margin)/Chess_Size;
		int row = (y-y_margin)/Chess_Size;
		double leftTopPosX = x_margin + Chess_Size*col;
		double leftTopPosY = y_margin + Chess_Size*row;
		int offset = Chess_Size *0.4;

		int distance = sqrt((x-leftTopPosX)*(x-leftTopPosX)+(y-leftTopPosY)*(y-leftTopPosY));
		if (distance < offset){
		if (Chess_Map[row][col]==0){
		pair<double,double>s(leftTopPosX,leftTopPosY);
		Chess_Map[row][col]=1;
		man_win=Check_win(row,col);
		cout<<"man_win:"<<man_win<<endl;
		Chess_transform.push_back(s);}
		flag_man=1;
		}
		int x2=leftTopPosX;
		int y2=leftTopPosY+Chess_Size;
		distance =	sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
		if (distance < offset){
		if (Chess_Map[row+1][col]==0){
		pair<double,double>s(x2,y2);
		Chess_Map[row+1][col]=1;
		man_win=Check_win(row+1,col);
		Chess_transform.push_back(s);}
		flag_man=1;
		}
		int x3=leftTopPosX+Chess_Size;
		int y3=leftTopPosY;
		distance =	sqrt((x-x3)*(x-x3)+(y-y3)*(y-y3));
		if (distance < offset){
		if (Chess_Map[row][col+1]==0){
		pair<double,double>s(x3,y3);
		Chess_Map[row][col+1]=1;
		man_win=Check_win(row,col+1);
		Chess_transform.push_back(s);}
		flag_man=1;
		}
		int x4=leftTopPosX+Chess_Size;
		int y4=leftTopPosY+Chess_Size;
		distance =	sqrt((x-x4)*(x-x4)+(y-y4)*(y-y4));
		if (distance < offset){
		if (Chess_Map[row+1][col+1]==0){
		pair<double,double>s(x4,y4);
		Chess_Map[row+1][col+1]=1;
		man_win=Check_win(row+1,col+1);
		Chess_transform.push_back(s);}
		flag_man=1;
		}
		}
		break;
	}

}
class Man{
    private:
    GLFWwindow* window;
    public:
	Man(GLFWwindow* win){
		window=win;
		glfwSetMouseButtonCallback(window,mouse_Click_callback);
	}

    void go(const VertexArray& chessva, const indexBuffer& ib, shader& sd,Renderer& rd){
		if (flag_man==1){
			flag_ai=1;
		}
		glm::mat4 model;
		for(int i=0;i<Chess_transform.size();i++){
			model=glm::mat4(1);
			double x=2*Chess_transform[i].first/750 -1;
			double y=1-(2*Chess_transform[i].second/750);
			glm::vec3 move=glm::vec3(x,y,0.0f);
			model = glm::translate(model,move);
			sd.SetUniform1i("flag",1);
			sd.SetUniformMat4("u_MVP",model);
			GLCALL(rd.Draw(chessva,ib,sd));
		}
    }
	
};