#pragma once

#include <cmath>

#define PI 3.14159265359

class vec2
{
public:
    float x;
    float y;

    inline vec2(float PosX = 0.0f, float PosY = 0.0f) : x(PosX), y(PosY) {}
    ~vec2() {}

    inline vec2 operator+(vec2 other)
    {
        return vec2(this->x + other.x, this->y + other.y);
    }
    inline vec2 operator-(vec2 other)
    {
        return vec2(this->x - other.x, this->y - other.y);
    }

    inline vec2 operator*(vec2 other)
    {
        return vec2(this->x * other.x, this->y * other.y);
    }
};

inline float DegToRad(float angle)
{
    return angle * (PI / 180);
}

inline float RadToDeg(float Rad)
{
    return Rad * (180 / PI);
}

inline float GetDistanceTwoObject(vec2 Object1, vec2 Object2)
{
    float x = Object2.x - Object1.x;
    float y = Object2.y - Object1.y;

    return std::sqrt((x * x) + (y * y));
}

#include <WSDL3.hpp>

class ObjectTest;

class Component
{
public:
    Component() {}
    virtual ~Component() {}
    virtual void Update(float DeltaTime) = 0;
    inline void AddObjectController(ObjectTest *objController)
    {
        if (objController != nullptr)
        {
            this->other = objController;
        }
    }

protected:
    ObjectTest *other = nullptr;
};

class ObjectTest
{
public:
    ObjectTest() {}
    ~ObjectTest()
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
        if (this->other != nullptr)
        {
            other->sprUse->dest.x = other->Position.x - (other->width * x);
            other->sprUse->dest.y = other->Position.y - (other->height * y);
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
        if (this->other != nullptr)
        {
            float Rad = DegToRad(this->other->Angle);

            if (rotObject != nullptr)
            {
                this->other->Position.x = rotObject->Position.x + std::cos(Rad) * Radio;
                this->other->Position.y = rotObject->Position.y + std::sin(Rad) * Radio;
            }

            this->other->Angle -= 1 * DeltaTime;
        }
    }

    void AddRotatedOfObject(ObjectTest *obj, float Distance = 0.0f)
    {
        if (obj != nullptr)
        {
            rotObject = obj;
            Radio = Distance;
        }
    }

protected:
    ObjectTest *rotObject = nullptr;
    float Radio = 0.0f;
};

class SimpleControllerRPGNoCollision : public Component
{
public:
    void Update(float DeltaTime) override
    {
        if (this->other != nullptr)
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
                this->other->Position.y -= SpeedMovent * DeltaTime;
            }
            if (CheckKey[1])
            {
                this->other->Position.y += SpeedMovent * DeltaTime;
            }
            if (CheckKey[2])
            {
                this->other->Position.x -= SpeedMovent * DeltaTime;
            }
            if (CheckKey[3])
            {
                this->other->Position.x += SpeedMovent * DeltaTime;
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
        if (this->other != nullptr && this->ThisCamera != nullptr)
        {
            ThisCamera->x = other->Position.x - (ThisCamera->viewPort.w * X);
            ThisCamera->y = other->Position.y - (ThisCamera->viewPort.h * Y);
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