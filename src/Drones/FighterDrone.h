
#ifndef FIGHTERDRONE_H
#define FIGHTERDRONE_H

#include <iostream>
#include <cstdlib>
#include "Drone.h"

const double FIGHTERDRONE_FIRE_RATE = 2.5;

class FighterDrone : public Drone
{
private:
      std::vector<std::string> spritesheet = {"./assets/sprites/PlayerProjectile.png"}; // for debug: change later
      double fireCounter;
      bool isRtoL;

      Mix_Chunk *laserSound = nullptr;

      const char *majorExplosionSpriteSheet[4] = {"./assets/sprites/drone_minorExplosion_1.png", "./assets/sprites/drone_minorExplosion_2.png", "./assets/sprites/drone_minorExplosion_3.png", "./assets/sprites/drone_minorExplosion_4.png"}; // for testing purposes : change later, unique for every drone
      double majorExplosionAnimCounter = 0.0;
      bool donePlayingMajorExplosion = false;

public:
      FighterDrone(glm::vec2 pos, glm::vec2 dir);
      ~FighterDrone();

      void UpdateDrone(double deltaTime) override;
      void RenderDrone(SDL_Renderer *renderer) override;
      void ShootLaser();

      // getters & setters
      std::vector<Projectile *> GetProjectiles() { return projectiles; }
};

#endif
