
#include "Game.h"

Game::Game() : spaceBugMinSpeed{SPACE_BUG_INIT_MIN_SPEED}, spaceBugMaxSpeed{SPACE_BUG_INIT_MAX_SPEED}
{
    Logger::Log("Game Constructor");
}

Game::~Game()
{
    Logger::Log("Game Destructor");
}

void Game::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Logger::Err("SDL_Init fails.");
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        Logger::Err("SDL_Mixer init fails.");
    }

    TTF_Init();

    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, backgroundWidth, backgroundHeight, SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        Logger::Err("SDL_Window creation fails.");
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        Logger::Err("SDL_Renderer creation fails.");
        return;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    isRunning = true;
    SDL_ShowCursor(0);
}

void Game::Display()
{
    SetupGameAssets();
    while (isRunning)
    {
        ProcessInput();
        UpdateGameAssets();
        Render();
    }
}

// *********************************************************************************************************************************************************************
// *************** SETUP ***********************************************************************************************************************************************
// *********************************************************************************************************************************************************************

void Game::SetupGameAssets()
{
    // setup audio
    audio = Mix_LoadWAV("./audio/game_music.wav");
    bugSplashSound = Mix_LoadWAV("./audio/smash.wav");
    bugScreamSound = Mix_LoadWAV("./audio/scream.wav");
    if (audio == NULL || bugSplashSound == NULL || bugScreamSound == NULL)
    {
        Logger::Err("Failed to load audio.");
    }
    Mix_PlayChannel(-1, audio, -1);

    // managers
    uiManager = new UIManager();
}

void Game::ProcessInput()
{
    SDL_Event gameEvent;
    while (SDL_PollEvent(&gameEvent))
    {
        if (gameEvent.type == SDL_QUIT)
        {
            isRunning = false;
        }
        if (gameEvent.type == SDL_KEYDOWN)
        {
            if (gameEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
            if (gameEvent.key.keysym.sym == SDLK_RETURN && mainPlayer && mainPlayer->GetCanFire())
            {
                mainPlayer->Fire();
            }
            if (gameEvent.key.keysym.sym == SDLK_y)
            {
                if (isGameOver)
                {
                    ResetGame();
                }
                else if (isWaveComplete)
                {
                    BringNextWave();
                }
            }
            if ((isGameOver || isWaveComplete) && gameEvent.key.keysym.sym == SDLK_n)
            {
                isRunning = false;
            }
            if (!isGameStarted && gameEvent.key.keysym.sym == SDLK_SPACE)
            {
                StartGame();
            }
        }
    }
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    if (keyboardState[SDL_SCANCODE_D] && mainPlayer)
    {
        mainPlayer->MoveRight(deltaTime);
    }
    if (keyboardState[SDL_SCANCODE_A] && mainPlayer)
    {
        mainPlayer->MoveLeft(deltaTime);
    }
    if (keyboardState[SDL_SCANCODE_SPACE] && isGameStarted && mainPlayer)
    {
        mainPlayer->UseJetPack(deltaTime);
    }
    if (!keyboardState[SDL_SCANCODE_SPACE] && isGameStarted && mainPlayer)
    {
        mainPlayer->SetIsUsingJetPack(false);
    }
}

// *********************************************************************************************************************************************************************
// *************** UPDATE **********************************************************************************************************************************************
// *********************************************************************************************************************************************************************

void Game::UpdateGameAssets()
{
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
    {
        SDL_Delay(timeToWait);
    }
    deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
    millisecsPreviousFrame = SDL_GetTicks();

    // *************** update background ******************************
    bg1_xPos -= deltaTime * bgSpeed;
    bg2_xPos -= deltaTime * bgSpeed;
    if (bg1_xPos <= -1280.0)
    {
        bg1_xPos = 1280.0;
    }
    if (bg2_xPos <= -1280.0)
    {
        bg2_xPos = 1280.0;
    }

    // ************************************************************************************************************************************************
    // *************** garbage collect bugs/drones ****************************************************************************************************

    for (auto bug : bugs)
    {
        if (bug->GetIsDestructible())
        {
            bugs.erase(std::remove(bugs.begin(), bugs.end(), bug), bugs.end());
            bug->Destroy();
            bug = nullptr;
            break;
        }
    }

    for (auto drone : drones)
    {
        if (drone->GetIsDestructible())
        {
            drones.erase(std::remove(drones.begin(), drones.end(), drone), drones.end());
            drone->DestroyDrone();
            drone = nullptr;
            break;
        }
    }

    // *************************************************************************************************************************************
    // *************** check collisions ****************************************************************************************************

    // *************** check if bugs/drones collide with player projectile ******************************
    if (mainPlayer && (!bugs.empty() || !mainPlayer->GetProjectileArray().empty()) && !isGameOver && !isWaveComplete && isGameStarted)
    {
        for (auto bug : bugs)
        {
            for (auto projectile : mainPlayer->GetProjectileArray())
            {
                if (bug->CheckCollision(projectile->GetProjectileRect()))
                {
                    Mix_PlayChannel(-1, bugScreamSound, 0);
                    Mix_PlayChannel(-1, bugSplashSound, 0);

                    bug->GetDamage();
                    mainPlayer->EraseElementFromProjarray(projectile);
                    projectile->Destroy();
                    projectile = nullptr;
                    IncrementScore();
                    break;
                }
            }
        }

        for (auto drone : drones)
        {
            for (auto projectile : mainPlayer->GetProjectileArray())
            {
                if (drone->CheckCollision(projectile->GetProjectileRect()))
                {
                    drone->GetDamage();
                    mainPlayer->EraseElementFromProjarray(projectile);
                    projectile->Destroy();
                    projectile = nullptr;
                    IncrementScore();
                    break;
                }
            }
        }
    }

    // *************** check if bugs collide with player ******************************
    if (!bugs.empty() && mainPlayer && !isGameOver && !isWaveComplete && isGameStarted)
    {
        for (auto bug : bugs)
        {
            if (bug->CheckCollision(mainPlayer->GetPlayerRect()) && bug->GetCanDamagePlayer())
            {
                if (bug->GetBugType() == BugType::Bladed)
                {
                    mainPlayer->GetDamage(20.0);
                    bug->SetCanDamagePlayer(false);
                }
                else
                {
                    bugs.erase(std::remove(bugs.begin(), bugs.end(), bug), bugs.end());
                    bug->Destroy();
                    bug = nullptr;

                    mainPlayer->GetDamage(20.0);
                }
                break;
            }

            if (bug->GetBugType() == BugType::Heavy)
            {
                for (auto proj : bug->GetBugProjArraj())
                {
                    if (mainPlayer->CheckCollision(proj->GetProjectileRect()))
                    {
                        bug->EraseElementFromProjarray(proj);
                        proj->Destroy();
                        proj = nullptr;
                        mainPlayer->GetDamage(5.0);
                        break;
                    }
                }
            }
        }
    }

    // *************** check if pickup collide with player ******************************
    if (pickup && mainPlayer && !isGameOver && isGameStarted)
    {
        if (pickup->CheckCollisionWithPlayer(mainPlayer->GetPlayerRect(), mainPlayer))
        {
            uiManager->ActivatePickupText(pickup->GetPickupType());
            pickup->DestroyPickup();
            pickup = nullptr;
        }
    }

    // *************************************************************************************************************************************
    // *************** end collisions ******************************************************************************************************

    // *************** update main player ******************************
    if (mainPlayer)
    {
        mainPlayer->Update(deltaTime);
        if (mainPlayer->GetIsDead())
        {
            isGameOver = true;
            isWaveComplete = false;
            delete mainPlayer;
            mainPlayer = nullptr;
        }
    }

    // *************** update space bugs ******************************
    if (bugs.size() <= 0 && !isWaveComplete && isGameStarted && !isGameOver)
    {
        isWaveComplete = true;
    }
    else
    {
        for (auto bug : bugs)
        {
            bug->UpdateSpaceBug(deltaTime, mainPlayer);
        }
    }

    // *************** update drones ******************************
    for (auto drone : drones)
    {
        drone->UpdateDrone(deltaTime);
    }

    // *************** update pickup ******************************
    if (pickup)
    {
        pickup->Update(deltaTime);

        glm::vec2 pos = pickup->GetPickupPos();
        if (pos.x > 1400 || pos.x < -100 || pos.y > 720 || pos.y < -200)
        {
            pickup->DestroyPickup();
            pickup = nullptr;
        }
    }
    else if (!isWaveComplete && isGameStarted && !isGameOver && waveType == WaveType::RegularWave)
    {
        GeneratePickup();
    }

    // *************** generate drones ******************************
    generateDroneCounter -= deltaTime;
    if (!isWaveComplete && isGameStarted && !isGameOver && generateDroneCounter <= 0.0)
    {
        GenerateDrones();
        generateDroneCounter = 7.5;
    }
}
// *********************************************************************************************************************************************************************
// *************** RENDER **********************************************************************************************************************************************
// *********************************************************************************************************************************************************************

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // *************** render background ******************************
    SDL_Surface *backgroundSurface = IMG_Load("./assets/deep_space_bg_1280x720.png");
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    SDL_Rect bgRect_1 = {static_cast<int>(bg1_xPos), 0, 1280, 720};
    SDL_Rect bgRect_2 = {static_cast<int>(bg2_xPos), 0, 1280, 720};
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect_1);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect_2);
    SDL_DestroyTexture(backgroundTexture);

    // *************** render player ******************************
    if (mainPlayer)
    {
        mainPlayer->RenderPlayer(renderer);
    }

    // *************** render spacebugs ******************************
    for (auto bug : bugs)
    {
        bug->RenderSpaceBug(renderer);
    }

    // *************** render drones ******************************
    for (auto drone : drones)
    {
        drone->RenderDrone(renderer);
    }

    // *************** render pickup ******************************
    if (pickup)
    {
        pickup->Render(renderer);
    }

    // *************** render UI ******************************
    uiManager->RenderUI(renderer, mainPlayer, score, wave, isGameStarted, isWaveComplete, isGameOver, deltaTime);

    SDL_RenderPresent(renderer);
}

// *********************************************************************************************************************************************************************
// *********************************************************************************************************************************************************************
// *********************************************************************************************************************************************************************

void Game::Destroy()
{
    if (mainPlayer)
    {
        delete mainPlayer;
        mainPlayer = nullptr;
    }
    delete uiManager;
    Mix_FreeChunk(audio);
    Mix_FreeChunk(bugScreamSound);
    Mix_FreeChunk(bugSplashSound);
    audio = nullptr;
    bugScreamSound = nullptr;
    bugSplashSound = nullptr;
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::StartGame()
{
    mainPlayer = new Player();
    spaceBugAmount = SPACE_BUG_INIT_AMOUNT;
    GenerateSpaceBugs(spaceBugAmount, spaceBugMinSpeed, spaceBugMaxSpeed);
    isGameStarted = true;
}

void Game::GenerateSpaceBugs(int amount, int minSpeed, int maxSpeed)
{
    if (wave > 0 && wave % 3 == 0)
    {
        bugs.push_back(new BladedSpaceBug(glm::vec2(1300.0, 360), glm::vec2(-1, 0)));
        waveType = WaveType::MiniBossWave;
    }
    else
    {
        for (int i = 0; i < amount; i++)
        {
            srand(spawnSeed);
            double randomYPos = 20.0 + static_cast<double>(rand() % 500);
            double randomXDirection = minSpeed + static_cast<double>(rand() % maxSpeed);
            double randomYDirection = minSpeed + static_cast<double>(rand() % maxSpeed);
            if (i == (amount - 1))
            {
                bugs.push_back(new HeavySpaceBug(glm::vec2(1000.0, randomYPos), glm::vec2(randomXDirection, randomYDirection)));
            }
            else
            {
                bugs.push_back(new SpaceBug(glm::vec2(1000.0, randomYPos), glm::vec2(randomXDirection, randomYDirection)));
            }
            spawnSeed++;
        }
        waveType = WaveType::RegularWave;
    }
}

void Game::GeneratePickup()
{
    srand(spawnSeed);
    double randomXPos = 1380; // + static_cast<double>(rand() % 1580);
    double randomYPos = -100 + static_cast<double>(rand() % 820);
    spawnSeed++;

    glm::vec2 initPos = glm::vec2(randomXPos, randomYPos);
    glm::vec2 direction = glm::normalize(glm::vec2(640, 360) - initPos);
    pickup = new Pickup(initPos, direction, spawnSeed);
}

void Game::GenerateDrones()
{
    srand(spawnSeed);
    double randomXPos = 1380; // + static_cast<double>(rand() % 1580);
    double randomYPos = -100 + static_cast<double>(rand() % 820);
    spawnSeed++;

    glm::vec2 initPos = glm::vec2(randomXPos, randomYPos);
    glm::vec2 direction = glm::vec2(-200.0, 0.0);
    drones.push_back(new FighterDrone(initPos, direction));
}

void Game::ResetGame()
{
    if (bugs.size() > 0)
    {
        for (auto bug : bugs)
        {
            bug->Destroy();
            bug = nullptr;
        }
        bugs.clear();
    }

    if (pickup)
    {
        delete pickup;
        pickup = nullptr;
    }

    spaceBugAmount = SPACE_BUG_INIT_AMOUNT;
    spaceBugMinSpeed = SPACE_BUG_INIT_MIN_SPEED;
    spaceBugMaxSpeed = SPACE_BUG_INIT_MAX_SPEED;
    GenerateSpaceBugs(spaceBugAmount, spaceBugMinSpeed, spaceBugMaxSpeed);
    score = 0;
    wave = 0;
    mainPlayer = new Player();
    isGameOver = false;
    isWaveComplete = false;
}

void Game::BringNextWave()
{
    if (mainPlayer->GetProjectileArray().size() > 0)
    {
        mainPlayer->ClearProjArray();
    }

    wave++;

    if (wave != 0 && wave % 3 == 0)
    {
        spaceBugAmount++;
        spaceBugMinSpeed += 5;
        spaceBugMaxSpeed += 5;
    }

    GenerateSpaceBugs(spaceBugAmount, spaceBugMinSpeed, spaceBugMaxSpeed);
    isWaveComplete = false;
}
