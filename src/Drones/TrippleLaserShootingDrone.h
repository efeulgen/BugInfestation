
#ifndef TRIPPLELASERSHOOTINGDRONE_H
#define TRIPPLELASERSHOOTINGDRONE_H

#include "Drone.h"

const int TRIPPLELASERSHOOTINGDRONE_PROJ_SPRITESHEET_SIZE = 1;
const double TRIPPLELASERSHOOTINGDRONE_FIRE_RATE = 0.1;
const double TRIPPLELASERSHOOTINGDRONE_FIRE_INTERVAL = 3.0;

class TrippleLaserShootingDrone : public Drone
{
private:
      const char *spritesheet[TRIPPLELASERSHOOTINGDRONE_PROJ_SPRITESHEET_SIZE] = {"./assets/sprites/TrippleLaserDroneLaser.png"};
      double fireCounter;
      double fireIntervalCounter;
      double fireIntervalSetBackCounter;
      bool canFire = true;

      double angle = 0.0;
      double rotationSpeed = 30.0;

      glm::vec2 rectCenter;
      glm::vec2 up;
      glm::vec2 bottomL;
      glm::vec2 bottomR;

public:
      TrippleLaserShootingDrone(glm::vec2 pos, glm::vec2 dir);
      ~TrippleLaserShootingDrone();

      void UpdateDrone(double deltaTime) override;
      void RenderDrone(SDL_Renderer *renderer) override;
      void ShootLaser();
      void UpdateLaserFirePoints();
};

#endif
