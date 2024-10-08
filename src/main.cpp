// Copyright 2024 Charlotte Jones

#include <SDL2/SDL.h>
#include <stdio.h>

#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
SDL_Surface* loadSurface(std::string path);
void close();

enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurfaces = nullptr;

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
      SDL_BlitSurface(gXOut, nullptr, gScreenSurface, nullptr);
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

SDL_Surface* loadSurface(std::string path) {
  SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
  if (loadedSurface == nullptr) {
    printf("Unable to load image %s! SDL Error: %s\n", path.c_str(),
           SDL_GetError());
  }

  return loadedSurface;
}

bool loadMedia() {
  bool success = true;

  gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] =
      loadSurface("../resources/press.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr) {
    printf("Failed to load default image!\n");
    success = false;
  }

  gKeyPressedSurfaces[KEY_PRESS_SURFACE_UP] =
      loadSurface("../resources/up.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == nullptr) {
    printf("Failed to load up image!\n");
    success = false;
  }

  return success;
}

void close() {
  SDL_FreeSurface(gXOut);
  gXOut = nullptr;

  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  SDL_Quit();
}
