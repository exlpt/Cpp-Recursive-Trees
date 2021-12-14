#include <iostream>
#include <string>
#include <chrono>
#include <math.h>
#include <thread>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <Line.hpp>
#include <Util.hpp>
#include <Tree.hpp>
#include <Macros.hpp>

int main() {
    // ======= INITIALIZATION =======
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Failed to initialize SDL!\n";
        return EXIT_FAILURE;
    }

    // Initialize SDL_image
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "Failed to initialize SDL_image!\n";
        return EXIT_FAILURE;
    }

    // Initialize SDL_ttf
    if (TTF_Init() != 0) {
        std::cerr << "Failed to initialize SDL_ttf!\n";
        return EXIT_FAILURE;
    }

    // ======= SETUP =======
    SDL_Event event;
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_CreateWindowAndRenderer(W_WIDTH, W_HEIGHT, 0, &window, &renderer);

    TTF_Font* roboto = TTF_OpenFont("fonts/Roboto-Regular.ttf", 50);

    int depth = 12;
    float testAngle = 0.0f;
    int framerate = 120;
    std::string fpsCounter("");

    while (!(SDL_PollEvent(&event) && event.type == SDL_QUIT)) {
        // ======= CODE =======
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



        // ======= RENDER =======
        ClearScreen(renderer);

        // Render lines
        for (int i = 0; i < lineCount; i++) {
            RenderLine(renderer, &lines[i], 245, 245, 255, 255);
        }

        // Render text
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(roboto, fpsCounter.c_str(), { 150, 150, 155 }); 
        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_Rect Message_rect;
        Message_rect.x = 5;
        Message_rect.y = 5;
        Message_rect.w = 9 * fpsCounter.length();
        Message_rect.h = 20;

        // Draw
        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
        SDL_RenderPresent(renderer);

        // Free surface + texture
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(Message);



        // ======= FRAME LIMITING =======
        auto end = std::chrono::steady_clock::now();
        float elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // Elapsed time in ms
        float frametime = 1000 / framerate; // Frametime in ms
        int sleep = frametime - elapsed;
        float calculatedFps = 1000.0f / elapsed;
        fpsCounter = std::to_string(floor(calculatedFps)) + '.' + std::to_string((int)(calculatedFps * 100.0f) % 100);
        if (elapsed > frametime)
            fpsCounter = std::to_string((int)floor(calculatedFps)) + '.' + std::to_string((int)(calculatedFps * 100.0f) % 100) + " Frame dropping!";
        else
            fpsCounter = "60.00fps";
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    }



    // ======= EXIT =======
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();

    return EXIT_SUCCESS;
}