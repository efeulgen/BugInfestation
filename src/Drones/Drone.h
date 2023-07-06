
#ifndef DRONE_H
#define DRONE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

enum DroneType
{
      SeekAndDestroyDrone,
      TrippleLaserShootingDrone,
      FighterDrone
};

class Drone
{
private:
      glm::vec2 position;
      glm::vec2 velocity;
      const char *imgPath;

public:
      Drone();
      ~Drone();
      virtual void UpdateDrone(double deltaTime);
      virtual void RenderDrone(SDL_Renderer *renderer);
      void DestroyDrone();
};

#endif
