// src/math/matrix4.cc
#include "matrix4.h"
#include <cstring>

namespace Math
{

    Matrix4::Matrix4()
    {
        SetIdentity();
    }

    void Matrix4::SetIdentity()
    {
        std::memset(m, 0, sizeof(m));
        m[0] = 1.0f;
        m[5] = 1.0f;
        m[10] = 1.0f;
        m[15] = 1.0f;
    }

    Matrix4 Matrix4::Identity()
    {
        Matrix4 mat;
        mat.SetIdentity();
        return mat;
    }

    // Implement additional transformation methods as needed

} // namespace Math
