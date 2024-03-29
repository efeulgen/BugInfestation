
#include "FighterDrone.h"

FighterDrone::FighterDrone(glm::vec2 pos, glm::vec2 dir) : Drone(pos, dir)
{
      Logger::Log("FighterDrone Constructor");

      imgPath = "./assets/sprites/AlienFighterJet_body.png";
      droneRectSize = 150;
      droneType = DroneType::DT_FighterDrone;
      droneSpeed = 200.0;
      projectileDamage = 10.0;

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
      Logger::Log("FighterDrone Destructor");

      Mix_FreeChunk(laserSound);
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
                  break;
            }
      }

      if (isDead)
      {
            majorExplosionAnimCounter += deltaTime * 8.0;

            if (projectiles.empty() && donePlayingMajorExplosion)
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
            isDead = true;
      }

      Drone::UpdateDrone(deltaTime);
}

void FighterDrone::RenderDrone(SDL_Renderer *renderer)
{
      for (auto projectile : projectiles)
      {
            projectile->RenderProjectile(renderer);
      }

      if (isDead)
      {
            if (!donePlayingMajorExplosion)
            {
                  SDL_Surface *surf = IMG_Load(majorExplosionSpriteSheet[static_cast<int>(majorExplosionAnimCounter)]);
                  SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
                  SDL_FreeSurface(surf);
                  SDL_Rect rect = {static_cast<int>(position.x), static_cast<int>(position.y), droneRectSize, droneRectSize};
                  SDL_RenderCopy(renderer, tex, NULL, &rect);
                  SDL_DestroyTexture(tex);

                  if (static_cast<int>(majorExplosionAnimCounter) >= 3)
                  {
                        donePlayingMajorExplosion = true;
                  }
            }
            return;
      }

      Drone::RenderDrone(renderer);
}

void FighterDrone::ShootLaser()
{
      Mix_PlayChannel(-1, laserSound, 0);
      Projectile *newProj = isRtoL ? new Projectile(glm::vec2(-1, 0), 1000.0, spritesheet) : new Projectile(glm::vec2(1, 0), 1000.0, spritesheet);
      glm::vec2 fireOffset = isRtoL ? glm::vec2(0.0, 75.0) : glm::vec2(150.0, 75.0);
      newProj->SetProjectilePosition(position + fireOffset);
      projectiles.push_back(newProj);
}
