
#include "Drone.h"

Drone::Drone(glm::vec2 pos, glm::vec2 dir) : position{pos}, direction{dir}, droneRect{0, 0, 0, 0}
{
      std::cout << "Drone Constructor" << std::endl;

      collisionRect = new SDL_Rect();
}

Drone::~Drone()
{
      std::cout << "Drone Destructor" << std::endl;
}

void Drone::UpdateDrone(double deltaTime)
{
      position.x += direction.x * deltaTime * droneSpeed;
      position.y += direction.y * deltaTime * droneSpeed;

      // update anim index
      if (isRenderingMinorExplosion)
      {
            minorExplosionAnimIndex += deltaTime * 8.0;
      }
}

void Drone::RenderDrone(SDL_Renderer *renderer)
{
      SDL_Surface *surf = IMG_Load(imgPath);
      SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
      SDL_FreeSurface(surf);
      droneRect = {static_cast<int>(position.x), static_cast<int>(position.y), droneRectSize, droneRectSize};
      if (isFlipped)
      {
            SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
            SDL_RenderCopyEx(renderer, tex, NULL, &droneRect, 0.0, NULL, flip);
      }
      else
      {
            SDL_RenderCopy(renderer, tex, NULL, &droneRect);
      }
      SDL_DestroyTexture(tex);

      if (isRenderingMinorExplosion)
      {
            RenderMinorExplosion(renderer);
      }
}

void Drone::DestroyDrone()
{
      delete this;
}

void Drone::GetDamage()
{
      health--;
      isRenderingMinorExplosion = true;
      if (health <= 0)
      {
            isDead = true;
      }
}

bool Drone::CheckCollision(SDL_Rect other) const
{
      if (SDL_HasIntersection(&droneRect, &other) && !isDead)
      {
            SDL_IntersectRect(&droneRect, &other, collisionRect);
            return true;
      }
      return false;
}

void Drone::EraseElementFromProjarray(Projectile *proj)
{
      projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), proj), projectiles.end());
}

void Drone::RenderMinorExplosion(SDL_Renderer *renderer)
{
      SDL_Surface *surf = IMG_Load(minorExplosionSpriteSheet[static_cast<int>(minorExplosionAnimIndex)]);
      SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
      SDL_FreeSurface(surf);
      SDL_Rect rect = {static_cast<int>(collisionRect->x), static_cast<int>(collisionRect->y), 80, 80};
      SDL_RenderCopy(renderer, tex, NULL, &rect);
      SDL_DestroyTexture(tex);

      if (static_cast<int>(minorExplosionAnimIndex) >= 3)
      {
            isRenderingMinorExplosion = false;
            minorExplosionAnimIndex = 0.0;
      }
}
