#pragma once

#include <map>

namespace game_settings
{
  const char TITLE[] = "Asteroids";
  const int WIDTH = 400;
  const int HEIGHT = 400;
  const int SCALE = 2;
  const int FPS = 60;
  const int DELAY_OFFSET = 1;
}

class GameWindow
{
public:
  GameWindow();
  ~GameWindow();

  SDL_Texture *loadTexture(const char *pFilePath);

  void renderTexture(SDL_Texture *pTexture, SDL_Rect *pSrcRect, SDL_Rect *pDstRect);
  void renderTexture(SDL_Texture *pTexture, SDL_Rect *pSrcRect, SDL_Rect *pDstRect, double pAngle, SDL_Point *pCenter);
  void clear();
  void present();

private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;

  std::map<const char *, SDL_Texture *> _textures;
};