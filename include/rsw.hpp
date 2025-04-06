#pragma once

#ifndef RSW_EXPORTS
#define RSW_API __declspec(dllimport)
#else
#define RSW_API __declspec(dllexport)
#endif

#define CALL _cdecl

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <memory>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

#ifdef __cplusplus
extern "C"
{
#endif

    class RSW_API Texture
    {
    private:
        SDL_Texture *text = nullptr;

    public:
        Texture(SDL_Texture *AddTexture = nullptr);
        ~Texture();
        static SDL_Texture *LoadTexture(const char *FilePath, SDL_Renderer *render);
    };

    typedef struct Sprite
    {
        int depth = -1;
        SDL_Texture *text = nullptr;
        SDL_FRect dest, src;
        float angle = 0.0f;
        int id = 0;
    } Sprite;

    typedef struct Camera
    {
        int id = -1;
        float x = 0.0f;
        float y = 0.0f;
        float angle = 0.0f;
        SDL_Rect ViewPort;
    } Camera;

    class RSW_API WSDL3
    {
    private:
        std::vector<std::shared_ptr<Sprite>> Sprites;
        std::map<std::string, std::unique_ptr<Texture>> Textures;
        std::vector<std::shared_ptr<Camera>> cameras;
        int IndexSprite = 0;
        int IndexCamera = 0;
        bool windowC = true;

    public:
        static SDL_Window *window;
        static SDL_Renderer *renderer;
        static SDL_Event event;
        WSDL3();
        ~WSDL3();

        void Init(const char *Title, int w, int h);
        void Event();
        void Draw();
        void OrderDraw();

        void CreateTexture(const char *FilePath, std::string nameTexture);
        std::shared_ptr<Sprite> CreateSprite(std::string nameTexture, int Depth);

        //return true = window Close or false = window Open
        inline bool WindowClose() { return windowC; }
    };

#ifdef __cplusplus
}
#endif
