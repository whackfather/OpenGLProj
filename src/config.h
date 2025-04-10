﻿// OpenGL Learning Project configuration header

#pragma once

// Defines
#define STB_IMAGE_IMPLEMENTATION

// Includes
#include <string>
#include <fstream>
#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

// Function declarations
void framebufferSizeCallback(GLFWwindow*, int, int);
void processInput(GLFWwindow* );
void mouseCallback(GLFWwindow*, double, double);
void scrollCallback(GLFWwindow*, double, double);