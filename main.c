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

int main(int argc, char *argv[]) {

  int yourPID = getpid();
  int sdl_startup_error = SDL_Init(SDL_INIT_VIDEO);
  if (sdl_startup_error != 0) {//initiates SDL
    printf("Error initiating SDL: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  int numdrivers = SDL_GetNumVideoDrivers();
  for (int i=0;i<numdrivers;i++){//debugging for video drivers
    const char *videodriver = SDL_GetVideoDriver(i);
    printf("Driver name: %s\n", videodriver);
  }
  printf("Current video driver: %s\n", SDL_GetCurrentVideoDriver());

  IMG_Init(IMG_INIT_PNG);//initiates sdl_image
  printf("SDL initiated successfully\n");

  SDL_Window *window = SDL_CreateWindow("Battleship Menu",//make window
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

  SDL_Surface* surface = IMG_Load("sprites/main-menu.png");
  if (surface == NULL) {
    //printf("Error making surface: %s\n", SDL_GetError());
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

  SDL_Surface* pvp_button_surface = IMG_Load("sprites/pvp.png");
  SDL_Surface* pve_button_surface = IMG_Load("sprites/pvb.png");
  SDL_Surface* quitgame_button_surface = IMG_Load("sprites/quit-game.png");

  SDL_Texture* pvp_button_texture = SDL_CreateTextureFromSurface(render, pvp_button_surface);
  SDL_Texture* pve_button_texture = SDL_CreateTextureFromSurface(render, pve_button_surface);
  SDL_Texture* quitgame_button_texture = SDL_CreateTextureFromSurface(render, quitgame_button_surface);

  printf("Texture made\n");

  //SDL_Delay(5000);

  SDL_Rect dest;
  dest.w = WINDOW_WIDTH;
  dest.h = WINDOW_HEIGHT;
  SDL_Rect pvp;
  pvp.x = WINDOW_WIDTH / 2 - 2 *BUTTON_WIDTH / 3 - 25;
  pvp.y = 175;
  pvp.w = BUTTON_WIDTH;
  pvp.h = BUTTON_HEIGHT;
  SDL_Rect pve;
  pve.x = WINDOW_WIDTH / 2 - 2 *BUTTON_WIDTH / 3 - 25;
  pve.y = 250;
  pve.w = BUTTON_WIDTH;
  pve.h = BUTTON_HEIGHT;
  SDL_Rect quit;
  quit.x = WINDOW_WIDTH / 2 - 2 * BUTTON_WIDTH / 3 - 25;
  quit.y = 325;
  quit.w = BUTTON_WIDTH;
  quit.h = BUTTON_HEIGHT;
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  SDL_QueryTexture(pvp_button_texture, NULL, NULL, &pvp.w, &pvp.h);
  SDL_QueryTexture(pve_button_texture, NULL, NULL, &pve.w, &pve.h);
  SDL_QueryTexture(quitgame_button_texture, NULL, NULL, &quit.w, &quit.h);

  while (1) {//loop to prevent window autoclosing
    SDL_Event event;
    while (SDL_PollEvent(&event)) { //check for events
      switch(event.type){
        case SDL_QUIT: //click X on opper right
          exit(0);
          break;
        case SDL_MOUSEBUTTONDOWN:
          if ( //click on quit game button
              event.button.x >= quit.x &&
              event.button.y >= quit.y &&
              event.button.x <= quit.x + BUTTON_WIDTH &&
              event.button.y <= quit.y + BUTTON_HEIGHT
              )
              {
                //exit(0);
                //fork();
                //int childPID = getpid();
                //if (childPID != yourPID) {
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
                //}
              }
          if ( //click on pvp button
              event.button.x >= pvp.x &&
              event.button.y >= pvp.y &&
              event.button.x <= pvp.x + BUTTON_WIDTH &&
              event.button.y <= pvp.y + BUTTON_HEIGHT
              )
              {
                exit(0); //temporary action, will be updated later
              }
          if ( //click on pve button
              event.button.x >= pve.x &&
              event.button.y >= pve.y &&
              event.button.x <= pve.x + BUTTON_WIDTH &&
              event.button.y <= pve.y + BUTTON_HEIGHT
              )
              {
                exit(0); //temporary action, will be updated later
              }
          break;
      }
    }

    SDL_RenderClear(render);
    SDL_RenderCopy(render, texture, NULL, NULL);
    SDL_RenderCopy(render, pvp_button_texture, NULL, &pvp);
    SDL_RenderCopy(render, pve_button_texture, NULL, &pve);
    SDL_RenderCopy(render, quitgame_button_texture, NULL, &quit);
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
