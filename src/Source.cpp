#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <LoadShader.hpp>
#include <Line.hpp>
#include <Util.hpp>
#include <Tree.hpp>
#include <chrono>
#include <thread>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1000, 1000, "Trees", NULL, NULL);
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
/*
    // Generate tree
    int depth = 6;
    AngleTree* angleTree = new AngleTree(depth, 0.5f, 0.0f, -1.0f, 0.5f, 1.5f);

    // Put tree lines into array
    int lineCount = (2 << depth) - 1;
    Line lines[lineCount];

    angleTree->DumpLines(lines);

    // Populate vertex array
    GLfloat verticies[18 * lineCount];
    SetVertexArray(lines, lineCount, verticies);*/

    // VAO
    unsigned vertexArrayObjectID;
    glGenVertexArrays(1, &vertexArrayObjectID);
    glBindVertexArray(vertexArrayObjectID);

    // Create vertex buffer
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    // Load shaders
    GLuint shader = LoadShaders("assets/BasicVertex.shader", "assets/BasicFragment.shader");
    glUseProgram(shader);

    int depth = 12;
    float testAngle = 0.0f;
    int framerate = 60;
    while (!glfwWindowShouldClose(window)) {
        auto start = std::chrono::steady_clock::now();

        glClear(GL_COLOR_BUFFER_BIT);
        
        if (testAngle > 6.28318530718f) testAngle = 0; 
        testAngle += 0.01f;

        // Generate tree
        AngleTree* angleTree = new AngleTree(depth, testAngle, 0.0f, -0.8f, 0.45f, 1.4f);

        // Put tree lines into array
        int lineCount = (2 << depth) - 1;
        Line lines[lineCount];

        angleTree->DumpLines(lines);

        // Populate vertex array
        GLfloat verticies[18 * lineCount];
        SetVertexArray(lines, lineCount, verticies);

        // Give verts to vertex buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

        // Render

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
        glDrawArrays(GL_TRIANGLES, 0, 6 * lineCount); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        // frame limiting
        auto end = std::chrono::steady_clock::now();
        int sleep = (
            1000 / framerate - // Frametime in ms
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() // Elapsed time in ms
        );
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}