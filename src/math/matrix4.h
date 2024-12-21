// src/math/matrix4.h
#pragma once

namespace Math
{

    class Matrix4
    {
    public:
        float m[16];

        Matrix4();
        void SetIdentity();
        static Matrix4 Identity();

        // Additional transformation methods, e.g., Translate, Rotate, Scale
    };

} // namespace Math
