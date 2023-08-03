
#include "HeavySpaceBug.h"
#include <iostream>
#include <SDL2/SDL_image.h>

HeavySpaceBug::HeavySpaceBug()
{
}

HeavySpaceBug::HeavySpaceBug(glm::vec2 pos, glm::vec2 dir) : SpaceBug(pos, dir), fireCounter(BUG_FIRE_RATE)
{
      health = 3;
      type = BugType::Heavy;
}

void HeavySpaceBug::GetDamage(int amount)
{
      health -= amount;
      if (health <= 0)
      {
            isDead = true;
            canDamagePlayer = false;
      }
}

void HeavySpaceBug::ShootProjectile(Player *player)
{
      glm::vec2 playerDirection = glm::normalize(player->GetPlayerPos() - spaceBugPos);
      Projectile *newProjectile = new Projectile(playerDirection, 300.0, bugProjectileSpritesheet);
      newProjectile->SetProjectilePosition(spaceBugPos);
      projArray.push_back(newProjectile);
}

void HeavySpaceBug::UpdateSpaceBug(double deltaTime, Player *player)
{
      for (auto proj : projArray)
      {
            proj->UpdateProjectile(deltaTime);
            if (proj->GetProjectilePosition().x <= -10 || proj->GetProjectilePosition().x >= 1300 || proj->GetProjectilePosition().y <= -100 || proj->GetProjectilePosition().y >= 900)
            {
                  projArray.erase(std::remove(projArray.begin(), projArray.end(), proj), projArray.end());
                  proj->Destroy();
                  proj = nullptr;
                  break;
            }
      }

      if (isDead)
      {
            explodeAnimIndex += deltaTime * 10.0;
            if (projArray.empty() && donePlayingExplodeAnim)
            {
                  isDestructible = true;
            }
            return;
      }

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

      heavyBugSpriteSheetIndex += deltaTime * 10.0;
}

void HeavySpaceBug::RenderSpaceBug(SDL_Renderer *gameRenderer)
{
      for (auto proj : projArray)
      {
            proj->RenderProjectile(gameRenderer);
      }
      if (isDead)
      {
            if (!donePlayingExplodeAnim)
            {
                  SDL_Surface *surf = IMG_Load(bugExplodeSpriteSheet[static_cast<int>(explodeAnimIndex)]);
                  SDL_Texture *tex = SDL_CreateTextureFromSurface(gameRenderer, surf);
                  SDL_FreeSurface(surf);
                  spaceBugRect = {static_cast<int>(spaceBugPos.x), static_cast<int>(spaceBugPos.y), 64, 64};
                  SDL_RenderCopy(gameRenderer, tex, NULL, &spaceBugRect);
                  SDL_DestroyTexture(tex);

                  if (static_cast<int>(explodeAnimIndex) >= 6)
                  {
                        donePlayingExplodeAnim = true;
                  }
            }
            return;
      }

      // render bug
      if (static_cast<int>(heavyBugSpriteSheetIndex) > 3)
      {
            heavyBugSpriteSheetIndex = 0.0;
      }
      SDL_Surface *surf = IMG_Load(heavyBugSpriteSheet[static_cast<int>(heavyBugSpriteSheetIndex)]);
      SDL_Texture *tex = SDL_CreateTextureFromSurface(gameRenderer, surf);
      SDL_FreeSurface(surf);
      spaceBugRect = {static_cast<int>(spaceBugPos.x), static_cast<int>(spaceBugPos.y), 64, 64};

      if (isFlipped)
      {
            SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
            SDL_RenderCopyEx(gameRenderer, tex, NULL, &spaceBugRect, 0.0, NULL, flip);
      }
      else
      {
            SDL_RenderCopy(gameRenderer, tex, NULL, &spaceBugRect);
      }

      SDL_DestroyTexture(tex);
}
