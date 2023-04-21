
#include "SpaceBug.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SpaceBug::SpaceBug()
{
    std::cout << "SpaceBug Constructor" << std::endl;
}

SpaceBug::SpaceBug(glm::vec2 initPos, glm::vec2 initDirection) : spaceBugPos{initPos}, spaceBugDirection{initDirection}
{
}

SpaceBug::~SpaceBug()
{
    std::cout << "SpaceBug Destructor" << std::endl;
}

void SpaceBug::UpdateSpaceBug()
{
    spaceBugPos += spaceBugDirection;
    if (spaceBugPos.x <= 0 || spaceBugPos.x >= (1280 - 64))
    {
        spaceBugDirection.x *= -1;
    }
    if (spaceBugPos.y <= 0 || spaceBugPos.y >= (720 - 64))
    {
        spaceBugDirection.y *= -1;
    }
}

void SpaceBug::RenderSpaceBug(SDL_Renderer *gameRenderer)
{
    SDL_Surface *spaceBugSurface = IMG_Load("./assets/space_bug.png");
    SDL_Texture *spaceBugTexture = SDL_CreateTextureFromSurface(gameRenderer, spaceBugSurface);
    SDL_FreeSurface(spaceBugSurface);
    spaceBugRect = {static_cast<int>(spaceBugPos.x), static_cast<int>(spaceBugPos.y), 64, 64};
    SDL_RenderCopy(gameRenderer, spaceBugTexture, NULL, &spaceBugRect);
    SDL_DestroyTexture(spaceBugTexture);
}

bool SpaceBug::CheckCollision(SDL_Rect other)
{
    if (SDL_HasIntersection(&spaceBugRect, &other))
    {
        return true;
    }
    return false;
}

void SpaceBug::Destroy()
{
    delete this;
}
