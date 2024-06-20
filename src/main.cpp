#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "GameWindow.hpp"
#include "InputSystem.hpp"
#include "RenderUnit.hpp"
#include "Ship.hpp"

int main(int, char **)
{
  if (SDL_Init(SDL_INIT_VIDEO) > 0)
    std::cout << "SDL2 has failed to init: " << SDL_GetError() << std::endl;

  if (!IMG_Init(IMG_INIT_PNG))
    std::cout << "SDL2_image has failed to init: " << SDL_GetError() << std::endl;

  GameWindow window;
  InputSystem inputs;

  Ship ship(window, "res/gfx/ship.png", 22, 41);
  RenderUnit bg(window, "res/gfx/bg.png", 0, 0, game_settings::WIDTH, game_settings::HEIGHT);

  SDL_Event event;

  const int timePerFrame = 1000 / game_settings::FPS;
  int ancientFrameTicks = SDL_GetTicks();

  while (true)
  {
    if (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        break;
      else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        inputs.registerKeyDown(event);
      else if (event.type == SDL_KEYUP)
        inputs.registerKeyUp(event);
    }

    if (inputs.keyHeld(SDL_SCANCODE_LEFT))
      ship.turnLeft();
    else if (inputs.keyHeld(SDL_SCANCODE_RIGHT))
      ship.turnRight();
    else
      ship.stopTurn();

    if (inputs.keyHeld(SDL_SCANCODE_UP))
      ship.boost();
    // else
    //   ship.stopBoost();

    inputs.reset();

    window.clear();

    // DRAW HERE

    bg.draw(window);

    ship.draw(window);

    window.present();

    const int beforeDelayTicks = SDL_GetTicks();
    const int beforeElapsedTime = std::min(beforeDelayTicks - ancientFrameTicks, timePerFrame);
    if (timePerFrame - game_settings::DELAY_OFFSET > beforeElapsedTime)
      SDL_Delay(timePerFrame - beforeElapsedTime - game_settings::DELAY_OFFSET);

    const int currentFrameTicks = SDL_GetTicks();
    // printf("TIME: %d, FPS: %d\n", currentFrameTicks - ancientFrameTicks, timePerFrame);
    const float elapsedTime = std::min(currentFrameTicks - ancientFrameTicks, timePerFrame);

    // UPDATE HERE
    ship.update(elapsedTime);

    ancientFrameTicks = SDL_GetTicks();
  }

  SDL_Quit();

  return 0;
}