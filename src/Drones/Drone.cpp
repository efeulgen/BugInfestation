
#include "Drone.h"

Drone::Drone(glm::vec2 pos, glm::vec2 vel) : position{pos}, velocity{vel}, droneRect{0, 0, 0, 0}
{
      std::cout << "Drone Constructor" << std::endl;
}

Drone::~Drone()
{
      std::cout << "Drone Destructor" << std::endl;
}

void Drone::UpdateDrone(double deltaTime)
{
      position.x += velocity.x * deltaTime;
      position.y += velocity.y * deltaTime;
}

void Drone::RenderDrone(SDL_Renderer *renderer)
{
      SDL_Surface *surf = IMG_Load(imgPath);
      SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
      SDL_FreeSurface(surf);
      droneRect = {static_cast<int>(position.x), static_cast<int>(position.y), 150, 150};
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
}

void Drone::DestroyDrone()
{
      delete this;
}

void Drone::GetDamage()
{
      health--;
      if (health <= 0)
      {
            isDead = true;
      }
}

bool Drone::CheckCollision(SDL_Rect other) const
{
      if (SDL_HasIntersection(&droneRect, &other))
      {
            return true;
      }
      return false;
}
