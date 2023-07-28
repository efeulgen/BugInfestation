
#ifndef SEEKANDDESTROYDRONE_H
#define SEEKANDDESTROYDRONE_H

#include "Drone.h"
#include "../Player.h"

const double UPDATE_POSITIONS_TO_FOLLOW_RATE = 0.1;

class SeekAndDestroyDrone : public Drone
{
private:
      glm::vec2 positionToFollow;
      double updatepositionsToFollowCounter = 0.0;
      Player *refToPlayer;

public:
      SeekAndDestroyDrone(glm::vec2 pos, glm::vec2 dir, Player *player);
      ~SeekAndDestroyDrone();

      void UpdateDrone(double deltaTime) override;
      void RenderDrone(SDL_Renderer *renderer) override;

      void UpdatePositionsToFollow();
};

#endif
