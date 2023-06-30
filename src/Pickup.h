
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
      ExtraLifePickup,
      RocketPickup
};

class Pickup
{
private:
      PickupType type;
      SDL_Rect rect;
      const char *imgPath;

      glm::vec2 pos;
      glm::vec2 speed;

public:
      Pickup(glm::vec2 initPos, glm::vec2 initSpeed, int seed);
      ~Pickup();

      void Update(double deltaTime);
      void Render(SDL_Renderer *gameRenderer);
      void DestroyPickup();
      bool CheckCollisionWithPlayer(SDL_Rect playerRect, Player *mainPlayer);

      glm::vec2 GetPickupPos() { return pos; }
};

#endif
