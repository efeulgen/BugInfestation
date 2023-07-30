
#ifndef FIGHTERDRONE_H
#define FIGHTERDRONE_H

#include <iostream>
#include <cstdlib>
#include <SDL2/SDL_mixer.h>
#include "Drone.h"

const int FIGHTERDRONE_PROJ_SPRITESHEET_SIZE = 1;
const double FIGHTERDRONE_FIRE_RATE = 2.5;

class FighterDrone : public Drone
{
private:
      const char *spritesheet[FIGHTERDRONE_PROJ_SPRITESHEET_SIZE] = {"./assets/sprites/PlayerProjectile.png"}; // for debug: change later
      double fireCounter;
      bool isRtoL;

      Mix_Chunk *laserSound = nullptr;

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
