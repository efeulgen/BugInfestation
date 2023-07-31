
#ifndef DRONE_H
#define DRONE_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include "../Projectile.h"
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
      std::vector<Projectile *> projectiles;
      double projectileDamage;

      const char *minorExplosionSpriteSheet[4] = {"./assets/sprites/drone_minorExplosion_1.png", "./assets/sprites/drone_minorExplosion_2.png", "./assets/sprites/drone_minorExplosion_3.png", "./assets/sprites/drone_minorExplosion_4.png"};
      double minorExplosionAnimIndex = 0.0;
      bool isRenderingMinorExplosion = false;
      SDL_Rect *collisionRect;

public:
      Drone(glm::vec2 pos, glm::vec2 dir);
      virtual ~Drone();
      virtual void UpdateDrone(double deltaTime);
      virtual void RenderDrone(SDL_Renderer *renderer);
      void DestroyDrone();
      void GetDamage();
      bool CheckCollision(SDL_Rect other) const;
      void EraseElementFromProjarray(Projectile *proj);
      void RenderMinorExplosion(SDL_Renderer *renderer);

      // getters & setters
      bool GetIsDead() const { return isDead; }
      bool GetIsDestructible() { return isDestructible; }
      DroneType GetDroneType() { return droneType; }
      std::vector<Projectile *> GetProjectiles() { return projectiles; }
      double GetProjectileDamage() { return projectileDamage; }
      SDL_Rect GetDroneRect() const { return droneRect; }
};

#endif
