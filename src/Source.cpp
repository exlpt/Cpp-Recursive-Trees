#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <LoadShader.hpp>
#include <Line.hpp>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to load OpenGL and its extensions\n";
        return EXIT_FAILURE;
    }

    unsigned vertexArrayObjectID;
    glGenVertexArrays(1, &vertexArrayObjectID);
    glBindVertexArray(vertexArrayObjectID);

    Line test(-0.7f, -0.5f, 0.1f, 0.9f, 0.1f);
    float* testPoint1 = test.GetPixelCoords(0);
    float* testPoint2 = test.GetPixelCoords(1);

    // Define verticies
    static const GLfloat verticies[] = {
        testPoint1[0],  testPoint1[1], 0.0f,
        testPoint1[2],  testPoint1[3], 0.0f,
        testPoint2[0],  testPoint2[1], 0.0f,

        testPoint2[2],  testPoint2[3], 0.0f, 
        testPoint1[2],  testPoint1[3], 0.0f,
        testPoint2[0],  testPoint2[1], 0.0f,
    };

    // Create vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    // Load shaders
    GLuint shader = LoadShaders("assets/BasicVertex.shader", "assets/BasicFragment.shader");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        glUseProgram(shader);
        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        // Draw
        glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}