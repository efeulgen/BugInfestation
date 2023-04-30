
#include "HeavySpaceBug.h"
#include <iostream>
#include <SDL2/SDL_image.h>

HeavySpaceBug::HeavySpaceBug()
{
}

HeavySpaceBug::HeavySpaceBug(glm::vec2 pos, glm::vec2 dir) : SpaceBug(pos, dir), fireCounter(BUG_FIRE_RATE)
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

void HeavySpaceBug::ShootProjectile(Player *player)
{
      glm::vec2 playerDirection = glm::normalize(player->GetPlayerPos() - spaceBugPos);
      Projectile *newProjectile = new Projectile(playerDirection, 300.0);
      newProjectile->SetProjectilePosition(spaceBugPos);
      projArray.push_back(newProjectile);
}

void HeavySpaceBug::UpdateSpaceBug(double deltaTime, Player *player)
{
      SpaceBug::UpdateSpaceBug(deltaTime, player);

      if (fireCounter < BUG_FIRE_RATE)
      {
            fireCounter += deltaTime;
      }
      else if (player)
      {
            ShootProjectile(player);
            fireCounter = 0.0;
      }

      for (auto proj : projArray)
      {
            proj->UpdateProjectile(deltaTime);
            if (proj->GetProjectilePosition().x <= -10 || proj->GetProjectilePosition().x >= 1300 || proj->GetProjectilePosition().y <= -100 || proj->GetProjectilePosition().y >= 900)
            {
                  projArray.erase(std::remove(projArray.begin(), projArray.end(), proj), projArray.end());
                  proj->Destroy();
                  proj = nullptr;
            }
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
