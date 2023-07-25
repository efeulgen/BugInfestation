
#include "TrippleLaserShootingDrone.h"

TrippleLaserShootingDrone::TrippleLaserShootingDrone(glm::vec2 pos, glm::vec2 vel) : Drone(pos, vel)
{
      std::cout << "TrippleLaserShootingDrone Constructor" << std::endl;

      imgPath = "./assets/sprites/TrippleLaserDrone.png";
      droneRectSize = 64;

      fireCounter = TRIPPLELASERSHOOTINGDRONE_FIRE_RATE;
      fireIntervalCounter = 0.0;
      fireIntervalSetBackCounter = 0.0;

      rectCenter = glm::vec2((static_cast<double>(position.x + droneRectSize)) / 2.0, (static_cast<double>(position.y + droneRectSize)) / 2.0);
      fireDirCtoUp = glm::normalize(glm::vec2((static_cast<double>(position.x + droneRectSize)) / 2.0, position.y) - rectCenter);
      // fireDirCtoBottomL = glm::normalize(glm::vec2(droneRect.x, droneRect.y + droneRect.h) - rectCenter);
      // fireDirCtoBottomR = glm::normalize(glm::vec2((droneRect.x + droneRect.w), droneRect.y + droneRect.h) - rectCenter);
}

TrippleLaserShootingDrone::~TrippleLaserShootingDrone()
{
      std::cout << "TrippleLaserShootingDrone Destructor" << std::endl;
}

void TrippleLaserShootingDrone::UpdateDrone(double deltaTime)
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
            isDestructible = true;
      }

      // rotate
      angle += (deltaTime * rotationSpeed);

      UpdateLaserFirePoints(rectCenter, fireDirCtoUp, fireDirCtoBottomL, fireDirCtoBottomR, deltaTime);

      Drone::UpdateDrone(deltaTime);
}

void TrippleLaserShootingDrone::RenderDrone(SDL_Renderer *renderer)
{
      for (auto projectile : projectiles)
      {
            projectile->RenderProjectile(renderer, spritesheet, TRIPPLELASERSHOOTINGDRONE_PROJ_SPRITESHEET_SIZE);
      }

      if (isDead)
      {
            return;
      }

      SDL_Surface *surf = IMG_Load(imgPath);
      SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
      SDL_FreeSurface(surf);
      droneRect = {static_cast<int>(position.x), static_cast<int>(position.y), droneRectSize, droneRectSize};
      SDL_RenderCopyEx(renderer, tex, NULL, &droneRect, angle, NULL, SDL_FLIP_NONE);
      SDL_DestroyTexture(tex);
}

void TrippleLaserShootingDrone::ShootLaser()
{
      Projectile *newProj1 = new Projectile(fireDirCtoUp, 1000.0);
      newProj1->SetProjectilePosition(rectCenter);
      projectiles.push_back(newProj1);

      /*
      Projectile *newProj2 = new Projectile(fireDirCtoBottomL, 1000.0);
      newProj2->SetProjectilePosition(rectCenter);
      projectiles.push_back(newProj2);

      Projectile *newProj3 = new Projectile(fireDirCtoBottomR, 1000.0);
      newProj3->SetProjectilePosition(rectCenter);
      projectiles.push_back(newProj3);*/
}

void TrippleLaserShootingDrone::UpdateLaserFirePoints(glm::vec2 rectCenter, glm::vec2 cToUp, glm::vec2 cToBottomL, glm::vec2 cToBottomR, double deltaTime)
{
      // update position
      rectCenter.x += velocity.x * deltaTime;
      rectCenter.y += velocity.y * deltaTime;

      cToUp.x += velocity.x * deltaTime;
      cToUp.y += velocity.y * deltaTime;
      cToUp = glm::normalize(cToUp);

      /*
      cToBottomL.x += velocity.x * deltaTime;
      cToBottomL.y += velocity.y * deltaTime;
      cToBottomL = glm::normalize(cToBottomL);

      cToBottomR.x += velocity.x * deltaTime;
      cToBottomR.y += velocity.y * deltaTime;
      cToBottomR = glm::normalize(cToBottomR);
      */

      // update rotation
      float angleRadians = glm::radians(angle);
      glm::mat2 rotationMatrix(cos(angleRadians), -sin(angleRadians),
                               sin(angleRadians), cos(angleRadians));

      cToUp = cToUp - rectCenter;
      cToUp = rotationMatrix * cToUp;
      cToUp += rectCenter;
      /*
      cToBottomL = rotationMatrix * cToBottomL;
      cToBottomR = rotationMatrix * cToBottomR;*/
}
