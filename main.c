#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
//#include "SDL_stdinc.h"

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error initiating SDL: %s\n", SDL_GetError());
  }
  else {
    printf("SDL initiated successfully\n");
  }

  SDL_Window* window = SDL_CreateWindow("Battleship", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, 0);
  if (window == NULL) {
    printf("Error creating window: %s\n", SDL_GetError());
  }
  else {
    printf("Window created successfully\n");
  }

  SDL_Quit();
  return 0;
}
