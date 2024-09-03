// Copyright 2024 Charlotte Jones

#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gHelloWorld = nullptr;

bool init() {
  bool success{true};

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

bool loadMedia() {
  bool success{true};

  gHelloWorld = SDL_LoadBMP("../resources/hello_world.bmp");
  if (gHelloWorld == nullptr) {
    printf("Unable to load image %s! SDL Error: %s\n",
           "../resources/hello_world.png", SDL_GetError());
    success = false;
  }

  return success;
}

void close() {
  SDL_FreeSurface(gHelloWorld);
  gHelloWorld = nullptr;

  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  SDL_Quit();
}

int main(int argc, char* args[]) {
  // These parameters are necessary for SDL2 to function, but won't be used in
  // our code. The are cast to void to avoid compiler warnings about unused
  // variables
  (void)argc;
  (void)args;

  if (!init()) {
    printf("Failed to initialize!\n");
  } else {
    if (!loadMedia()) {
      printf("Failed to load media!\n");
    } else {
      SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);
      SDL_UpdateWindowSurface(gWindow);
    }

    SDL_Event e;
    bool quit{false};
    while (!quit) {
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
      }
    }
  }

  close();
  return 0;
}
