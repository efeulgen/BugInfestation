
#include "SeekAndDestroyDrone.h"

SeekAndDestroyDrone::SeekAndDestroyDrone(glm::vec2 pos, glm::vec2 dir, Player *player) : Drone(pos, dir)
{
      std::cout << "SeekAndDestroyDrone Constructor" << std::endl;

      imgPath = "./assets/sprites/TrippleLaserDrone.png"; // for debugging change later
      droneRectSize = 64;
      droneType = DroneType::DT_SeekAndDestroyDrone;
      refToPlayer = player;
      droneSpeed = 150.0;
      UpdatePositionsToFollow();
}

SeekAndDestroyDrone::~SeekAndDestroyDrone()
{
      std::cout << "SeekAndDestroyDrone Destructor" << std::endl;
}

void SeekAndDestroyDrone::UpdateDrone(double deltaTime)
{
      updatepositionsToFollowCounter += deltaTime;
      if (updatepositionsToFollowCounter >= UPDATE_POSITIONS_TO_FOLLOW_RATE)
      {
            UpdatePositionsToFollow();
      }

      if (isDead)
      {
            isDestructible = true;
      }

      Drone::UpdateDrone(deltaTime);
}

void SeekAndDestroyDrone::RenderDrone(SDL_Renderer *renderer)
{
      Drone::RenderDrone(renderer);
}

void SeekAndDestroyDrone::UpdatePositionsToFollow()
{
      positionToFollow = refToPlayer->GetPlayerPos();
      direction = glm::normalize(positionToFollow - position);
}
