// src/math/vector2.h
#pragma once

namespace Math
{

    class Vector2
    {
    public:
        float x, y;

        Vector2();
        Vector2(float xVal, float yVal);

        Vector2 operator+(const Vector2 &rhs) const;
        Vector2 operator-(const Vector2 &rhs) const;
        Vector2 operator*(float scalar) const;
        float Length() const;
        void Normalize();
    };

} // namespace Math
