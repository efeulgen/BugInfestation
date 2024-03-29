
#include "TrippleLaserShootingDrone.h"

TrippleLaserShootingDrone::TrippleLaserShootingDrone(glm::vec2 pos, glm::vec2 dir) : Drone(pos, dir)
{
      Logger::Log("TrippleLaserShootingDrone Constructor");

      imgPath = "./assets/sprites/TrippleLaserDrone.png";
      droneRectSize = 64;
      droneType = DroneType::DT_TrippleLaserShootingDrone;
      droneSpeed = 120.0;
      projectileDamage = 2.0;

      fireCounter = TRIPPLELASERSHOOTINGDRONE_FIRE_RATE;
      fireIntervalCounter = 0.0;
      fireIntervalSetBackCounter = 0.0;

      rectCenter = glm::vec2(pos.x + static_cast<double>(droneRectSize) / 2.0, pos.y + static_cast<double>(droneRectSize) / 2.0);
      up = glm::normalize(glm::vec2(0, -1));
      bottomL = glm::normalize(glm::vec2(-1, 1));
      bottomR = glm::normalize(glm::vec2(1, 1));

      trippleLaserDroneLaser = Mix_LoadMUS("./audio/fighter_drone_laser.wav");
      if (trippleLaserDroneLaser == NULL)
      {
            Logger::Err("Failed to load music.");
      }
}

TrippleLaserShootingDrone::~TrippleLaserShootingDrone()
{
      Logger::Log("TrippleLaserShootingDrone Destructor");

      Mix_FreeMusic(trippleLaserDroneLaser);
}

void TrippleLaserShootingDrone::UpdateDrone(double deltaTime)
{
      for (auto proj : projectiles)
      {
            proj->UpdateProjectile(deltaTime);
            if ((std::abs(proj->GetProjectilePosition().x - position.x) > 1400.0 || std::abs(proj->GetProjectilePosition().y - position.y) > 1400.0))
            {
                  projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), proj), projectiles.end());
                  proj->Destroy();
                  proj = nullptr;
                  break;
            }
      }

      if (isDead)
      {
            canFire = false;
            majorExplosionAnimCounter += deltaTime * 8.0;

            if (projectiles.empty() && donePlayingMajorExplosion)
            {
                  isDestructible = true;
            }
            return;
      }

      // fire
      fireIntervalCounter += deltaTime;
      if (canFire)
      {
            if (fireCounter < TRIPPLELASERSHOOTINGDRONE_FIRE_RATE)
            {
                  fireCounter += deltaTime;
            }
            else
            {
                  ShootLaser();
                  fireCounter = 0.0;
            }
      }
      if (fireIntervalCounter > TRIPPLELASERSHOOTINGDRONE_FIRE_INTERVAL)
      {
            fireIntervalSetBackCounter += deltaTime;
            canFire = false;
            if (fireIntervalSetBackCounter > 3.0)
            {
                  fireIntervalCounter = 0.0;
                  fireIntervalSetBackCounter = 0.0;
                  canFire = true;
            }
      }

      // bound check
      if (position.x < -300.0 || position.x > 1500.0 || position.y < -300.0 || position.y > 1500.0)
      {
            isDead = true;
      }

      // rotate
      angle += (deltaTime * rotationSpeed);
      UpdateLaserFirePoints(); // TODO : debug

      Drone::UpdateDrone(deltaTime);
}

void TrippleLaserShootingDrone::RenderDrone(SDL_Renderer *renderer)
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
                  SDL_Rect rect = {static_cast<int>(position.x), static_cast<int>(position.y), droneRectSize * 2, droneRectSize * 2};
                  SDL_RenderCopy(renderer, tex, NULL, &rect);
                  SDL_DestroyTexture(tex);

                  if (static_cast<int>(majorExplosionAnimCounter) >= 3)
                  {
                        donePlayingMajorExplosion = true;
                  }
            }
            return;
      }

      SDL_Surface *surf = IMG_Load(imgPath);
      SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
      SDL_FreeSurface(surf);
      droneRect = {static_cast<int>(position.x), static_cast<int>(position.y), droneRectSize, droneRectSize};
      rectCenter = glm::vec2(position.x + static_cast<double>(droneRectSize) / 2.0, position.y + static_cast<double>(droneRectSize) / 2.0);
      SDL_RenderCopyEx(renderer, tex, NULL, &droneRect, angle, NULL, SDL_FLIP_NONE);
      SDL_DestroyTexture(tex);

      if (isRenderingMinorExplosion)
      {
            Drone::RenderMinorExplosion(renderer);
      }
}

void TrippleLaserShootingDrone::ShootLaser()
{
      Projectile *newProj1 = new Projectile(up, 1000.0, spritesheet, 5);
      newProj1->SetProjectilePosition(rectCenter);
      projectiles.push_back(newProj1);
      Mix_PlayMusic(trippleLaserDroneLaser, 0);

      Projectile *newProj2 = new Projectile(bottomL, 1000.0, spritesheet, 5);
      newProj2->SetProjectilePosition(rectCenter);
      projectiles.push_back(newProj2);
      Mix_PlayMusic(trippleLaserDroneLaser, 0);

      Projectile *newProj3 = new Projectile(bottomR, 1000.0, spritesheet, 5);
      newProj3->SetProjectilePosition(rectCenter);
      projectiles.push_back(newProj3);
      Mix_PlayMusic(trippleLaserDroneLaser, 0);
}

void TrippleLaserShootingDrone::UpdateLaserFirePoints()
{
      float angleRadians = glm::radians(1.0f);
      glm::mat2 rotationMatrix(cos(angleRadians), -sin(angleRadians),
                               sin(angleRadians), cos(angleRadians));

      up = rotationMatrix * up;
      up = glm::normalize(up);

      bottomL = rotationMatrix * bottomL;
      bottomL = glm::normalize(bottomL);

      bottomR = rotationMatrix * bottomR;
      bottomR = glm::normalize(bottomR);
}
