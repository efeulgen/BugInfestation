
#ifndef DRONE_H
#define DRONE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include "../Logger/Logger.h"

enum DroneType
{
      DT_FighterDrone,
      DT_TrippleLaserShootingDrone,
      DT_SeekAndDestroyDrone
};

class Drone
{
protected:
      glm::vec2 position;
      glm::vec2 direction;
      const char *imgPath;
      SDL_Rect droneRect;
      int droneRectSize;
      double droneSpeed;

      int health = 3;
      bool isDead = false;
      bool isDestructible = false;
      bool isFlipped = false;

      DroneType droneType;

public:
      Drone(glm::vec2 pos, glm::vec2 dir);
      virtual ~Drone();
      virtual void UpdateDrone(double deltaTime);
      virtual void RenderDrone(SDL_Renderer *renderer);
      void DestroyDrone();
      void GetDamage();
      bool CheckCollision(SDL_Rect other) const;

      // getters & setters
      bool GetIsDestructible() { return isDestructible; }
};

#endif
