#pragma once

// Include statements
#include <string>
#include <fstream>
#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Function declarations
void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);
std::string readShaderCode(const char*);