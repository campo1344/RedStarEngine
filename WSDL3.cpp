#include <WSDL3.hpp>

SDL_Window *WSDL3::window = nullptr;
SDL_Renderer *WSDL3::renderer = nullptr;
SDL_Event WSDL3::event;

WSDL3::WSDL3() {}
WSDL3::~WSDL3()
{
    ClearAllResource();
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void WSDL3::Init(const char *Title, int w, int h)
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        this->window = SDL_CreateWindow(Title, w, h, 0);
        if (this->window != nullptr)
        {
            this->renderer = SDL_CreateRenderer(this->window, NULL);
            if (this->renderer != nullptr)
            {
                IsClose = false;
            }
            else
            {
                SDL_DestroyWindow(this->window);
                SDL_Quit();
            }
        }
        else
        {
            SDL_Quit();
        }
    }
}

void WSDL3::Event()
{
    SDL_PollEvent(&event);

    if (event.type == SDL_EVENT_QUIT)
    {
        IsClose = true;
    }
}

bool WSDL3::CreateTexture(const char *FilePath, std::string name)
{
    Texture *text = new Texture();
    if (!text->CreateTextureFromFile(name, FilePath, this->renderer))
    {
        return false;
    }
    textures.push_back(text);
    return true;
}

Sprite *WSDL3::CreateSprite(std::string name)
{
    Sprite *spr = new Sprite;
    spr->id = idSpriteMax;
    idSpriteMax++;

    for (auto &text : textures)
    {
        if (text->GetName() == name)
        {
            spr->texture = text->GetTexture();
            break;
        }
    }

    if (spr->texture != nullptr)
    {
        spr->dest.x = 0;
        spr->dest.y = 0;
        spr->dest.h = 100;
        spr->dest.w = 100;

        spr->src.x = 0;
        spr->src.y = 0;
        spr->src.h = 100;
        spr->src.w = 100;

        sprites.push_back(spr);
        return spr;
    }

    delete spr;
    return nullptr;
}

bool WSDL3::DestroySprite(Sprite *DSprite)
{
    if (DSprite == nullptr)
    {
        return false;
    }
    for (int x = 0; x < sprites.size(); x++)
    {
        if (DSprite->id == sprites[x]->id)
        {
            delete sprites[x];
            sprites.erase(sprites.begin() + x);
            return true;
        }
    }
    return false;
}

void WSDL3::ClearAllSprite()
{
    for (auto &spr : sprites)
    {
        delete spr;
    }
    sprites.clear();
    idSpriteMax = 0;
}

void WSDL3::ClearAllTexture()
{
    for (auto &text : textures)
    {
        delete text;
    }
    textures.clear();
}

void WSDL3::DrawALL()
{
    SDL_RenderClear(this->renderer);

    if (cameras.size() == 0)
    {
        for (auto &spr : sprites)
        {
            SDL_RenderTextureRotated(this->renderer, spr->texture, &spr->src, &spr->dest, spr->angle, NULL, SDL_FLIP_NONE);
        }
    }
    else
    {
        for (auto &cam : cameras)
        {
            SDL_SetRenderViewport(this->renderer, &cam->viewPort);

            for (auto &spr : sprites)
            {
                TempDest.x = spr->dest.x - cam->x;
                TempDest.y = spr->dest.y - cam->y;
                TempDest.h = spr->dest.h;
                TempDest.w = spr->dest.w;

                SDL_RenderTextureRotated(this->renderer, spr->texture, &spr->src, &TempDest, spr->angle, NULL, SDL_FLIP_NONE);
            }
        }
    }

    SDL_RenderPresent(this->renderer);
}

Camera *WSDL3::CreateCamera(int w, int h, int x, int y)
{
    Camera *cam = new Camera;

    cam->viewPort.x = x;
    cam->viewPort.y = y;
    cam->viewPort.h = h;
    cam->viewPort.w = w;
    cam->id = idCameraMax;

    idCameraMax++;

    this->cameras.push_back(cam);

    return cam;
}

bool WSDL3::DestroyCamera(Camera *dcam)
{

    if (dcam == nullptr)
    {
        return false;
    }

    for (int x = 0; x < cameras.size(); x++)
    {
        if (cameras[x]->id == dcam->id)
        {
            delete cameras[x];
            dcam = nullptr;
            cameras.erase(cameras.begin() + x);
            return true;
        }
    }
    return false;
}