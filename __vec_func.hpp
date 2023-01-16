#include "__vec_type.hpp"

#ifndef _TINYMAT_VEC_FUNC
#define _TINYMAT_VEC_FUNC abs
#endif

#ifndef _TINYMAT_VEC_REAL_FUNC
#define _TINYMAT_VEC_REAL_FUNC _TINYMAT_VEC_FUNC
#endif

template<int C>
vec<C> _TINYMAT_VEC_FUNC(const vec<C>& v)
{
    vec<C> res;
    __for_dec(i, 0, v.size) { res[i] = _TINYMAT_VEC_REAL_FUNC(v[i]); }
    return res;
}

#undef _TINYMAT_VEC_FUNC
#undef _TINYMAT_VEC_REAL_FUNC