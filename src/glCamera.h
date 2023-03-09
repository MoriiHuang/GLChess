#pragma once
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include<vector>
enum Camera_Movement{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};
const float YAW =-90.0f;
const float PITCH =0.0f;
const float SPEED =2.5f;
const float SENSITIVITY = 0.2f;
const float ZOOM = 45.0f;
bool firstMouse =true;
float lastX = 400, lastY = 300;
struct glCameraVec
{
    /* data */
    glm::vec3 cameraPos;
    glm::vec3 Worldup;
    glm::vec3 cameraRight;
    glm::vec3 cameraUp;
};

class Camera
{
// private:
private:
    /* data */
   glCameraVec glvec;
   glm::vec3 Front;
   glm::mat4 lookAt;
   float Yaw;
   float Pitch;
   float MovementSpeed;
   float MouseSensitivity;
   float Zoom; 
   float deltaTime=0.0f;
   bool firstMouse=true;
public:
    Camera(const glm::vec3 & cameraPos =glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3 up =glm::vec3(0.0f, 1.0f, 0.0f),float yaw=YAW, float pitch = PITCH)
    :Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        glvec.cameraPos=cameraPos;
        glvec.Worldup = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors(); 
    };
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        glvec.cameraPos=glm::vec3(posX,posY,posZ);
        glvec.Worldup=glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    ~Camera(){}
    glCameraVec* getCameraVec(){
        return &glvec;
    }
    glm::mat4 LookAt(){
        glm::mat4 lookAt=glm::lookAt(glvec.cameraPos, glvec.cameraPos + Front, glvec.Worldup);
        return lookAt;
    }
    void processInput(GLFWwindow *window)
    {
        getDeltaTime();
        float cameraSpeed = 0.05f*deltaTime; // adjust accordingly
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            glvec.cameraPos += cameraSpeed *Front;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            glvec.cameraPos -= cameraSpeed * Front;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            glvec.cameraPos -= glm::normalize(glm::cross(Front, glvec.Worldup)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            glvec.cameraPos += glm::normalize(glm::cross(Front, glvec.Worldup)) * cameraSpeed;
        }
    void ProcessMouseMovement(GLFWwindow* window,double xpos,double ypos)
    {   
        if(firstMouse){
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; 
        lastX = xpos;
        lastY = ypos;
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }
    void ProcessMouseScroll(GLFWwindow* window,float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f; 
    }
    float getZoom(){
        return Zoom;
    }
    private:
        void updateCameraVectors(){
            glm::vec3 front;
            front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            front.y = sin(glm::radians(Pitch));
            front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            Front = glm::normalize(front);
            // also re-calculate the Right and Up vector
            glvec.cameraRight = glm::normalize(glm::cross(Front, glvec.Worldup));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            glvec.cameraUp  = glm::normalize(glm::cross(glvec.cameraRight, Front));
        }
        void getDeltaTime(){
            float lastFrame = 0.0f; // 上一帧的时间
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
        }
};




