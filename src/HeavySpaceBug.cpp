
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

void HeavySpaceBug::ShootProjectile(glm::vec2 playerPos)
{
      glm::vec2 playerDirection = glm::normalize(playerPos - spaceBugPos);
      Projectile *newProjectile = new Projectile(playerDirection, 300.0);
      newProjectile->SetProjectilePosition(spaceBugPos);
      projArray.push_back(newProjectile);
}

void HeavySpaceBug::UpdateSpaceBug(double deltaTime, glm::vec2 playerPos)
{
      SpaceBug::UpdateSpaceBug(deltaTime);

      if (fireCounter < BUG_FIRE_RATE)
      {
            fireCounter += deltaTime;
      }
      else
      {
            ShootProjectile(playerPos);
            fireCounter = 0.0;
      }

      for (auto proj : projArray)
      {
            proj->UpdateProjectile(deltaTime);
      }
}

void HeavySpaceBug::RenderSpaceBug(SDL_Renderer *gameRenderer)
{
      SDL_Surface *surf = IMG_Load("./assets/heavy_space_bug.png");
      SDL_Texture *tex = SDL_CreateTextureFromSurface(gameRenderer, surf);
      SDL_FreeSurface(surf);
      spaceBugRect = {static_cast<int>(spaceBugPos.x), static_cast<int>(spaceBugPos.y), 64, 64};
      SDL_RenderCopy(gameRenderer, tex, NULL, &spaceBugRect);
      SDL_DestroyTexture(tex);

      for (auto proj : projArray)
      {
            proj->RenderProjectile(gameRenderer, bugProjectileSpritesheet, BUG_PROJECTILE_SPRITESHEET_SIZE);
      }
}
