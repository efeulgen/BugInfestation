
#ifndef TRIPPLELASERSHOOTINGDRONE_H
#define TRIPPLELASERSHOOTINGDRONE_H

#include "Drone.h"

class TrippleLaserShootingDrone : public Drone
{
public:
      TrippleLaserShootingDrone(glm::vec2 pos, glm::vec2 vel);
      ~TrippleLaserShootingDrone();
};

#endif
