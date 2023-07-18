
#include "FighterDrone.h"

FighterDrone::FighterDrone(glm::vec2 pos, glm::vec2 vel) : Drone(pos, vel)
{
      std::cout << "FighterDrone Constructor" << std::endl;

      imgPath = "./assets/sprites/AlienFighterJet_body.png";
      fireCounter = FIGHTERDRONE_FIRE_RATE - 0.5;
      isRtoL = pos.x >= 1300.0 ? true : false;
      isFlipped = isRtoL ? false : true;
}

FighterDrone::~FighterDrone()
{
      std::cout << "FighterDrone Destructor" << std::endl;
}

void FighterDrone::UpdateDrone(double deltaTime)
{
      for (auto proj : projectiles)
      {
            proj->UpdateProjectile(deltaTime);
      }

      if (isDead)
      {
            return;
      }

      // fire
      if (fireCounter < FIGHTERDRONE_FIRE_RATE)
      {
            fireCounter += deltaTime;
      }
      else
      {
            ShootLaser();
            fireCounter = 0.0;
      }

      Drone::UpdateDrone(deltaTime);
}

void FighterDrone::RenderDrone(SDL_Renderer *renderer)
{
      for (auto projectile : projectiles)
      {
            projectile->RenderProjectile(renderer, spritesheet, FIGHTERDRONE_PROJ_SPRITESHEET_SIZE);
      }

      if (isDead)
      {
            if (projectiles.empty())
            {
                  isDestructible = true;
            }
            return;
      }

      Drone::RenderDrone(renderer);
}

void FighterDrone::ShootLaser()
{
      Projectile *newProj = isRtoL ? new Projectile(glm::vec2(-1, 0), 1000.0) : new Projectile(glm::vec2(1, 0), 1000.0);
      glm::vec2 fireOffset = isRtoL ? glm::vec2(0.0, 75.0) : glm::vec2(150.0, 75.0);
      newProj->SetProjectilePosition(position + fireOffset);
      projectiles.push_back(newProj);
}
