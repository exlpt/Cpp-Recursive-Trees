#include <SDL2/SDL.h>
#include <Line.hpp>
#include <Util.hpp>
#include <Macros.hpp>

void RenderLine(SDL_Renderer* renderer, Line* line, int R, int G, int B, int A) {
    SDL_SetRenderDrawColor(renderer, R, G, B, A);
    SDL_RenderDrawLine(renderer,
        (1.0f - (line->GetPoint(0)[0] + 1.0f) / 2.0f) * W_WIDTH,
        (1.0f - (line->GetPoint(0)[1] + 1.0f) / 2.0f) * W_WIDTH,
        (1.0f - (line->GetPoint(1)[0] + 1.0f) / 2.0f) * W_HEIGHT,
        (1.0f - (line->GetPoint(1)[1] + 1.0f) / 2.0f) * W_HEIGHT
    );
}

void ClearScreen(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}