#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "GameWindow.hpp"

GameWindow::GameWindow() : _window(NULL), _renderer(NULL)
{
  this->_window = SDL_CreateWindow(game_settings::TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game_settings::WIDTH * game_settings::SCALE, game_settings::HEIGHT * game_settings::SCALE, SDL_WINDOW_SHOWN);

  this->_renderer = SDL_CreateRenderer(this->_window, 0, SDL_RENDERER_ACCELERATED);

  if (this->_window == NULL)
  {
    std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
  }
}

GameWindow::~GameWindow()
{
  SDL_DestroyWindow(this->_window);
  SDL_DestroyRenderer(this->_renderer);
}

SDL_Texture *GameWindow::loadTexture(const char *pFilePath)
{
  if (this->_textures.count(pFilePath) == 0)
  {
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(this->_renderer, pFilePath);
    if (texture == NULL)
      std::cout
          << "Failed to load texture (" << pFilePath << "): " << SDL_GetError() << std::endl;
    this->_textures[pFilePath] = texture;
  }
  return this->_textures[pFilePath];
}

void GameWindow::renderTexture(SDL_Texture *pTexture, SDL_Rect *pSrcRect, SDL_Rect *pDstRect)
{
  SDL_RenderCopy(this->_renderer, pTexture, pSrcRect, pDstRect);
}
void GameWindow::renderTexture(SDL_Texture *pTexture, SDL_Rect *pSrcRect, SDL_Rect *pDstRect, double pAngle, SDL_Point *pCenter)
{
  SDL_RenderCopyEx(this->_renderer, pTexture, pSrcRect, pDstRect, pAngle, pCenter, SDL_FLIP_NONE);
}

void GameWindow::clear()
{
  SDL_RenderClear(this->_renderer);
}

void GameWindow::present()
{
  SDL_RenderPresent(this->_renderer);
}