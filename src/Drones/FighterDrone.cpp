
#include "FighterDrone.h"

FighterDrone::FighterDrone(glm::vec2 pos, glm::vec2 vel) : Drone(pos, vel)
{
      std::cout << "FighterDrone Constructor" << std::endl;

      imgPath = "./assets/sprites/AlienFighterJet_body.png";
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
      projectiles.push_back(new Projectile(glm::vec2(-1, 0), 200.0));
}
