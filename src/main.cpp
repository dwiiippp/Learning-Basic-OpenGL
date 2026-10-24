#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <ShaderManajer.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    int size = width < height ? width : height;

    int x = (width - size) / 2;
    int y = (height - size) / 2;

    glViewport(x, y, size, size);
}

int main(void)
{
    GLFWwindow* window;
    

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    });

    /* cek glad */
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "wadoh error\n");
        return -1;
    }

        float vertices[] = {
    //posisi            //warna             //uv koordinat teksture
    0.1f,0.4f,0.0f,    1.0f, 0.0f, 0.0f,   0.0f,0.0f,
    0.3f,0.4f,0.0f,     0.0f, 1.0f, 0.0f,   1.0f,0.0f,
    0.2f,0.2f,0.0f,    0.0f, 0.0f, 1.0f,   1.0f,1.0f,
    0.4f,0.2f,0.0f,     1.0f, 0.0f, 0.0f,   0.0f,1.0f,
    0.0f,0.2f,0.0f,     0.0f, 1.0f, 0.0f,   1.0f,0.0f,
    -0.1f,0.4f,0.0f,     0.0f, 0.0f, 1.0f,   0.5f,0.5f,
    -0.2f,0.2f,0.0f,     1.0f, 0.0f, 0.0f,   1.0f,1.0f,
    -0.3f,0.4f,0.0f,     0.0f, 1.0f, 0.0f,   0.0f,1.0f,
    -0.4f,0.2f,0.0f,     0.0f, 0.0f, 1.0f,   0.0f,0.0f,
    0.4f,-0.1f,0.0f,     1.0f, 0.0f, 0.0f,   1.0f,0.0f,
    -0.4f,-0.1f,0.0f,     0.0f, 1.0f, 0.0f,   1.0f,1.0f,
    0.0f,-0.4f,0.0f,     0.0f, 0.0f, 1.0f,   0.0f,1.0f,
    }; 

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3,
        0, 2, 4,
        4, 5, 6,
        5, 6, 7,
        6, 7, 8,
        3, 8, 9,
        8, 9, 10,
        9, 10, 11,
    };

    float colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f
    };

   ShaderManager::GetInstance()->compileAndLink("resources/Test.vs", "resources/Test.fs");

    //Variable
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    //texture warping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    std::string fileTex = "resources/basecolor.png";
    unsigned char* data = stbi_load(fileTex.c_str(), &width, &height, &nrChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    //VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8, (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8, (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);


    //EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //VAO
    glBindVertexArray(0);

    GLuint shaderProgram = ShaderManager::GetInstance()->getShaderProgram();

    GLuint transformLoc = glGetUniformLocation(shaderProgram,"transform");


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glBindTexture(GL_TEXTURE_2D, texture);
        glUseProgram(shaderProgram);
        float time = glfwGetTime();

        float angle = time; 

        glm::mat4 transform = glm::mat4(1.0f);

        transform = glm::rotate(transform, angle, glm::vec3(0.0f,1.0f,0.0f));

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        float timeValue = glfwGetTime();
        float blink = abs(sin(timeValue * 2.0f));

        GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "mycolor");
        glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
        glUniform4f(vertexColorLocation, blink, blink, blink, 1.0f);
      
        glBindVertexArray(VAO);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
        
        glDrawElements( GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    ShaderManager::GetInstance()->destroy();

    glfwTerminate();
    return 0;
}