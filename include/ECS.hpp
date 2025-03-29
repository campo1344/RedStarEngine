#pragma once

#include <vec.hpp>
#include <vector>
#include <memory>

#include <WSDL3.hpp>

class ECS;

class Component
{
public:
    Component() {}
    virtual ~Component() {}
    virtual void Update(float DeltaTime) = 0;
    inline void AddObjectController(ECS *objController)
    {
        if (objController != nullptr)
        {
            this->ThisObject = objController;
        }
    }

protected:
    ECS *ThisObject = nullptr;
};

class ECS
{
public:
    ECS() {}
    ~ECS()
    {
        for (auto &comp : components)
        {
            delete comp;
        }
        components.clear();
    }

    vec2 Position;
    float Angle = 0.0f;

    int width = 100;
    int height = 100;

    inline void AddSprite(Sprite *sprAdd)
    {
        if (sprAdd != nullptr)
        {
            this->sprUse = sprAdd;
        }
    }

    inline void Update(float DeltaTime)
    {
        for (auto &comp : components)
        {
            comp->Update(DeltaTime);
        }
        if (this->Angle > 360 || this->Angle < -360)
        {
            this->Angle = 0;
        }
    }

    inline void AddComponent(Component *comp)
    {
        if (comp != nullptr)
        {
            components.push_back(comp);
        }
    }

    Sprite *sprUse = nullptr;

private:
    std::vector<Component *> components;
};

class DrawSprite : public Component
{
public:
    void Update(float DeltaTime) override
    {
        if (this->ThisObject != nullptr)
        {
            ThisObject->sprUse->dest.x = ThisObject->Position.x - (ThisObject->width * x);
            ThisObject->sprUse->dest.y = ThisObject->Position.y - (ThisObject->height * y);
        }
    }
    // float 0 - 1
    inline void SetPositionDraw(float PosX, float PosY)
    {
        x = PosX;
        y = PosY;
    }

protected:
    float x = 0.0f;
    float y = 0.0f;
};

class RotationOn : public Component
{
public:
    void Update(float DeltaTime) override
    {
        if (this->ThisObject != nullptr)
        {
            float Rad = DegToRad(this->ThisObject->Angle);

            if (rotObject != nullptr)
            {
                this->ThisObject->Position.x = rotObject->Position.x + std::cos(Rad) * Radio;
                this->ThisObject->Position.y = rotObject->Position.y + std::sin(Rad) * Radio;
            }

            this->ThisObject->Angle -= 1 * DeltaTime;
        }
    }

    void AddRotatedOfObject(ECS *obj, float Distance = 0.0f)
    {
        if (obj != nullptr)
        {
            rotObject = obj;
            Radio = Distance;
        }
    }

protected:
    ECS *rotObject = nullptr;
    float Radio = 0.0f;
};

class SimpleControllerRPGNoCollision : public Component
{
public:
    void Update(float DeltaTime) override
    {
        if (this->ThisObject != nullptr)
        {
            for (int x = 0; x < 4; x++)
            {
                if (WSDL3::event.type == SDL_EVENT_KEY_UP && WSDL3::event.key.key == KeyUse[x])
                {
                    CheckKey[x] = false;
                }
                if (WSDL3::event.type == SDL_EVENT_KEY_DOWN && WSDL3::event.key.key == KeyUse[x])
                {
                    CheckKey[x] = true;
                }
            }

            if (CheckKey[0])
            {
                this->ThisObject->Position.y -= SpeedMovent * DeltaTime;
            }
            if (CheckKey[1])
            {
                this->ThisObject->Position.y += SpeedMovent * DeltaTime;
            }
            if (CheckKey[2])
            {
                this->ThisObject->Position.x -= SpeedMovent * DeltaTime;
            }
            if (CheckKey[3])
            {
                this->ThisObject->Position.x += SpeedMovent * DeltaTime;
            }
        }
    }
    inline void AddKeyMovent(Uint32 UP, Uint32 Down, Uint32 Left, Uint32 Rigth, float Speed)
    {
        SpeedMovent = Speed;
        KeyUse[0] = UP;
        KeyUse[1] = Down;
        KeyUse[2] = Left;
        KeyUse[3] = Rigth;
    }

protected:
    Uint32 KeyUse[4] = {SDLK_W, SDLK_S, SDLK_A, SDLK_D};
    float SpeedMovent = 1.0f;
    bool CheckKey[4] = {false, false, false, false};
};

class PosCamera : public Component
{
public:
    inline void Update(float DeltaTime) override
    {
        if (this->ThisObject != nullptr && this->ThisCamera != nullptr)
        {
            ThisCamera->x = ThisObject->Position.x - (ThisCamera->viewPort.w * X);
            ThisCamera->y = ThisObject->Position.y - (ThisCamera->viewPort.h * Y);
        }
    }

    inline void SetPosition(float PosX, float PosY, Camera *cam)
    {
        if (cam != nullptr)
        {
            ThisCamera = cam;
        }
        X = PosX;
        Y = PosY;
    };

protected:
    float X = 0.0f;
    float Y = 0.0f;
    Camera *ThisCamera = nullptr;
};