#include <SDL2/SDL.h>

#include "InputSystem.hpp"

void InputSystem::registerKeyDown(const SDL_Event &pEvent)
{
  this->_keysDown[pEvent.key.keysym.scancode] = true;
  this->_keysHeld[pEvent.key.keysym.scancode] = true;
}

void InputSystem::registerKeyUp(const SDL_Event &pEvent)
{
  this->_keysUp[pEvent.key.keysym.scancode] = true;
  this->_keysHeld[pEvent.key.keysym.scancode] = false;
}

bool InputSystem::keyPressed(SDL_Scancode pScancode)
{
  return this->_keysDown[pScancode];
}

bool InputSystem::keyReleased(SDL_Scancode pScancode)
{
  return this->_keysUp[pScancode];
}

bool InputSystem::keyHeld(SDL_Scancode pScancode)
{
  return this->_keysHeld[pScancode];
}

void InputSystem::reset()
{
  this->_keysDown.clear();
  this->_keysUp.clear();
}
