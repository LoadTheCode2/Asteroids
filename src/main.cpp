#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "GameWindow.hpp"
#include "InputSystem.hpp"
#include "RenderUnit.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Ship.hpp"

int main(int argc, char **argv)
{
  srand(time(NULL));

  if (SDL_Init(SDL_INIT_VIDEO) > 0)
    std::cout << "SDL2 has failed to init: " << SDL_GetError() << std::endl;

  if (!IMG_Init(IMG_INIT_PNG))
    std::cout << "SDL2_image has failed to init: " << SDL_GetError() << std::endl;

  GameWindow window;
  InputSystem inputs;

  Ship ship(window);
  std::vector<Asteroid> asteroids;
  std::vector<Bullet> bullets;
  RenderUnit bg(window, "res/gfx/bg.png", 0, 0, game_settings::WIDTH, game_settings::HEIGHT);

  asteroids.push_back(Asteroid(window));

  int lastSpawnTime = SDL_GetTicks();

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

    if (inputs.keyPressed(SDL_SCANCODE_SPACE))
      ship.shoot(window, bullets);
    if (inputs.keyHeld(SDL_SCANCODE_LEFT))
      ship.turnLeft();
    if (inputs.keyHeld(SDL_SCANCODE_RIGHT))
      ship.turnRight();
    if (inputs.keyHeld(SDL_SCANCODE_UP))
      ship.boost();
    if (inputs.keyHeld(SDL_SCANCODE_DOWN))
      ship.brake();

    inputs.reset();

    window.clear();

    bg.draw(window, 2);

    for (int i = 0; i < asteroids.size(); i++)
    {
      asteroids[i].draw(window);
    }

    for (int i = 0; i < bullets.size(); i++)
    {
      bullets[i].draw(window);
    }
    ship.draw(window);

    window.present();

    const int beforeDelayTicks = SDL_GetTicks();
    const int beforeElapsedTime = std::min(beforeDelayTicks - ancientFrameTicks, timePerFrame);
    if (timePerFrame - game_settings::DELAY_OFFSET > beforeElapsedTime)
      SDL_Delay(timePerFrame - beforeElapsedTime - game_settings::DELAY_OFFSET);

    const int currentFrameTicks = SDL_GetTicks();
    const float elapsedTime = std::min(currentFrameTicks - ancientFrameTicks, timePerFrame);

    for (int i = 0; i < asteroids.size(); i++)
    {
      asteroids[i].update(elapsedTime);
      if (asteroids[i].offScreen())
        asteroids.erase(asteroids.begin() + i);
    }

    for (int i = 0; i < bullets.size(); i++)
    {
      bullets[i].update(elapsedTime);
      if (bullets[i].offScreen())
        bullets.erase(bullets.begin() + i);
    }

    std::vector<Asteroid> pendingAsteroids;

    if (bullets.empty() == false)
    {
      for (int i = 0; i < bullets.size(); i++)
      {
        for (int j = 0; j < asteroids.size(); j++)
        {
          if (
              bullets[i].collidesWith(asteroids[j].getBoundingBox()))
          {

            pendingAsteroids.push_back(asteroids[j].smash(window));
            bullets.erase(bullets.begin() + i);
          }
        }
      }
    }

    for (int i = 0; i < pendingAsteroids.size(); i++)
    {
      asteroids.push_back(pendingAsteroids[i]);
    }

    ship.update(elapsedTime);

    bool shipDead = false;

    for (int i = 0; i < asteroids.size(); i++)
    {
      if (ship.collidesWith(asteroids[i].getBoundingBox()))
        shipDead = true;
    }

    if (shipDead)

      break;

    ancientFrameTicks = SDL_GetTicks();

    if (SDL_GetTicks() - lastSpawnTime > 1000)
    {
      asteroids.push_back(Asteroid(window));
      lastSpawnTime = SDL_GetTicks();
    }
  }

  SDL_Quit();

  return 0;
}