#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <sys/types.h>
#include <unistd.h>
#include "testing.h"

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)
#define BUTTON_WIDTH (175)
#define BUTTON_HEIGHT (40)

int makeGameWindow() { //makes window for the gameplay

  SDL_Window *game_window = SDL_CreateWindow("Battleship Gameplay",//make window
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              640, 480,
                                              SDL_WINDOW_SHOWN |
                                              //SDL_WINDOW_FULLSCREEN
                                              SDL_WINDOW_RESIZABLE
                                              //SDL_WINDOW_MINIMIZED
                                              );
  SDL_Renderer *game_render = SDL_CreateRenderer(game_window, -1, SDL_RENDERER_PRESENTVSYNC);
  SDL_Surface *game_sf = SDL_GetWindowSurface(game_window);
  SDL_UpdateWindowSurface(game_window);
  SDL_Surface *game_surface = IMG_Load("sprites/battleship-grid.png");
  SDL_Texture *game_texture = SDL_CreateTextureFromSurface(game_render, game_surface);

  SDL_Rect gamedest;
  gamedest.w = WINDOW_WIDTH;
  gamedest.h = WINDOW_HEIGHT;

  SDL_QueryTexture(game_texture, NULL, NULL, &gamedest.w, &gamedest.h);

  while (1) {
    SDL_Event game_event;
    while (SDL_PollEvent(&game_event)) {

    switch (game_event.type) {
      case SDL_QUIT:
        SDL_DestroyTexture(game_texture);
        SDL_DestroyRenderer(game_render);
        SDL_DestroyWindow(game_window);
        exit(0);
        break;
      }
    }

    SDL_RenderClear(game_render);
    SDL_RenderCopy(game_render, game_texture, NULL, NULL);
    SDL_RenderPresent(game_render);
    SDL_Delay(1000/60);
  }
}

int makeMainMenu(SDL_Window *window,
                 SDL_Surface *window_surface,
                 SDL_Renderer *render) { //makes window for main menu

   window = SDL_CreateWindow("Battleship Menu",//make window
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

  window_surface = SDL_GetWindowSurface(window);

    if(!window_surface)
    {
        printf("Failed to get the surface from the window\n");
        return -1;
    }

    SDL_UpdateWindowSurface(window);

    //SDL_Delay(5000);

  render = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  if (render == NULL) {
    printf("Error rendering: %s\n", SDL_GetError());
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  printf("Render successful\n");
}

