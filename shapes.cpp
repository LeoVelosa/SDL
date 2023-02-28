#include <SDL2/SDL.h>
#include <cstdlib>
#include <vector>
#include <iostream>

void DrawWireframeTriangle(SDL_Point p0, SDL_Point p1, SDL_Point p2, SDL_Color color, SDL_Renderer *renderer) {
    DrawLine(p0, p1, color, renderer);
    DrawLine(p1, p2, color, renderer);
    DrawLine(p2, p0, color, renderer);
}    
void DrawFilledTriangle(SDL_Point p0, SDL_Point p1, SDL_Point p2, SDL_Color color, SDL_Renderer *renderer) {
    int x;
    int y;

    if(p1.y < p0.y) { swap(p1, p0); }
    if(p2.y < p0.y) { swap(p2, p0); }
    if(p2.y < p1.y) { swap(p2, p1); }

    std::vector<float> x01 = Interpolate(p0.y, p0.x, p1.y, p1.x);
    std::vector<float> x12 = Interpolate(p1.y, p1.x, p2.y, p2.x);
    std::vector<float> x02 = Interpolate(p0.y, p0.x, p2.y, p2.x);

    x01.pop_back();
    std::vector<float> x012;
    x012.reserve(x01.size() + x12.size());
    x012.insert(x012.end(), x01.begin(), x01.end());
    x012.insert(x012.end(), x12.begin(), x12.end());

    std::vector<float> x_left;
    std::vector<float> x_right;

    float m = x02.size()/2;

    if(x02[m] < x012[m]) {
        x_left = x02;
        x_right = x012;
    }
    else {
        x_left = x012;
        x_right = x02;
    }
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b , color.a);
    for(int y = p0.y; y <= p2.y; y++) {
        for(int x = x_left[y - p0.y]; x <= x_right[y - p0.y]; x++) {
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

void DrawShadedTriangle(SDL_Point p0, SDL_Point p1, SDL_Point p2, SDL_Color color, SDL_Renderer *renderer) {
    int x;
    int y;

    if(p1.y < p0.y) { swap(p1, p0); }
    if(p2.y < p0.y) { swap(p2, p0); }
    if(p2.y < p1.y) { swap(p2, p1); }

    std::vector<float> x01 = Interpolate(p0.y, p0.x, p1.y, p1.x);
    std::vector<float> h01 = Interpolate(p0.y, 1.0, p1.y, 0.25);

    std::vector<float> x12 = Interpolate(p1.y, p1.x, p2.y, p2.x);
    std::vector<float> h12 = Interpolate(p1.y, 0.25, p2.y, 0.0);
    
    std::vector<float> x02 = Interpolate(p0.y, p0.x, p2.y, p2.x);
    std::vector<float> h02 = Interpolate(p0.y, 1.0, p2.y, 0.0);

    x01.pop_back();
    std::vector<float> x012;
    x012.reserve(x01.size() + x12.size());
    x012.insert(x012.end(), x01.begin(), x01.end());
    x012.insert(x012.end(), x12.begin(), x12.end());
    
    h01.pop_back();
    std::vector<float> h012;
    h012.reserve(h01.size() + h12.size());
    h012.insert(h012.end(), h01.begin(), h01.end());
    h012.insert(h012.end(), h12.begin(), h12.end());

    std::vector<float> x_left;
    std::vector<float> x_right;
    std::vector<float> h_left;
    std::vector<float> h_right;

    float m = x012.size()/2;

    if(x02[m] < x012[m]) {
        x_left = x02;
        h_left = h02;

        x_right = x012;
        h_right = h012;
    }
    else {
        x_left = x012;
        h_left = h012;

        x_right = x02;
        h_right = h02;
    }
    for(int y = (int)p0.y; y <= (int)p2.y; y++) {
        int idx = y - (int)p0.y;
        float x_l = x_left[idx];
        float x_r = x_right[idx];

        std::vector<float> h_segment = Interpolate(x_l, h_left[idx], x_r, h_right[idx]);
        for(int x = (int)x_l; x <= (int)x_r; x++) {
            SDL_SetRenderDrawColor(renderer, color.r * h_segment[x - (int)x_l], color.g * h_segment[x - (int)x_l], color.b * h_segment[x - (int)x_l], color.a);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}
