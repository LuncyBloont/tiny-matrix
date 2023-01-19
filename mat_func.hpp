#ifndef __TINTMAT_MAT_FUNC_HPP
#define __TINTMAT_MAT_FUNC_HPP

#include "__vec_type.hpp"

using namespace tinymat;

inline float det(const mat1& m)
{
    return m[0][0];
}

template<int C>
float det(const mat<C, C>& m)
{
    int k = 1;
    float res = 0.0f;
    __for_dec(i, 0, m.width)
    {
        mat<C - 1, C - 1> sub;
        __for_dec(si, 0, m.width)
        {
            __for_dec(sj, 1, m.height)
            {
                if (si == i) { continue; }
                sub[si < i ? si : si - 1][sj - 1] = m[si][sj];
            }
        }
        res += m[i][0] * det(sub) * k;
        k *= -1;
    }
    return res;
}

inline mat1 adjugate(const mat1& m)
{
    return mat1(1.0f);
}

template<int C>
mat<C, C> adjugate(const mat<C, C>& m)
{
    mat<C, C> res;
    int k = 1;
    __for_dec(i, 0, m.width)
    {
        __for_dec(j, 0, m.height)
        {
            mat<C - 1, C - 1> sub;
            __for_dec(si, 0, m.width)
            {
                __for_dec(sj, 0, m.height)
                {
                    if (si == i || sj == j) { continue; }
                    sub[si < i ? si : si - 1][sj < j ? sj : sj - 1] = m[si][sj];
                }
            }
            res[j][i] = det(sub) * k;
            k *= -1;
        }
    }
    return res;
}

#endif

