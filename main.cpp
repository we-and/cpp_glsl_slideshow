#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
GLuint loadShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertexSource = vertexShaderSrc.c_str();
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    // Check for vertex shader compile errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragmentSource = fragmentShaderSrc.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    // Check for fragment shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint compileAndLinkShader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLint success;
    char infoLog[512];

    // Compile vertex shader
    const char* vertexShaderSource = vertexShaderCode.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Compile fragment shader
    const char* fragmentShaderSource = fragmentShaderCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link shaders to a program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}
std::string readShaderSource(const std::string& filePath) {
    std::ifstream shaderFile;
    std::stringstream shaderStream;

    shaderFile.open(filePath);
    if (!shaderFile) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: Unable to open file " << filePath << std::endl;
        return ""; // Return an empty string if file could not be opened
    }

    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    return shaderStream.str();
}

int checkVersion(){
      if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    

    // Create a windowed mode window and its OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1); // Use OpenGL 1.0 as the baseline to check higher support
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Version Check", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Print the OpenGL version supported by the GPU
    std::cout << "OpenGL Version Supported: " << glGetString(GL_VERSION) << std::endl;

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
int main() {
//    checkVersion();
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac


    GLFWwindow* window = glfwCreateWindow(800, 600, "Shader Switcher", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewInit();

    auto fragmentShaderSrc=readShaderSource("shaders/frag.glsl");
    auto vertexShaderSrc=readShaderSource("shaders/vertexShader.glsl");


    std::vector<GLuint> shaders;
    shaders.push_back(loadShader(vertexShaderSrc, fragmentShaderSrc));
//    shaders.push_back(LoadShader(vertexShaderSource, fragmentShader2));

    GLuint currentShader = shaders[0];
    auto lastSwitch = std::chrono::steady_clock::now();
    int index = 0;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Check if 3 seconds have passed
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastSwitch).count() >= 3) {
            index = (index + 1) % shaders.size();
            currentShader = shaders[index];
            lastSwitch = now;
        }

        glUseProgram(currentShader);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    for (auto shader : shaders) {
        glDeleteProgram(shader);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}