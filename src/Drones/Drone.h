
#ifndef DRONE_H
#define DRONE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

class Drone
{
protected:
      glm::vec2 position;
      glm::vec2 velocity;
      const char *imgPath;
      SDL_Rect droneRect;

      int health = 3;
      bool isDead = false;
      bool isDestructible = false;
      bool isFlipped = false;

public:
      Drone(glm::vec2 pos, glm::vec2 vel);
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
