#include <SDL2/SDL.h>
#include <cstdlib>
#include <vector>
#include <iostream>

void swap(SDL_Point &p0, SDL_Point &p1) {
    SDL_Point temp = p0;
    p0 = p1;
    p1 = temp;
}
std::vector<float> Interpolate(int i0, float d0, int i1, float d1) {
    std::vector<float> values;
    if (i0 == i1) {
        values.push_back(d0);
        return values;
    }
    float a = (d1-d0) / (i1-i0);
    float d = d0;
    for(int i=i0; i <= i1;i++) {
        values.push_back(d);
        d = d + a;
    }
    return values;
}
void DrawLine(SDL_Point p0, SDL_Point p1, SDL_Color color, SDL_Renderer* renderer) {
    int i;
    if (std::abs((p1.x-p0.x)) > std::abs((p1.y-p0.y))) {
        if(p0.x > p1.x) {
            swap(p0, p1);
        }
        std::vector<float> ys = Interpolate(p0.x, p0.y, p1.x, p1.y);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b , color.a);
        for(int i=(int)p0.x;i<=(int)p1.x;i++) {
            SDL_RenderDrawPoint(renderer, (float)i, ys[(i-(int)p0.x)]);
        }
    }
    else {
        if(p0.y > p1.y) {
            swap(p0, p1);
        }
        std::vector<float> xs = Interpolate(p0.y, p0.x, p1.y, p1.x);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        for(int i=(int)p0.y;i<=(int)p1.y;i++) {
            SDL_RenderDrawPoint(renderer, xs[(i-(int)p0.y)], (float)i);
        }
    }
}
