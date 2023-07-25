
#ifndef TRIPPLELASERSHOOTINGDRONE_H
#define TRIPPLELASERSHOOTINGDRONE_H

#include <vector>
#include "Drone.h"
#include "../Projectile.h"

const int TRIPPLELASERSHOOTINGDRONE_PROJ_SPRITESHEET_SIZE = 1;
const double TRIPPLELASERSHOOTINGDRONE_FIRE_RATE = 0.5;
const double TRIPPLELASERSHOOTINGDRONE_FIRE_INTERVAL = 3.0;

class TrippleLaserShootingDrone : public Drone
{
private:
      std::vector<Projectile *> projectiles;
      const char *spritesheet[TRIPPLELASERSHOOTINGDRONE_PROJ_SPRITESHEET_SIZE] = {"./assets/sprites/PlayerProjectile.png"}; // for debug: change later
      double fireCounter;
      double fireIntervalCounter;
      double fireIntervalSetBackCounter;
      bool canFire = true;

      double angle = 0.0;
      double rotationSpeed = 10.0;

      glm::vec2 rectCenter;
      glm::vec2 fireDirCtoUp;
      glm::vec2 fireDirCtoBottomL;
      glm::vec2 fireDirCtoBottomR;
      // int fireVectorIndex = 0;

public:
      TrippleLaserShootingDrone(glm::vec2 pos, glm::vec2 vel);
      ~TrippleLaserShootingDrone();

      void UpdateDrone(double deltaTime) override;
      void RenderDrone(SDL_Renderer *renderer) override;
      void ShootLaser();
      void UpdateLaserFirePoints(glm::vec2 rectCenter, glm::vec2 cToUp, glm::vec2 cToBottomL, glm::vec2 cToBottomR, double deltaTime);
};

#endif
