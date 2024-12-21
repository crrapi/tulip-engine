// src/math/quaternion.cc
#include "quaternion.h"
#include <cmath>

namespace Math
{

    Quaternion::Quaternion() : x(0), y(0), z(0), w(1) {}

    Quaternion::Quaternion(float xVal, float yVal, float zVal, float wVal)
        : x(xVal), y(yVal), z(zVal), w(wVal) {}

    Quaternion Quaternion::Identity()
    {
        return Quaternion(0, 0, 0, 1);
    }

    Quaternion Quaternion::operator*(const Quaternion &rhs) const
    {
        return Quaternion(
            w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
            w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x,
            w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w,
            w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z);
    }

    void Quaternion::Normalize()
    {
        float mag = std::sqrt(x * x + y * y + z * z + w * w);
        if (mag > 0.0f)
        {
            x /= mag;
            y /= mag;
            z /= mag;
            w /= mag;
        }
    }

} // namespace Math
