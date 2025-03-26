#include <iostream>
#include <ReadRSEngine.hpp>
#include <WSDL3.hpp>
#include <vec.hpp>

WSDL3 *win = nullptr;

typedef enum TypeProccesProgram
{
    Init = 0,
    Load = 1,
    Donwload = 2,
    Run = 3,
    Pause = 4,
} TypeProccesProgram;

inline void LoadConfigUserInit()
{
    nlohmann::json config;
    ReadDataOfFileJson("userConfig.json", &config);

    try
    {
        win->Init("Demo 1 - Simple Game", config["screenW"], config["screenH"]);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

inline void LoadMap(const char *Name)
{
    nlohmann::json map;
    ReadDataOfFileJson(Name, &map);

    try
    {
        /* code */
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        win->ExitWindow();
    }
}

int main(int argc, char *argv[])
{
    win = new WSDL3();

    LoadConfigUserInit();

    if (win == nullptr)
    {
        return 1;
    }

    float LockFPS = 1000.0f / 60;

    Uint64 TimePrevius = SDL_GetTicks();
    Uint64 TimePresent;
    float FrameRate;
    float DeltaTime;

    win->CreateTexture("SprPlanet.png", "planetas");

    Sprite *SPR_Planet1 = win->CreateSprite("planetas");
    SPR_Planet1->src.w = 200;
    SPR_Planet1->src.h = 200;
    SPR_Planet1->dest.w = 200;
    SPR_Planet1->dest.h = 200;

    Sprite *SPR_Planet2 = win->CreateSprite("planetas");
    SPR_Planet2->src.w = 200;
    SPR_Planet2->src.h = 200;
    SPR_Planet2->src.x = 200;
    SPR_Planet2->dest.x = 400;
    SPR_Planet2->dest.w = 200;
    SPR_Planet2->dest.h = 200;
	
	DrawSprite* DrawPlanet1 = new DrawSprite();
	ObjectTest* OBJPlanet1 = new ObjectTest();
    OBJPlanet1->width = 200;
    OBJPlanet1->height = 200;
    OBJPlanet1->Position.x = 400;
    OBJPlanet1->Position.y = 300;
	DrawPlanet1->SetPositionDraw(0.5, 0.5);
    DrawPlanet1->AddObjectController(OBJPlanet1);
	OBJPlanet1->AddSprite(SPR_Planet1);
    OBJPlanet1->AddComponent(DrawPlanet1);

    DrawSprite* DrawPlanet2 = new DrawSprite();
	ObjectTest* OBJPlanet2 = new ObjectTest();
    OBJPlanet2->width = 200;
    OBJPlanet2->height = 200;
	DrawPlanet2->SetPositionDraw(0.5, 0.5);
    DrawPlanet2->AddObjectController(OBJPlanet2);
	OBJPlanet2->AddSprite(SPR_Planet2);
    OBJPlanet2->AddComponent(DrawPlanet2);

    RotationOn* RotPlanet2 = new RotationOn();
    RotPlanet2->AddObjectController(OBJPlanet2);
    RotPlanet2->AddRotatedOfObject(OBJPlanet1, 300);
    OBJPlanet2->AddComponent(RotPlanet2);

    Camera* camUser = win->CreateCamera(800, 600, 0, 0);
    ObjectTest *Player = new ObjectTest();
    
    SimpleControllerRPGNoCollision *ControlPlayer = new SimpleControllerRPGNoCollision();
    ControlPlayer->AddObjectController(Player);
    ControlPlayer->AddKeyMovent(SDLK_W, SDLK_S, SDLK_A, SDLK_D, 50);
    Player->AddComponent(ControlPlayer);

    PosCamera *PostCameraPlayer = new PosCamera();
    PostCameraPlayer->AddObjectController(Player);
    PostCameraPlayer->SetPosition(0.5f, 0.5f, camUser);
    Player->AddComponent(PostCameraPlayer);

    while (!win->WindowClose())
    {
        TimePresent = SDL_GetTicks();

        DeltaTime = (TimePresent - TimePrevius) / 100.0f;

        OBJPlanet1->Update(DeltaTime);
        OBJPlanet2->Update(DeltaTime);
        Player->Update(DeltaTime);

        win->DrawALL();

        win->Event();

        FrameRate = (SDL_GetTicks() - TimePresent) / LockFPS;

        if (FrameRate < LockFPS)
        {
            SDL_Delay(LockFPS - FrameRate);
        }

        TimePrevius = TimePresent;
    }

    delete Player;
    delete OBJPlanet1;
    delete OBJPlanet2;

    delete win;

    return 0;
}