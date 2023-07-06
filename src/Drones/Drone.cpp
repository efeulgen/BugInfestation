
#include <Drone.h>

Drone::Drone()
{
      std::cout << "Drone Constructor" << std::endl;
}

Drone::~Drone()
{
      std::cout << "Drone Destructor" << std::endl;
}

void Drone::UpdateDrone(double deltaTime)
{
      position.x += velocity.x * deltaTime;
      position.y += velocity.y * deltaTime;
}

void Drone::RenderDrone(SDL_Renderer *renderer)
{
      SDL_Surface *surf = IMG_Load(imgPath);
      SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
      SDL_FreeSurface(surf);
      SDL_Rect rect = {static_cast<int>(position.x), static_cast<int>(position.y), 64, 64};
      SDL_RenderCopy(renderer, tex, NULL, &rect);
      SDL_DestroyTexture(tex);
}

void Drone::DestroyDrone()
{
      delete this;
}
