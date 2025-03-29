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