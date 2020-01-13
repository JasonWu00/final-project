#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

int main(int argc, char *argv[]) {
  int sdl_startup_error = SDL_Init(SDL_INIT_VIDEO);
  if (sdl_startup_error != 0) {
    printf("Error initiating SDL: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  int numdrivers = SDL_GetNumVideoDrivers();
  for (int i=0;i<numdrivers;i++){
    const char *videodriver = SDL_GetVideoDriver(i);
    printf("Driver name: %s\n", videodriver);
  }
  printf("Current video driver: %s\n", SDL_GetCurrentVideoDriver());

  IMG_Init(IMG_INIT_PNG);
  printf("SDL initiated successfully\n");

  SDL_Window *window = SDL_CreateWindow("Battleship",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        640, 480,
                                        SDL_WINDOW_SHOWN |
                                        //SDL_WINDOW_FULLSCREEN
                                        SDL_WINDOW_RESIZABLE
                                        //SDL_WINDOW_MINIMIZED
                                      );
  if (window == NULL) {
    printf("Error creating window: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  printf("Window created successfully\n");

  SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    if(!window_surface)
    {
        printf("Failed to get the surface from the window\n");
        return -1;
    }

    SDL_UpdateWindowSurface(window);

    //SDL_Delay(5000);

  SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
  if (render == NULL) {
    printf("Error rendering: %s\n", SDL_GetError());
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  printf("Render successful\n");

  SDL_Surface* surface = IMG_Load("sprites/battleship-grid.png");
  if (surface == NULL) {
    printf("Error making surface: %s\n", SDL_GetError());
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  printf("Surface made\n");

  SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
  //SDL_FreeSurface(surface);
  if (texture == NULL) {
    printf("Error making texture: %s\n", SDL_GetError());
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  printf("Texture made\n");

  //SDL_Delay(5000);

  SDL_Rect dest;
  dest.w = WINDOW_WIDTH;
  dest.h = WINDOW_HEIGHT;
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

  while (1) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        exit(0);
      }
    }
    SDL_RenderClear(render);
    SDL_RenderCopy(render, texture, NULL, NULL);
    SDL_RenderPresent(render);
    SDL_Delay(1000/60);
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
