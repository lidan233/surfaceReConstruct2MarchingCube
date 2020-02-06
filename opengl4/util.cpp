//
// Created by 李源 on 2020-02-06.
//

#include "util.h"

static void error_callback(int error, const char* description)
{
    std::cerr << description << std::endl;
}


GLFWwindow* init(std::string name,int width,int height)
{
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if(!glfwInit())
    {
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // OS X
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 2);

    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if(!window)
    {
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window);

    glEnable(GL_MULTISAMPLE);

    std::cout << "Using OpenGL version " << glGetString(GL_VERSION) << std::endl;

    return window;
}


GLuint createShader(const char* src, GLenum shaderType)
{
    // Create a shader and load the string as source code and compile it
    GLuint s = glCreateShader(shaderType);
    glShaderSource(s, 1, (const GLchar**)&src, NULL);
    glCompileShader(s);

    // Check compilation status: this will report syntax errors
    GLint status;
    glGetShaderiv(s, GL_COMPILE_STATUS, &status);
    if(!status)
    {
        std::cerr << "Compiling of shader failed: ";
        char log[512];
        glGetShaderInfoLog(s, 512, NULL, log);
        std::cerr << log << std::endl;
        return 0;
    }

    return s;
}

GLuint createShaderProgram(GLuint vertex, GLuint fragment)
{
    // Create a shader program and attach the vertex and fragment shaders
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    return program;
}

GLuint createShaderProgram(GLuint vertex, GLuint geometry, GLuint fragment)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, geometry);
    glAttachShader(program, fragment);
    return program;
}

bool linkShader(GLuint program)
{
    // Link the program and check the status: this will report semantics errors
    glLinkProgram(program);
    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(!status)
    {
        std::cerr << "Linking of shader failed: ";
        char log[512];
        glGetProgramInfoLog(program, 512, NULL, log);
        std::cerr << log << std::endl;
        return false;
    }
    return true;
}

// Still here for backwards compatibility
bool validateShader(GLuint program)
{
    return true;
}


