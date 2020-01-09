#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_stdinc.h"

int main() {
  setenv(SDL_VIDEODRIVER);
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error initiating SDL: %s\n", SDL_GetError());
  }
  else {
    printf("SDL initiated successfully\n");
  }
  SDL_Quit();
  return 0;
}
