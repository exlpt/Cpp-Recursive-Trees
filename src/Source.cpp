#include <iostream>
#include <chrono>
#include <thread>
#define SDL_MAIN_HANDLED 
#include <SDL2/SDL.h>
#include <Line.hpp>
#include <Util.hpp>
#include <Tree.hpp>
#include <Macros.hpp>

int main() {
    SDL_Event event;
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(W_WIDTH, W_HEIGHT, 0, &window, &renderer);

    int depth = 10;
    float testAngle = 0.0f;
    int framerate = 60;
    while (!(SDL_PollEvent(&event) && event.type == SDL_QUIT)) {
        // Start timer
        auto start = std::chrono::steady_clock::now();
        
        // Change angle of tree
        if (testAngle > 6.28318530718f) testAngle = 0; 
        testAngle += 0.01f;

        // Generate tree
        AngleTree* angleTree = new AngleTree(depth, testAngle, 0.0f, -0.8f, 0.45f, 1.4f);

        // Put tree lines into array
        int lineCount = (2 << depth) - 1;
        Line lines[lineCount];

        angleTree->DumpLines(lines);

        // Render
        ClearScreen(renderer);

        // Render lines
        for (int i = 0; i < lineCount; i++) {
            RenderLine(renderer, &lines[i], 245, 245, 255, 255);
        }
        
        // Draw
        SDL_RenderPresent(renderer);

        // Frame limiting using timer
        auto end = std::chrono::steady_clock::now();
        int sleep = (
            1000 / framerate - // Frametime in ms
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() // Elapsed time in ms
        );
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}