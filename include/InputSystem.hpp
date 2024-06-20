#pragma once

#include <map>

class InputSystem
{
public:
  void registerKeyDown(const SDL_Event &pEvent);
  void registerKeyUp(const SDL_Event &pEvent);

  bool keyPressed(SDL_Scancode pScancode);
  bool keyReleased(SDL_Scancode pScancode);
  bool keyHeld(SDL_Scancode pScancode);

  void reset();

private:
  std::map<SDL_Scancode, bool> _keysDown;
  std::map<SDL_Scancode, bool> _keysUp;
  std::map<SDL_Scancode, bool> _keysHeld;
};