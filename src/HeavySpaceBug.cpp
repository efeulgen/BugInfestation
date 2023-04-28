
#include "HeavySpaceBug.h"
#include <iostream>
#include <SDL2/SDL_image.h>

HeavySpaceBug::HeavySpaceBug()
{
}

HeavySpaceBug::HeavySpaceBug(glm::vec2 pos, glm::vec2 dir) : SpaceBug(pos, dir)
{
}

void HeavySpaceBug::GetDamage()
{
      health--;
      if (health <= 0)
      {
            Destroy();
      }
}

void HeavySpaceBug::ShootProjectile()
{
      std::cout << "Shoot projectile." << std::endl;
}

void HeavySpaceBug::RenderSpaceBug(SDL_Renderer *gameRenderer)
{
      SDL_Surface *surf = IMG_Load("./assets/heavy_space_bug.png");
      SDL_Texture *tex = SDL_CreateTextureFromSurface(gameRenderer, surf);
      SDL_FreeSurface(surf);
      spaceBugRect = {static_cast<int>(spaceBugPos.x), static_cast<int>(spaceBugPos.y), 64, 64};
      SDL_RenderCopy(gameRenderer, tex, NULL, &spaceBugRect);
      SDL_DestroyTexture(tex);
}
