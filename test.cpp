#include <SDL2/SDL.h>
#include <cstdlib>
#include <array>
#include <iostream>

void swap(float &x0, float &y0, float &x1, float &y1) {
    float tempx0 = x0;
    float tempy0 = y0;
    x0 = x1;
    y0 = y1;
    x1 = tempx0;
    y1 = tempy0;
}
std::array<float, 600> Interpolate(int i0, float d0, int i1, float d1) {
    std::array<float, 600> values;
    if (i0 == i1) {
        values.fill(d0);
        return values;
    }
    std::cout<<d0<<"\n"<<d1<<"\n";
    float a = (d1-d0) / (i1-i0);
    std::cout<<a<<"\n";
    float d = d0;
    for(int i=i0; i <= i1;i++) {
        values.fill(d);
        d = d + a;
    }
    return values;
}
void DrawLine(float x0, float y0, float x1, float y1, int r, int g, int b, SDL_Renderer* renderer) {
    int i;
    if (std::abs((x1-x0)) > std::abs((y1-y0))) {
        if(x0 > x1) {
            swap(x0,y0,x1,y1);
        }
        std::array<float, 600> ys = Interpolate(x0,y0,x1,y1);
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        for(int i=(int)x0;i<=(int)x1;i++) {
            std::cout<<i<<"\n";
            SDL_RenderDrawPoint(renderer, (float)i, ys[(i-(int)x0)]);
        }
    }
    else {
        if(y0 > y1) {
            swap(x0,y0,x1,y1);
        }
        std::array<float, 600> xs = Interpolate(y0, x0, y1, x1);
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        for(int i=(int)y0;i<=(int)y1;i++) {
            std::cout<<i<<"\n";
            SDL_RenderDrawPoint(renderer, xs[(i-(int)y0)], (float)i);
        }
    }
}
int main()
{
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int i;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(600, 600, 0, &window, &renderer);

    DrawLine(0, 50, 125, 75, 255, 0, 0, renderer);
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
