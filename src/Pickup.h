
#ifndef PICKUP_H
#define PICKUP_H

#include <iostream>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

enum PickupType
{
      HealthPickup,
      SpeedBoostPickup,
      ExtraLifePickup,
      RocketPickup
};

class Pickup
{
private:
      PickupType type;
      SDL_Rect rect;

      glm::vec2 pos;
      glm::vec2 speed;

public:
      Pickup(PickupType pickupType);
      ~Pickup();

      void Update(double deltaTime);
      void Render(SDL_Renderer *gameRenderer);
      void DestroyPickup();

      void CheckCollisionWithPlayer(SDL_Rect playerRect);
};

#endif
