// src/math/quaternion.h
#pragma once

namespace Math
{

    class Quaternion
    {
    public:
        float x, y, z, w;

        Quaternion();
        Quaternion(float xVal, float yVal, float zVal, float wVal);

        static Quaternion Identity();
        Quaternion operator*(const Quaternion &rhs) const;

        void Normalize();
    };

} // namespace Math
