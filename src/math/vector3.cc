// src/math/vector3.cc
#include "vector3.h"
#include <cmath>

namespace Math
{

    Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

    Vector3::Vector3(float xVal, float yVal, float zVal)
        : x(xVal), y(yVal), z(zVal) {}

    Vector3 Vector3::operator+(const Vector3 &rhs) const
    {
        return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    Vector3 Vector3::operator-(const Vector3 &rhs) const
    {
        return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    Vector3 Vector3::operator*(float scalar) const
    {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    float Vector3::Length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    void Vector3::Normalize()
    {
        float len = Length();
        if (len > 0.0f)
        {
            x /= len;
            y /= len;
            z /= len;
        }
    }

} // namespace Math
