#include "ShaderManajer.h"

std::string readShader(const char* VertexShaderFile)
{
    std::string content;
    std::ifstream fileStream(VertexShaderFile, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << VertexShaderFile << ". File does not exist." << std::endl;
        return"";
    }

    std::string  line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line +"\n");
    }

    fileStream.close();
    return content;
}

ShaderManager* ShaderManager::instance = NULL;
ShaderManager* ShaderManager::GetInstance()
{
    if(instance == NULL)
        instance = new ShaderManager();
    return instance;
}

void ShaderManager::compileAndLink(const char* vertexFile, const char* fragmentFile)
{
    std::string vsTemp = readShader(vertexFile);
    std::string fsTemp = readShader(fragmentFile);
    const char* vertexShaderSource = vsTemp.c_str();
    const char* fragmentShaderSource = fsTemp.c_str();
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

unsigned int ShaderManager::getShaderProgram()
{
    return shaderProgram;
}

void ShaderManager::destroy()
{
    if(instance)
        delete instance;
    instance = NULL;
}