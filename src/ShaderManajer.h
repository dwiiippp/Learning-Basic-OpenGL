#ifndef _SHADERMANAGER_H_
#define _SHADERMANAGER_H_

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>

class ShaderManager{
private:
    static ShaderManager* instance;
    unsigned int shaderProgram;
public:
    static ShaderManager* GetInstance();
    void compileAndLink(const char* vertexFile, const char* fragmentFile);
    unsigned int getShaderProgram();
    void destroy();
};

#endif