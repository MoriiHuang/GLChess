#include<string>
#include"renderer.h"
#include"indexBuffer.h"
#include"renderer.h"
#include"VertexArray.h"
#include<cmath>
#include"Texture.h"
#include"Chess.h"
#include<unistd.h>
#include<random>
#define trans_for_glm 180.0f/3.1415926535897932384626433832795f
#define Chess_Row 13
#define Chess_Col 13
#define x_margin 36.82
#define y_margin 36.72
#define Chess_Size 56.27
struct ChessPos
{
    int row;
    int col;
    ChessPos(){

    }
    ChessPos(int r, int c){
        row=r;
        col=c;
    }
};
std::vector<pair<double,double> > Chess_transform_ai; 
class AI{
private: 
   std::vector<std::vector<int> > scoreMap;
public:
    AI(){
        for(int i=0;i<Chess_Col;i++){
            vector<int> score;
            for(int j=0;j<Chess_Row;j++){
                score.push_back(0);
            }
            scoreMap.push_back(score);
        }   
    }
    void go(const VertexArray& chessva, const indexBuffer& ib, shader& sd,Renderer& rd){
        if (flag_ai==1){
        ChessPos pos=evalueScore();
        Chess_Map[pos.row][pos.col]=-1;
        double leftTopPosX = x_margin + Chess_Size*pos.col;
		double leftTopPosY = y_margin + Chess_Size*pos.row;
        pair<double,double> s(leftTopPosX,leftTopPosY);
        ai_win=Check_win(pos.col,pos.row);
        cout<<"ai_win:"<<ai_win<<endl;
        Chess_transform_ai.push_back(s);
        flag_ai=0;
        flag_man=0;
        }
        glm::mat4 model;
		for(int i=0;i<Chess_transform_ai.size();i++){
			model=glm::mat4(1);
			double x=2*Chess_transform_ai[i].first/750 -1;
			double y=1-(2*Chess_transform_ai[i].second/750);
			glm::vec3 move=glm::vec3(x,y,0.0f);
			model = glm::translate(model,move);
			sd.SetUniform1i("flag",2);
			sd.SetUniformMat4("u_MVP",model);
			GLCALL(rd.Draw(chessva,ib,sd));
        }
    }
    void calculateScore(){
        int personNum;//棋手连续有多少个棋子
        int aiNum;//ai 有多少连续的棋子
        int emptyNum ; // 该方向上空白位置的个数 
        for(int i=0;i<Chess_Col;i++){
            for(int j=0;j<Chess_Row;j++){
                scoreMap[i][j]=0;
            }
        }
        for(int row =0;row<Chess_Row;row++){
            for(int col=0;col<Chess_Col;col++){
                if (Chess_Map[row][col]) continue;
                for (int y= -1;y<=0;y++){
                    for (int x=-1;x<=1;x++){    
                        if (y==0 && x==0) continue;
                        if (y==0 && x!=1) continue;
                        personNum=0;
                        aiNum=0;
                        emptyNum=0;
                        for (int i=1;i<5;i++){
                            int curRow=row+i*y;
                            int curCol=col+i*x;
                            if (curCol>=0 && curCol <Chess_Col && curRow>=0 
                            && curRow<Chess_Row && Chess_Map[curRow][curCol]==1){
                                personNum++;
                            }
                            else if (curCol>=0 && curCol <Chess_Col && curRow>=0 
                            && curRow<Chess_Row && Chess_Map[curRow][curCol]==0){
                                emptyNum++;
                                break;
                            }
                            else{
                                break;
                            }
                        }
                        for (int i=1;i<5;i++){
                            int curRow=row-i*y;
                            int curCol=col-i*x;
                            if (curCol>=0 && curCol <Chess_Col && curRow>=0 
                            && curRow<Chess_Row && Chess_Map[curRow][curCol]==1){
                                personNum++;
                            }
                            else if (curCol>=0 && curCol <Chess_Col && curRow>=0 
                            && curRow<Chess_Row && Chess_Map[curRow][curCol]==0){
                                emptyNum++;
                                break;
                            }
                            else{
                                break;
                            }
                        }
                        if(personNum == 1){
                            scoreMap[row][col]+=10;
                        } 
                        else if (personNum==2){
                            if (emptyNum==1){
                                scoreMap[row][col]+=30;
                            }
                            else if (emptyNum==2){
                                scoreMap[row][col]+=40;
                            }
                        }
                        else if (personNum==3){
                            if (emptyNum==1){
                                scoreMap[row][col] =60;
                            }
                            else if (emptyNum==2){
                                scoreMap[row][col] =200;
                            }
                        }
                        else if(personNum==4) {
                            scoreMap[row][col]=20000;
                        }     
                                          
                        emptyNum=0;
                        for (int i=1;i<5;i++){
                            int curRow=row+i*y;
                            int curCol=col+i*x;
                            if (curCol>=0 && curCol <Chess_Col && curRow>=0 
                            && curRow<Chess_Row && Chess_Map[curRow][curCol]==-1){
                                aiNum++;
                            }
                            else if (curCol>=0 && curCol <Chess_Col && curRow>=0 
                            && curRow<Chess_Row && Chess_Map[curRow][curCol]==0){
                                emptyNum++;
                                break;
                            }
                            else{
                                break;
                            }
                        }
                        for (int i=1;i<5;i++){
                            int curRow=row-i*y;
                            int curCol=col-i*x;
                            if (curCol>=0 && curCol <Chess_Col && curRow>=0 
                            && curRow<Chess_Row && Chess_Map[curRow][curCol]==-1){
                                aiNum++;
                            }
                            else if (curCol>=0 && curCol <Chess_Col && curRow>=0 
                            && curRow<Chess_Row && Chess_Map[curRow][curCol]==0){
                                emptyNum++;
                                break;
                            }
                            else{
                                break;
                            }
                        }
                        if (aiNum ==0){
                            scoreMap[row][col]+=5;
                        }
                        if(aiNum == 1){
                            scoreMap[row][col]+=10;
                        } 
                        else if (aiNum==2){
                            if (emptyNum==1){
                                scoreMap[row][col]+=25;
                            }
                            else if (emptyNum==2){
                                scoreMap[row][col]+=50;
                            }
                        }
                        else if (aiNum==3){
                            if (emptyNum==1){
                                scoreMap[row][col]+=55;
                            }
                            else if (emptyNum==2){
                                scoreMap[row][col]+=10000;
                            }
                        }
                        else if (aiNum==4){
                            scoreMap[row][col]+=30000;
                        }
                    }
                }
            }
        }
    for(int row =0;row<Chess_Row;row++){
            for(int col=0;col<Chess_Col;col++){
                cout<<scoreMap[row][col]<<" ";
            }
            cout<<endl;}     
    }

    ChessPos evalueScore(){
        calculateScore();
        vector<ChessPos> maxPoints;
        int maxScore=0;
        for(int row =0;row<Chess_Row;row++){
            for(int col=0;col<Chess_Col;col++){
                if (Chess_Map[row][col] ==0){
                    if (scoreMap[row][col]>maxScore){
                    maxScore=scoreMap[row][col];
                    maxPoints.clear();
                    maxPoints.push_back(ChessPos(row,col));
                    continue;
                    }
                }
                if (scoreMap[row][col] ==maxScore){
                    maxPoints.push_back(ChessPos(row,col));
                }
            }
        }
        random_device rd;
        default_random_engine generator(rd());
        int index = generator()%maxPoints.size();
        cout<<index<<endl;
        return maxPoints[index];
    }

    bool Check_win(int col,int row){
        for (int i=0;i<5;i++){
            if (col-i>=0 && col-i+4<=Chess_Col
            && Chess_Map[row][col-i]==Chess_Map[row][col-i+1]
            && Chess_Map[row][col-i]==Chess_Map[row][col-i+2]
            && Chess_Map[row][col-i]==Chess_Map[row][col-i+3]
            && Chess_Map[row][col-i]==Chess_Map[row][col-i+4]
            ){
                return true;
            }
        }
        for (int i=0;i<5;i++){
            if (row-i>=0 && row-i+4<=Chess_Row
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
};