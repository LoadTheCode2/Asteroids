#pragma once

class GameWindow;

class RenderUnit
{
public:
  RenderUnit(GameWindow &pWindow, const char *pFilePath, float pX, float pY, int pW, int pH);

  void draw(GameWindow &pWindow);

  void update(int elapsedTime);

protected:
  float _x, _y;
  SDL_Texture *_texture;
  SDL_Rect _srcRect;
};