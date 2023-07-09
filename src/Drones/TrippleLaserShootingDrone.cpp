
#include "TrippleLaserShootingDrone.h"

TrippleLaserShootingDrone::TrippleLaserShootingDrone(glm::vec2 pos, glm::vec2 vel) : Drone(pos, vel)
{
      std::cout << "TrippleLaserShootingDrone Constructor" << std::endl;
}

TrippleLaserShootingDrone::~TrippleLaserShootingDrone()
{
      std::cout << "TrippleLaserShootingDrone Destructor" << std::endl;
}
