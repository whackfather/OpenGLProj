// OpenGL Learning Project

// Include configuration header file
#include "config.h"
#include "shader.h"

int main(void) {
    // Initialize GLFW
    glfwInit();
    int width = 640;
    int height = 480;
    std::string title = "Le Triangl";

    // Create GLWF window
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window.\n");
        glfwTerminate();
        return -1;
    }

    // Make context current and set up window resizing
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Make sure GLAD is initialized
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize glad.\n");
        return -1;
    }

    // Create shaders
    Shader shader("../../../shader/vertexshader.vert", "../../../shader/fragmentshader.frag");
    
    // Establish vertex data
    float vertices[] = {
        // positions        // colors
        -0.05f, 0.2f, 0.0f,  0.2f, 0.0f, 0.4f,
        0.05f, 0.2f, 0.0f,  0.2f, 0.0f, 0.4f,
        -0.05f, -0.2f, 0.0f,  1.0f, 1.0f, 1.0f,
        0.05f, -0.2f, 0.0f,  0.2f, 0.0f, 0.4f,
        -0.08f, 0.2f, 0.0f,  1.0f, 1.0f, 1.0f,
        0.08f, 0.2f, 0.0f,  0.2f, 0.0f, 0.4f,
        0.0f, 0.35f, 0.0f,  0.2f, 0.0f, 0.4f
    };
    // Establish index data for vertices
    unsigned int indices[] = {
        0, 1, 3,
        0, 2, 3,
        4, 5, 6
    };

    // Generate vertex and element buffers, and generate vertex array
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Bind vertex array
    glBindVertexArray(VAO);

    // Bind buffers and provide them with data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind buffers once we are done using them
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Process input
        processInput(window);

        // Clean screen with custom color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Use shader and bind vertex array to draw elements
        shader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);   // 9 represents number of vertices we will be drawing

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Deallocate to free resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Terminate GLFW
    glfwTerminate();
    return 0;
}

// Change viewport size
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Process input
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}