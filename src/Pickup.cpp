
#include "Pickup.h"

Pickup::Pickup(PickupType pickupType) : type{pickupType}
{
      std::cout << "Pickup Constructor" << std::endl;
}

Pickup::~Pickup()
{
      std::cout << "Pickup Destructor" << std::endl;
}

void Pickup::Update(double deltaTime)
{
      pos += speed;
}

void Pickup::Render(SDL_Renderer *gameRenderer)
{
}

void Pickup::DestroyPickup()
{
      delete this;
}

void Pickup::CheckCollisionWithPlayer(SDL_Rect playerRect)
{
      if (SDL_HasIntersection(&rect, &playerRect))
      {
            if (type == PickupType::HealthPickup)
            {
                  // heal player
            }
            else if (type == PickupType::ExtraLifePickup)
            {
                  // give extra life
            }
            else if (type == PickupType::RocketPickup)
            {
                  // give rocket
            }
            else if (type == PickupType::SpeedBoostPickup)
            {
                  // give speed boost
            }
      }
}