#include <SDL2/SDL.h>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "utility.cpp"
#include "shapes.cpp"

int main()
{
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int i;

    SDL_Point p0 = {400, 80};
    SDL_Point p1 = {125, 300};
    SDL_Point p2 = {300, 550};

    SDL_Color color = {255, 255, 0, 255};

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(600, 600, 0, &window, &renderer);

    //DrawLine(p0, p1, color, renderer);
    //DrawWireframeTriangle(p0, p1, p2, color, renderer);
    //DrawFilledTriangle(p0, p1, p2, color, renderer);
    DrawShadedTriangle(p0, p1, p2, color, renderer);
    SDL_RenderPresent(renderer);

    while(1) {
        if(SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
