#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <sys/types.h>
#include <unistd.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)
#define BUTTON_WIDTH (175)
#define BUTTON_HEIGHT (40)

int main(int argc, char* argv[]) {

  SDL_Window *game_window = SDL_CreateWindow("Battleship Gameplay",//make window
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              640, 480,
                                              SDL_WINDOW_SHOWN |
                                              //SDL_WINDOW_FULLSCREEN
                                              SDL_WINDOW_RESIZABLE
                                              //SDL_WINDOW_MINIMIZED
                                              );
  SDL_Renderer *game_render = SDL_CreateRenderer(game_window, -1, 0);
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
