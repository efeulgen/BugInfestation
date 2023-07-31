
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

      const char *majorExplosionSpriteSheet[4] = {"./assets/sprites/drone_minorExplosion_1.png", "./assets/sprites/drone_minorExplosion_2.png", "./assets/sprites/drone_minorExplosion_3.png", "./assets/sprites/drone_minorExplosion_4.png"}; // for testing purposes : change later, unique for every drone
      double majorExplosionAnimCounter = 0.0;
      bool donePlayingMajorExplosion = false;

public:
      SeekAndDestroyDrone(glm::vec2 pos, glm::vec2 dir, Player *player);
      ~SeekAndDestroyDrone();

      void UpdateDrone(double deltaTime) override;
      void RenderDrone(SDL_Renderer *renderer) override;

      void UpdatePositionsToFollow();
};

#endif
