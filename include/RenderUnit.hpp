#pragma once

class GameWindow;

class RenderUnit
{
public:
  RenderUnit();
  RenderUnit(GameWindow &pWindow, const char *pFilePath, float pX, float pY, int pW, int pH);

  void draw(GameWindow &pWindow, float scale = 0, float angle = 0);

  void update(int elapsedTime);

protected:
  float _x, _y;
  SDL_Texture *_texture;
  SDL_Rect _srcRect;
};