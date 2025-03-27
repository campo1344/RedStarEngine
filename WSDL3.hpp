#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

typedef struct Texture
{
    SDL_Texture *texture = nullptr;
    std::string name = "";
} Texture;

typedef struct Sprite
{
    SDL_Texture *texture = nullptr;
    SDL_FRect dest, src;
    float angle = 0.0f;
    int id = -1;
} Sprite;

typedef struct Camera
{
    SDL_Rect viewPort;
    int x = 0;
    int y = 0;
    float zoom = 1.0f;
    int id = -1;
} Camera;

class WSDL3
{
private:
    bool IsClose = true;
    std::vector<Sprite *> sprites;
    std::vector<Texture *> textures;
    std::vector<Camera *> cameras;
    int idSpriteMax = 0;
    int idCameraMax = 0;
    SDL_FRect TempDest;

public:
    static SDL_Window *window;
    static SDL_Renderer *renderer;
    static SDL_Event event;

    WSDL3();
    ~WSDL3();

    void Event();
    inline void Draw() { SDL_RenderPresent(this->renderer); }
    void DrawALL();
    inline void ClearDraw() { SDL_RenderClear(this->renderer); }
    void Init(const char *Title, int w, int h);

    inline void CloseWindow() { IsClose = true; }
    inline bool WindowClose() { return IsClose; }

    Sprite *CreateSprite(std::string name);
    bool CreateTexture(const char *FilePath, std::string name);
    Camera *CreateCamera(int w, int h, int x, int y);

    bool DestroySprite(Sprite *DSprite);
    bool DestroyCamera(Camera *dcam);
    void ClearAllTexture();
    void ClearAllSprite();

    inline void ClearAllResource()
    {
        ClearAllSprite();
        ClearAllTexture();
        for (auto &cam : cameras)
        {
            delete cam;
        }
        cameras.clear();
    }

    inline void ExitWindow() { IsClose = true; }
};

typedef struct Alarma
{
    int id = -1;
    Uint64 StartTime;
    int Time;
    bool isCall = false;
} Alarma;

static std::vector<Alarma *> alarmas;
static int idAlarmaMax = 0;

// 10 = 1segundo
inline Alarma *CreateAlarma(int Time)
{
    Alarma *newAlarma = new Alarma;
    newAlarma->id = idAlarmaMax;
    idAlarmaMax++;
    newAlarma->Time = Time;
    newAlarma->StartTime = SDL_GetTicks();

    alarmas.push_back(newAlarma);

    return newAlarma;
}

inline bool DestroyAlarma(Alarma *DAlarma)
{

    for (int x = 0; x < alarmas.size(); x++)
    {
        if (DAlarma->id == alarmas[x]->id)
        {
            delete alarmas[x];
            DAlarma = nullptr;
            alarmas.erase(alarmas.begin() + x);
            return true;
        }
    }

    return false;
}

inline void CheckUpdateAlarma(Uint64 *TimePresent)
{
    for (auto &ala : alarmas)
    {
        if ((*TimePresent - ala->StartTime) / 100 <= ala->Time)
        {
            ala->isCall = true;
        }
    }
}