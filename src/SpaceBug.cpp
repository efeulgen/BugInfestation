
#include "SpaceBug.h"

SpaceBug::SpaceBug()
{
    Logger::Log("SpaceBug Constructor");
}

SpaceBug::SpaceBug(glm::vec2 initPos, glm::vec2 initDirection) : spaceBugPos{initPos}, spaceBugDirection{initDirection}, spaceBugRect{0, 0, 0, 0}
{
    Logger::Log("SpaceBug Constructor");

    health = 1;
    type = BugType::Regular;
}

SpaceBug::~SpaceBug()
{
    Logger::Log("SpaceBug Destructor");
}

void SpaceBug::UpdateSpaceBug(double deltaTime, Player *player)
{
    if (isDead)
    {
        explodeAnimIndex += deltaTime * ANIM_SPEED;
        return;
    }
    spaceBugPos.x += spaceBugDirection.x * deltaTime;
    spaceBugPos.y += spaceBugDirection.y * deltaTime;
    if (spaceBugPos.x <= 0 || spaceBugPos.x >= (1280 - 64))
    {
        spaceBugDirection.x *= -1;
        isFlipped = !isFlipped;
    }
    if (spaceBugPos.y <= 0 || spaceBugPos.y >= (720 - 64))
    {
        spaceBugDirection.y *= -1;
    }

    // update anim index
    spriteSheetIndex += deltaTime * ANIM_SPEED;
}

void SpaceBug::RenderSpaceBug(SDL_Renderer *gameRenderer)
{
    if (isDead)
    {
        if (!donePlayingExplodeAnim)
        {
            SDL_Surface *surf = IMG_Load(bugExplodeSpriteSheet[static_cast<int>(explodeAnimIndex)]);
            SDL_Texture *tex = SDL_CreateTextureFromSurface(gameRenderer, surf);
            SDL_FreeSurface(surf);
            spaceBugRect = {static_cast<int>(spaceBugPos.x), static_cast<int>(spaceBugPos.y), 64, 64};
            SDL_RenderCopy(gameRenderer, tex, NULL, &spaceBugRect);
            SDL_DestroyTexture(tex);

            if (static_cast<int>(explodeAnimIndex) >= 6)
            {
                donePlayingExplodeAnim = true;
                isDestructible = true;
            }
        }
        return;
    }
    if (static_cast<int>(spriteSheetIndex) > 3)
    {
        spriteSheetIndex = 0.0;
    }
    spaceBugSurface = IMG_Load(bugSpriteSheet[static_cast<int>(spriteSheetIndex)]);
    SDL_Texture *spaceBugTexture = SDL_CreateTextureFromSurface(gameRenderer, spaceBugSurface);
    SDL_FreeSurface(spaceBugSurface);
    spaceBugRect = {static_cast<int>(spaceBugPos.x), static_cast<int>(spaceBugPos.y), 64, 64};

    if (isFlipped)
    {
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(gameRenderer, spaceBugTexture, NULL, &spaceBugRect, 0.0, NULL, flip);
    }
    else
    {
        SDL_RenderCopy(gameRenderer, spaceBugTexture, NULL, &spaceBugRect);
    }
    SDL_DestroyTexture(spaceBugTexture);
}

void SpaceBug::GetDamage(int amount)
{
    health -= amount;
    if (health <= 0)
    {
        isDead = true;
        canDamagePlayer = false;
    }
}

bool SpaceBug::CheckCollision(SDL_Rect other) const
{
    if (SDL_HasIntersection(&spaceBugRect, &other) && canDamagePlayer)
    {
        return true;
    }
    return false;
}

void SpaceBug::Destroy()
{
    delete this;
}

void SpaceBug::EraseElementFromProjarray(Projectile *proj)
{
    projArray.erase(std::remove(projArray.begin(), projArray.end(), proj), projArray.end());
}
