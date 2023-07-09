
#include "SeekAndDestroyDrone.h"

SeekAndDestroyDrone::SeekAndDestroyDrone(glm::vec2 pos, glm::vec2 vel) : Drone(pos, vel)
{
      std::cout << "SeekAndDestroyDrone Constructor" << std::endl;
}

SeekAndDestroyDrone::~SeekAndDestroyDrone()
{
      std::cout << "SeekAndDestroyDrone Destructor" << std::endl;
}
