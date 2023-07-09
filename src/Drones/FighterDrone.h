
#ifndef FIGHTERDRONE_H
#define FIGHTERDRONE_H

#include <iostream>
#include <vector>
#include "Drone.h"
#include "../Projectile.h"

const int FIGHTERDRONE_PROJ_SPRITESHEET_SIZE = 1;

class FighterDrone : public Drone
{
private:
      std::vector<Projectile *> projectiles;
      const char *spritesheet[FIGHTERDRONE_PROJ_SPRITESHEET_SIZE] = {"./assets/sprites/PlayerProjectile.png"};

public:
      FighterDrone(glm::vec2 pos, glm::vec2 vel);
      ~FighterDrone();

      void UpdateDrone(double deltaTime) override;
      void RenderDrone(SDL_Renderer *renderer) override;
      void ShootLaser();
};

#endif
