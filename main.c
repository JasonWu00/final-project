#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
//#include "SDL_stdinc.h"

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error initiating SDL: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  printf("SDL initiated successfully\n");

  SDL_Window* window = SDL_CreateWindow("Battleship", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, 0);
  if (window == NULL) {
    printf("Error creating window: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  printf("Window created successfully\n");

  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  SDL_Renderer* render = SDL_CreateRenderer(window, -1, render_flags);
  if (render == NULL) {
    printf("Error rendering: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  //SDL_Surface* surface = IMG_Load();

  SDL_Quit();
  return 0;
}
