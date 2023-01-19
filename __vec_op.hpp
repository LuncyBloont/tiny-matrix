#include "__vec_type.hpp"

#ifndef _TINYMAT_VEC_OP
#define _TINYMAT_VEC_OP +
#endif

#define _TINYMAT_VEC_LINK_OP__(s) s##=
#define _TINYMAT_VEC_OP_EQUAL(s) _TINYMAT_VEC_LINK_OP__(s)

namespace tinymat {

template<int C>
vec<C> operator _TINYMAT_VEC_OP(const float& scale, const vec<C>& o)
{
    vec<C> res;
    __for_dec(i, 0, o.size) { res[i] = scale _TINYMAT_VEC_OP o.data[i]; }
    return res;
}

template<int C>
vec<C> operator _TINYMAT_VEC_OP(const vec<C>& o, const float& scale)
{
    vec<C> res;
    __for_dec(i, 0, o.size) { res[i] = o.data[i] _TINYMAT_VEC_OP scale; }
    return res;
}

template<int C>
vec<C> operator _TINYMAT_VEC_OP(const vec<C>& o0, const vec<C>& o1)
{
    vec<C> res;
    __for_dec(i, 0, o0.size) { res[i] = o0[i] _TINYMAT_VEC_OP o1[i]; }
    return res;
}

template<int C>
vec<C>& vec<C>::operator _TINYMAT_VEC_OP_EQUAL(_TINYMAT_VEC_OP)(const vec<C>& o1)
{
    *this = *this + o1;
    return *this;
}

}

#undef _TINYMAT_VEC_OP