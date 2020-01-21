#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
//#include "networking.h"
#include "testing.h"

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)
#define BUTTON_WIDTH (175)
#define BUTTON_HEIGHT (40)
#define GAME_WIDTH (544)
#define GAME_HEIGHT (662)
#define VELOCITY (300)

int main(int argc, char *argv[]) {

  //int yourPID = getpid();
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
                                        SDL_WINDOW_SHOWN //|
                                        //SDL_WINDOW_FULLSCREEN
                                        //SDL_WINDOW_RESIZABLE
                                        //SDL_WINDOW_MINIMIZED
                                      );
  SDL_Window *game_window = SDL_CreateWindow("Battleship Gameplay",//make window
                                             SDL_WINDOWPOS_CENTERED,
                                             SDL_WINDOWPOS_CENTERED,
                                             GAME_WIDTH, GAME_HEIGHT,
                                             SDL_WINDOW_HIDDEN //|
                                             //SDL_WINDOW_FULLSCREEN
                                             //SDL_WINDOW_RESIZABLE
                                             //SDL_WINDOW_MINIMIZED
                                           );
  if (window == NULL) {
    printf("Error creating window: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  int menu_id = SDL_GetWindowID(window);
  int gameplay_id = SDL_GetWindowID(game_window);

  printf("Window created successfully\n");

  SDL_Surface *window_surface = SDL_GetWindowSurface(window);
  SDL_Surface *game_window_surface = SDL_GetWindowSurface(game_window);

  if(!window_surface) {
    printf("Failed to get the surface from the window\n");
    return -1;
  }

  SDL_UpdateWindowSurface(window);
  SDL_UpdateWindowSurface(game_window);

  //SDL_Delay(5000);

  SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  if (render == NULL) {
    printf("Error rendering: %s\n", SDL_GetError());
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  printf("Render successful\n");
  SDL_Renderer* game_render = SDL_CreateRenderer(game_window, -1, SDL_RENDERER_PRESENTVSYNC);

  SDL_Surface* surface = IMG_Load("sprites/main-menu.png");
  if (surface == NULL) {
    printf("Error making surface: %s\n", SDL_GetError());
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  printf("Surface made\n");
  SDL_Surface* game_surface = IMG_Load("sprites/battleship-grid.png");

  SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
  //SDL_FreeSurface(surface);
  if (texture == NULL) {
    printf("Error making texture: %s\n", SDL_GetError());
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  SDL_Texture* game_texture = SDL_CreateTextureFromSurface(game_render, game_surface);

  SDL_Surface* pvp_button_surface = IMG_Load("sprites/pvp.png");
  SDL_Surface* pve_button_surface = IMG_Load("sprites/pvb.png");
  SDL_Surface* quitgame_button_surface = IMG_Load("sprites/quit-game.png");
  SDL_Surface* surrender_surface = IMG_Load("sprites/surrender.png");
  SDL_Surface* defeated_surface = IMG_Load("sprites/defeated.png");
  SDL_Surface* carrier_surface = IMG_Load("sprites/carrier-sprite.png");
  SDL_Surface* battleship_surface = IMG_Load("sprites/battleship-sprite.png");

  SDL_Texture* pvp_button_texture = SDL_CreateTextureFromSurface(render, pvp_button_surface);
  SDL_Texture* pve_button_texture = SDL_CreateTextureFromSurface(render, pve_button_surface);
  SDL_Texture* quitgame_button_texture = SDL_CreateTextureFromSurface(render, quitgame_button_surface);
  SDL_Texture* surrender_texture = SDL_CreateTextureFromSurface(game_render, surrender_surface);
  SDL_Texture* defeated_texture = SDL_CreateTextureFromSurface(game_render, defeated_surface);
  SDL_Texture* carrier_texture = SDL_CreateTextureFromSurface(game_render, carrier_surface);
  SDL_Texture* battleship_texture = SDL_CreateTextureFromSurface(game_render, battleship_surface);

  printf("Textures made\n");

  //SDL_Delay(5000);
  //initiating SDL_Rects for all the sprites
  SDL_Rect arizona;
  arizona.x = 0;
  arizona.y = 0;
  arizona.w = 115;
  arizona.h = 30;
  SDL_QueryTexture(battleship_texture, NULL, NULL, &arizona.w, &arizona.h);
  SDL_Rect nimitz;
  nimitz.x = 0;
  nimitz.y = 0;
  nimitz.w = 160;
  nimitz.h = 40;
  SDL_QueryTexture(carrier_texture, NULL, NULL, &nimitz.w, &nimitz.h);
  SDL_Rect defeat;
  defeat.x = GAME_WIDTH / 2 - 150;
  defeat.y = GAME_HEIGHT / 2 - 75;
  defeat.w = 300;
  defeat.h = 150;
  SDL_QueryTexture(defeated_texture, NULL, NULL, &defeat.w, &defeat.h);
  SDL_Rect game;
  game.w = GAME_WIDTH;
  game.h = GAME_HEIGHT;
  SDL_QueryTexture(game_texture, NULL, NULL, &game.w, &game.h);
  SDL_Rect dest;
  dest.w = WINDOW_WIDTH;
  dest.h = WINDOW_HEIGHT;
  SDL_Rect pvp;
  pvp.x = WINDOW_WIDTH / 2 - 2 * BUTTON_WIDTH / 3 - 25;
  pvp.y = 175;
  pvp.w = BUTTON_WIDTH;
  pvp.h = BUTTON_HEIGHT;
  SDL_Rect pve;
  pve.x = WINDOW_WIDTH / 2 - 2 * BUTTON_WIDTH / 3 - 25;
  pve.y = 250;
  pve.w = BUTTON_WIDTH;
  pve.h = BUTTON_HEIGHT;
  SDL_Rect quit;
  quit.x = WINDOW_WIDTH / 2 - 2 * BUTTON_WIDTH / 3 - 25;
  quit.y = 325;
  quit.w = BUTTON_WIDTH;
  quit.h = BUTTON_HEIGHT;
  SDL_Rect surrender;
  surrender.x = GAME_WIDTH - 40;
  surrender.y = GAME_HEIGHT - 40;
  surrender.w = 40;
  surrender.h = 40;
  SDL_QueryTexture(surrender_texture, NULL, NULL, &surrender.w, &surrender.h);
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  SDL_QueryTexture(pvp_button_texture, NULL, NULL, &pvp.w, &pvp.h);
  SDL_QueryTexture(pve_button_texture, NULL, NULL, &pve.w, &pve.h);
  SDL_QueryTexture(quitgame_button_texture, NULL, NULL, &quit.w, &quit.h);

  int carrier_deployed = 1;
  int battleship_deployed = 0;
  int cruiser_deployed = 0;
  int destroyer_deployed = 0;
  int gunboat_deployed = 0;
  int game_over_victory = 0;
  int game_over_defeat = 0;
  int frames_to_close_gamewindow = 0;
  int ship_dropped = 0;
  int gametype = 0; //1 for pvp, 2 for pve, 0 for no game

  //setting up server and client
  //int c1d = client1setup();//c1d is fildes for client 1 ("server side")
  //int c2d = client2setup();//c2d is fildes for client 2 ("client side")
  float x_pos = (WINDOW_WIDTH - dest.w) / 2;
  float y_pos = (WINDOW_HEIGHT - dest.h) / 2;
  float x_vel = 0;
  float y_vel = 0;

  while (1) {//loop to prevent window autoclosing
    /*if (carrier_deployed = 0) {
      current = nimitz;
    }*/
    SDL_Event event;
      while (SDL_PollEvent(&event)) { //check for events
        if (event.window.windowID == gameplay_id) {

          switch(event.type) {

            case SDL_WINDOWEVENT:
              if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                SDL_HideWindow(game_window);
                SDL_ShowWindow(window);
              }
              break;
            case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
              if ( //click on surrender flag on lower right
                event.button.x >= surrender.x &&
                event.button.y >= surrender.y //&&
                //event.button.x <= surrender.x + 40 &&
                //event.button.y <= surrender.y + 40
                ) {
                  game_over_defeat = 1;
                }
              }
              break;
            }
          }

        if (event.window.windowID == menu_id) { //occurs in menu window

          switch(event.type) {

            case SDL_WINDOWEVENT:
              if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                exit(0);
              }
              break;

            case SDL_MOUSEBUTTONDOWN:
              if ( //click on quit game button
                event.button.x >= quit.x &&
                event.button.y >= quit.y &&
                event.button.x <= quit.x + BUTTON_WIDTH * 1.5 &&
                event.button.y <= quit.y + BUTTON_HEIGHT
                )
                {
                  if (event.window.windowID == menu_id) {
                    exit(0);
                  }
                }

              if ( //click on pvp button
                event.button.x >= pvp.x &&
                event.button.y >= pvp.y &&
                event.button.x <= pvp.x + BUTTON_WIDTH * 1.5 &&
                event.button.y <= pvp.y + BUTTON_HEIGHT
                )
                {
                  battleship_deployed = 0;
                  cruiser_deployed = 0;
                  destroyer_deployed = 0;
                  gunboat_deployed = 0;
                  carrier_deployed = 1;
                  game_over_victory = 0;
                  game_over_defeat = 0;
                  frames_to_close_gamewindow = 0;
                  gametype = 1;
                  //while(battleship_deployed + cruiser_deployed + destroyer_deployed + gunboat_deployed + aircraft_deployed != 5) {//while user placing boats
                    SDL_HideWindow(window);
                    SDL_ShowWindow(game_window);
                    /*while(aircraft_deployed == 0) {
                      if(event.type == SDL_MOUSEBUTTONDOWN) {
                        aircraft.x = event.button.x - (event.button.x % 32) - 16;
                        aircraft.y = event.button.y - (event.button.y % 26) - 366;
                        aircraft_deployed = 1;
                      }
                    }*/
                    /*while(battleship_deployed == 0) {
                      if(event.type == SDL_MOUSEBUTTONDOWN) {
                        battleship.x = event.button.x - (event.button.x % 32) - 48;
                        battleship.y = event.button.y - (event.button.y % 26) - 366;
                        battleship_deployed = 1;
                        gunboat_deployed = 1;
                        cruiser_deployed = 1;
                        destroyer_deployed = 1;
                      }
                    }*/
                  //}
                  //if (game_over_defeat == 0 || game_over_victory == 0) {//if started
                    SDL_HideWindow(window);
                    SDL_ShowWindow(game_window);
                //  }
                }

              if ( //click on pve button
                event.button.x >= pve.x &&
                event.button.y >= pve.y &&
                event.button.x <= pve.x + BUTTON_WIDTH  * 1.5 &&
                event.button.y <= pve.y + BUTTON_HEIGHT
                )
                {
                  battleship_deployed = 0;
                  cruiser_deployed = 0;
                  destroyer_deployed = 0;
                  gunboat_deployed = 0;
                  carrier_deployed = 1;
                  game_over_victory = 0;
                  game_over_defeat = 0;
                  frames_to_close_gamewindow = 0;
                  gametype = 2;
                  /*while(battleship_deployed + cruiser_deployed + destroyer_deployed + gunboat_deployed + aircraft_deployed != 5) {//while user placing boats
                    SDL_HideWindow(window);
                    SDL_ShowWindow(game_window);

                  }*/
                  //while(game_over_defeat == 0 || game_over_victory == 0) {//while game is going on
                    SDL_HideWindow(window);
                    SDL_ShowWindow(game_window);
                  //}
                }
                break;
            }
          }
          break;
    }

    int mouse_x, mouse_y;
    int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

    int target_x = mouse_x - current.w / 2;
    int target_y = mouse_y - current.h / 2;
    float delta_x = target_x - x_pos;
    float delta_y = target_y - y_pos;
    float distance = sqrt(delta_x * delta_x + delta_y * delta_y);

    /*SDL_Event dropship;
    while (SDL_PollEvent(&dropship)) {
      switch (dropship.type) {
        case SDL_MOUSEBUTTONDOWN:
          //if (event.t)
          ship_dropped = 1;
          break;
      }
    }*/

    if (distance < 5) {
      x_vel = y_vel = 0;
    }
    /*else if (ship_dropped = 1){
      x_vel = 0;
      y_vel = 0;
    }*/
    else if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        x_vel = 0;
        y_vel = 0;
    }
    else{
      x_vel = delta_x * VELOCITY / distance;
      y_vel = delta_y * VELOCITY / distance;
    }

    x_pos += x_vel / 60;
    y_pos += y_vel / 60;


    nimitz.y = (int) y_pos;
    nimitz.x = (int) x_pos;

    SDL_RenderClear(render);
    SDL_RenderCopy(render, texture, NULL, NULL);
    SDL_RenderCopy(render, pvp_button_texture, NULL, &pvp);
    SDL_RenderCopy(render, pve_button_texture, NULL, &pve);
    SDL_RenderCopy(render, quitgame_button_texture, NULL, &quit);
    SDL_RenderPresent(render);

    SDL_RenderClear(game_render);
    SDL_RenderCopy(game_render, game_texture, NULL, NULL);
    if(carrier_deployed == 1) {
      SDL_RenderCopy(game_render, carrier_texture, NULL, &nimitz);
    }
    if(battleship_deployed == 1) {
      SDL_RenderCopy(game_render, battleship_texture, NULL, &arizona);
    }
    if (game_over_defeat == 1) {
      SDL_RenderCopy(game_render, defeated_texture, NULL, &defeat);
    }
    SDL_RenderCopy(game_render, surrender_texture, NULL, &surrender);
    SDL_RenderPresent(game_render);
    if (game_over_defeat == 1 || game_over_victory == 1) {
      frames_to_close_gamewindow++;
    }
    if (frames_to_close_gamewindow == 300) {
      game_over_defeat = 0;
      game_over_victory = 0;
      frames_to_close_gamewindow = 0;
      SDL_HideWindow(game_window);
      SDL_ShowWindow(window);
    }
    SDL_Delay(1000/60);
  }


  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
