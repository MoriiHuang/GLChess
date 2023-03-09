#pragma once
#include<GL/glew.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include"renderer.h"
#include<unordered_map>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
using namespace std;
struct ShaderProcessSource
{
	/* data */
	string VertexSource;
	string FragmentSource;
};
class shader
{
private:
    /* data */
    unsigned int m_RendererID;
    const string& m_filepath;
    unordered_map<string,int> m_LocationCache;
public:
    shader(const shader& sd):m_filepath(sd.m_filepath){
        m_RendererID = sd.m_RendererID;
        m_LocationCache=sd.m_LocationCache;
    }
    shader(const string& filepath):m_filepath(filepath){
        ShaderProcessSource source =ParseShader(filepath);
        m_RendererID=CreateShader(source.VertexSource,source.FragmentSource);
    }
    ~shader(){
        GLCALL(glDeleteShader(m_RendererID));
    }
    void Bind() const {
        glUseProgram(m_RendererID);
    }
    void Unbind() const{
        glUseProgram(0);
    }
    void SetUniform4f( const string& name,float v0,float v1,float v2, float v3){
        glUniform4f(GetUniformlocation(name),v0,v1,v2,v3);
    }
    void SetUniform1f( const string& name,float v0){
        glUniform1f(GetUniformlocation(name),v0);
    }
    void SetUniform1i( const string& name,int v0){
        glUniform1i(GetUniformlocation(name),v0);
    }
     void SetUniformMat4( const string& name,const glm::mat4& mat){
        glUniformMatrix4fv(GetUniformlocation(name),1,GL_FALSE,glm::value_ptr(mat));
    }
    void SetUniform3f(const string& name,float v0,float v1,float v2){
        glUniform3f(GetUniformlocation(name),v0,v1,v2);
    }
    int GetUniformlocation(const string& name){
        if (m_LocationCache.find(name)!=m_LocationCache.end()){
            return m_LocationCache[name];
        }
        int location;
        location=glGetUniformLocation(m_RendererID,name.c_str());
        ASSERT(location !=-1);
        m_LocationCache[name]=location;
        return location;
    }
private:
    ShaderProcessSource ParseShader(const string& filepath){
        ifstream stream(filepath);
        string line;
        stringstream ss[2];
        enum class Shadertype{
            NONE=-1,VERTEX=0,FRAGMENT=1
        };
        Shadertype type=Shadertype::NONE;
        while(getline(stream,line)){
            if(line.find("#shader")!=string::npos){
                if(line.find("vertex")!=string::npos){
                    type=Shadertype::VERTEX;

                }
                else if(line.find("fragment")!=string::npos){
                    type=Shadertype::FRAGMENT;
                }
            }
            else{
                ss[(int)type]<<line<<"\n";
            }

        }
        return{ss[0].str(),ss[1].str()};
}
    unsigned int CompileShader(unsigned int type,const string& source){
        unsigned int id=glCreateShader(type);
        const char* src=source.c_str();
        glShaderSource(id,1,&src,nullptr);
        glCompileShader(id);
        int result;
        glGetShaderiv(id,GL_COMPILE_STATUS,&result);
        if(result==GL_FALSE){
            int length;
            glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
            char* message =(char*)alloca(length*sizeof(char));
            glGetShaderInfoLog(id,length,&length,message);
            cout<<"Failed to compile "<<(type==GL_VERTEX_SHADER ? "verterx":"fragment")<<endl;
            cout<<message<<endl;
            glDeleteShader(id);
            return 0;
        }
        return id;
}
    unsigned int CreateShader(const string&vertexShader,const string& fragmentShader){
        unsigned int program=glCreateProgram();
        unsigned int vs=CompileShader(GL_VERTEX_SHADER,vertexShader);
        unsigned int fs=CompileShader(GL_FRAGMENT_SHADER,fragmentShader);
        glAttachShader(program,vs);
        glAttachShader(program,fs);
        glLinkProgram(program);
        glUseProgram(program);
        glDeleteShader(vs);
        glDeleteShader(fs);
        return program;
}
};

