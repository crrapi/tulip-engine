// src/math/vector3.h
#pragma once

namespace Math
{

    class Vector3
    {
    public:
        float x, y, z;

        Vector3();
        Vector3(float xVal, float yVal, float zVal);

        Vector3 operator+(const Vector3 &rhs) const;
        Vector3 operator-(const Vector3 &rhs) const;
        Vector3 operator*(float scalar) const;

        float Length() const;
        void Normalize();
    };

} // namespace Math
