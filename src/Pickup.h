
#ifndef PICKUP_H
#define PICKUP_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

#include "Player.h"

enum PickupType
{
      HealthPickup,
      SpeedBoostPickup,
      FireRateBoost,
      ExtraLifePickup,
      RocketPickup
};

class Pickup
{
private:
      PickupType type;
      const char *imgPath;

      glm::vec2 pos;
      glm::vec2 speed;
      SDL_Rect rect;

public:
      Pickup(glm::vec2 initPos, glm::vec2 initSpeed, int seed);
      ~Pickup();

      void Update(double deltaTime);
      void Render(SDL_Renderer *gameRenderer);
      void DestroyPickup();
      bool CheckCollisionWithPlayer(SDL_Rect playerRect, Player *mainPlayer);

      // getters & setters
      glm::vec2 GetPickupPos() const { return pos; }
      PickupType GetPickupType() const { return type; }
};

#endif
