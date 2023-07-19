
#include "FighterDrone.h"

FighterDrone::FighterDrone(glm::vec2 pos, glm::vec2 vel) : Drone(pos, vel)
{
      std::cout << "FighterDrone Constructor" << std::endl;

      imgPath = "./assets/sprites/AlienFighterJet_body.png";
      fireCounter = FIGHTERDRONE_FIRE_RATE - 0.5;
      isRtoL = pos.x >= 1300.0 ? true : false;
      isFlipped = isRtoL ? false : true;
      laserSound = Mix_LoadWAV("./audio/fighter_drone_laser.wav");
      if (laserSound == NULL)
      {
            Logger::Err("Fighter Drone laser sound isn't loaded.");
      }
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
            if (std::abs(proj->GetProjectilePosition().x - position.x) > 1400.0)
            {
                  projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), proj), projectiles.end());
                  proj->Destroy();
                  proj = nullptr;
            }
      }

      if (isDead)
      {
            if (projectiles.empty())
            {
                  isDestructible = true;
            }
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

      // bound check
      if ((isRtoL && position.x < -200.0) || (!isRtoL && position.x > 1300.0))
      {
            isDestructible = true;
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
            return;
      }

      Drone::RenderDrone(renderer);
}

void FighterDrone::ShootLaser()
{
      Mix_PlayChannel(-1, laserSound, 0);
      Projectile *newProj = isRtoL ? new Projectile(glm::vec2(-1, 0), 1000.0) : new Projectile(glm::vec2(1, 0), 1000.0);
      glm::vec2 fireOffset = isRtoL ? glm::vec2(0.0, 75.0) : glm::vec2(150.0, 75.0);
      newProj->SetProjectilePosition(position + fireOffset);
      projectiles.push_back(newProj);
}
