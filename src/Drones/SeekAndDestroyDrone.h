
#ifndef SEEKANDDESTROYDRONE_H
#define SEEKANDDESTROYDRONE_H

#include "Drone.h"

class SeekAndDestroyDrone : public Drone
{
public:
      SeekAndDestroyDrone(glm::vec2 pos, glm::vec2 vel);
      ~SeekAndDestroyDrone();
};

#endif
