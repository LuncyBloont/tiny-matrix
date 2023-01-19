#include "__vec_type.hpp"

#ifndef _TINYMAT_VEC_FUNC
#define _TINYMAT_VEC_FUNC min
#endif

#ifndef _TINYMAT_VEC_REAL_FUNC
#define _TINYMAT_VEC_REAL_FUNC _TINYMAT_VEC_FUNC
#endif

using namespace tinymat;

template<int C>
vec<C> _TINYMAT_VEC_FUNC(const vec<C>& o0, const vec<C>& o1, const vec<C>& o2)
{
    vec<C> res;
    __for_dec(i, 0, o0.size) { res[i] = _TINYMAT_VEC_REAL_FUNC(o0[i], o1[i], o2[i]); }
    return res;
}

#undef _TINYMAT_VEC_FUNC
#undef _TINYMAT_VEC_REAL_FUNC