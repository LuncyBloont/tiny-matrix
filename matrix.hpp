#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cmath>
#include <algorithm>
#include "mat_func.hpp"

#include "__vec_type.hpp" // IWYU pragma: keep

namespace tinymat {

#define _TINYMAT_VEC_OP +
#include "__vec_op.hpp"

#define _TINYMAT_VEC_OP -
#include "__vec_op.hpp"

#define _TINYMAT_VEC_OP *
#include "__vec_op.hpp"

#define _TINYMAT_VEC_OP /
#include "__vec_op.hpp"

template<int V, int C>
mat<V, C>& mat<V, C>::operator+=(const mat<V, C>& o)
{
    *this = *this + o;
    return *this;
}

template<int V, int C>
mat<V, C>& mat<V, C>::operator-=(const mat<V, C>& o)
{
    *this = *this - o;
    return *this;
}

template<int V, int C>
mat<V, C>& mat<V, C>::operator*=(const float& s)
{
    *this = *this * s;
    return *this;
}

template<int V, int C>
mat<V, C>& mat<V, C>::operator/=(const float& s)
{
    *this = *this / s;
    return *this;
}
    
inline float __fastSqrtInv(const float& k)
{
    union { float f; int i; } val{ k };
    val.i = 0x5f3759df - (val.i >> 1);
    return val.f * (1.5f - 0.5f * k * val.f * val.f);
}

inline float sqrtInv(const float& k)
{
#ifdef __TINYMAT_USE_FAST_SQRT__
    return __fastSqrtInv(k);
#else
    return 1.0f / sqrtf(k);
#endif
}

inline float fastSqrt(const float& k)
{
    return 1.0f / __fastSqrtInv(k);
}

inline float fract(float k)
{
    return k - floor(k);
}

inline float step(float edge, float x)
{
    return x < edge ? 0.0f : 1.0f;
}

inline float clamp(const float& c, const float& m0, const float& m1)
{
    return std::max(std::min(c, m1), m0);
}

inline float mix(const float& a, const float& b, const float& m)
{
    return a * (1.0f - m) + b * m;
}

#define _TINYMAT_VEC_FUNC abs
#define _TINYMAT_VEC_REAL_FUNC std::abs
#include "__vec_func.hpp"

#define _TINYMAT_VEC_FUNC sign
#define _TINYMAT_VEC_REAL_FUNC signf
#include "__vec_func.hpp"

#define _TINYMAT_VEC_FUNC floor
#include "__vec_func.hpp"

#define _TINYMAT_VEC_FUNC ceil
#include "__vec_func.hpp"

#define _TINYMAT_VEC_FUNC cos
#include "__vec_func.hpp"

#define _TINYMAT_VEC_FUNC sin
#include "__vec_func.hpp"

#define _TINYMAT_VEC_FUNC tan
#include "__vec_func.hpp"

#define _TINYMAT_VEC_FUNC acos
#include "__vec_func.hpp"

#define _TINYMAT_VEC_FUNC asin
#include "__vec_func.hpp"

#define _TINYMAT_VEC_FUNC atan
#include "__vec_func.hpp"

#define _TINYMAT_VEC_FUNC exp
#include "__vec_func.hpp"

#define _TINYMAT_VEC_FUNC log
#include "__vec_func.hpp"

#define _TINYMAT_VEC_FUNC exp2
#include "__vec_func.hpp"

#define _TINYMAT_VEC_FUNC log2
#include "__vec_func.hpp"

#define _TINYMAT_VEC_FUNC fract
#include "__vec_func.hpp"

#define _TINYMAT_VEC_FUNC mod
#define _TINYMAT_VEC_REAL_FUNC modf
#include "__vec_func2.hpp"

#define _TINYMAT_VEC_FUNC min
#define _TINYMAT_VEC_REAL_FUNC std::min
#include "__vec_func2.hpp"

#define _TINYMAT_VEC_FUNC max
#define _TINYMAT_VEC_REAL_FUNC std::max
#include "__vec_func2.hpp"

#define _TINYMAT_VEC_FUNC atan
#define _TINYMAT_VEC_REAL_FUNC atan2
#include "__vec_func2.hpp"

#define _TINYMAT_VEC_FUNC pow
#include "__vec_func2.hpp"

#define _TINYMAT_VEC_FUNC step
#include "__vec_func2.hpp"

#define _TINYMAT_VEC_FUNC clamp
#include "__vec_func3.hpp"

#define _TINYMAT_VEC_FUNC mix
#include "__vec_func3.hpp"

template<int C>
vec<C> sqrt(const vec<C>& k)
{
    vec<C> res;
    __for_dec(i, 0, k.size)
    {
        res[i] = 1.0f / sqrtInv(k[i]);
    }
    return res;
}

template<int C>
float dot(const vec<C>& o0, const vec<C>& o1)
{
    float res = 0.0f;
    __for_dec(i, 0, o0.size) { res += o0[i] * o1[i]; }
    return res;
}

template<int C>
float length(const vec<C>& o)
{
    return sqrt<1>(dot(o, o));
}

template<int C>
float distance(const vec<C>& o0, const vec<C>& o1)
{
    return length(o0 - o1);
}

template<int C>
vec<C> normalize(const vec<C>& v)
{
    return v * sqrtInv(dot(v, v));
}

inline vec3 cross(const vec3& o0, const vec3& o1)
{
    return vec3(
        o0.y() * o1.z() - o0.z() * o1.y(),
        o0.z() * o1.x() - o0.x() * o1.z(),
        o0.x() * o1.y() - o0.y() * o1.x() 
        );
}

template<int Mv, int Mc>
vec<Mc> mul(const mat<Mv, Mc>& m, const vec<Mv> v)
{
    vec<Mc> res;
    __for_dec(i, 0, res.size)
    {
        vec<m.width> tmp; 
        __for_dec(j, 0, m.width) { tmp[j] = m[j][i]; }
        res[i] = dot(tmp, v);
    }
    return res;
}

template<int Vc, int Mv>
vec<Mv> mul(const vec<Vc> v, const mat<Mv, Vc>& m)
{
    vec<Mv> res;
    __for_dec(i, 0, m.width)
    {
        res[i] = dot(m[i], v);
    }
    return res;
}

template<int M0c, int M0v, int M1v>
mat<M1v, M0c> operator*(const mat<M0v, M0c> m0, const mat<M1v, M0v>& m1)
{
    mat<M1v, M0c> res;
    __for_dec(i, 0, m1.width)
    {
        res[i] = mul(m0, m1[i]);
    }
    return res;
}

template<int V, int C>
mat<V, C> operator+(const mat<V, C>& m0, const mat<V, C>& m1)
{
    mat<V, C> res;
    __for_dec(i, 0, m0.width) { res[i] = m0[i] + m1[i]; }
    return res;
}

template<int V, int C>
mat<V, C> operator-(const mat<V, C>& m0, const mat<V, C>& m1)
{
    mat<V, C> res;
    __for_dec(i, 0, m0.width) { res[i] = m0[i] - m1[i]; }
    return res;
}

template<int V, int C>
mat<V, C> operator*(const mat<V, C>& m0, const float& s)
{
    mat<V, C> res;
    __for_dec(i, 0, m0.width) { res[i] = m0[i] * s; }
    return res;
}

template<int V, int C>
mat<V, C> operator*(const float& s, const mat<V, C>& m0)
{
    mat<V, C> res;
    __for_dec(i, 0, m0.width) { res[i] = s * m0[i]; }
    return res;
}

template<int V, int C>
mat<V, C> operator/(const mat<V, C>& m0, const float& s)
{
    mat<V, C> res;
    __for_dec(i, 0, m0.width) { res[i] = m0[i] / s; }
    return res;
}

template<int V, int C>
mat<V, C> operator/(const float& s, const mat<V, C>& m0)
{
    mat<V, C> res;
    __for_dec(i, 0, m0.width) { res[i] = s / m0[i]; }
    return res;
}

template<int V, int C>
mat<C, V> transpose(const mat<V, C>& m)
{
    mat<C, V> res;
    __for_dec(i, 0, res.width)
    {
        __for_dec(j, 0, res.height)
        {
            res[i][j] = m[j][i];
        }
    }
    return res;
}

template<int C>
mat<C, C> inverse(const mat<C, C>& m)
{
    return adjugate(m) / det(m);
}

} // tinymat
#endif