#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error initiating SDL: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  IMG_Init(IMG_INIT_PNG);
  printf("SDL initiated successfully\n");

  SDL_Window* window = SDL_CreateWindow("Battleship", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, 0);
  if (window == NULL) {
    printf("Error creating window: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  printf("Window created successfully\n");

  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  SDL_Renderer* render = SDL_CreateRenderer(window, -1, render_flags);
  if (render == NULL) {
    printf("Error rendering: %s\n", SDL_GetError());
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_Surface* surface = IMG_Load("battleship-grid.png");
  if (surface == NULL) {
    printf("Error making surface: %s\n", SDL_GetError());
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
  SDL_FreeSurface(surface);
  if (texture == NULL) {
    printf("Error making texture: %s\n", SDL_GetError());
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_RenderClear(render);
  SDL_RenderCopy(render, texture, NULL, NULL);
  SDL_RenderPresent(render);

  SDL_Delay(5000);

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
