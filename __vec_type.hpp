#ifndef __VEC_TYPE_HPP
#define __VEC_TYPE_HPP

#include <cassert>

#define __TINY_MAT_MAX_DIM__ 4

namespace tinymat {

template<int C>
struct vec;

typedef vec<1> vec1;
typedef vec<2> vec2;
typedef vec<3> vec3;
typedef vec<4> vec4;

template<int V, int C>
struct mat;

typedef mat<1, 1> mat1;
typedef mat<2, 2> mat2;
typedef mat<3, 3> mat3;
typedef mat<4, 4> mat4;

typedef mat<1, 1> mat1x1;
typedef mat<1, 2> mat1x2;
typedef mat<1, 3> mat1x3;
typedef mat<1, 4> mat1x4;

typedef mat<2, 1> mat2x1;
typedef mat<2, 2> mat2x2;
typedef mat<2, 3> mat2x3;
typedef mat<2, 4> mat2x4;

typedef mat<3, 1> mat3x1;
typedef mat<3, 2> mat3x2;
typedef mat<3, 3> mat3x3;
typedef mat<3, 4> mat3x4;

typedef mat<4, 1> mat4x1;
typedef mat<4, 2> mat4x2;
typedef mat<4, 3> mat4x3;
typedef mat<4, 4> mat4x4;

#define __for_dec(i, i0, limit) for (int i = i0; i < limit; ++i)

template<int C>
struct vec
{
    float data[C]{};

    static constexpr int size = C;

    float x() const { return data[0]; }
    float y() const { return data[1]; }
    float z() const { return data[2]; }
    float w() const { return data[3]; }
    
    float& x() { return data[0]; }
    float& y() { return data[1]; }
    float& z() { return data[2]; }
    float& w() { return data[3]; }

    template<int I>
    void _init() {
        if (I == 1)
        {
            __for_dec(i, I, size)
            {
                data[i] = data[0];
            }
        }
#ifdef __TINYMAT_STRICT_INIT__
        assert(I <= 1 || I == size);
#endif
    }
    
    template<int I, typename T, typename... Args>
    void _init(T first, Args... args)
    {
        assert(I < C);
        data[I] = first;
        _init<I + 1>(args...);
    }

    template<int I, int Oc, typename... Args>
    void _init(const vec<Oc>& first, Args... args)
    {
        __for_dec(i, 0, first.size)
        {
            assert(I + i < C);
            data[I + i] = first[i];
        }
        _init<I + first.size>(args...);
    }

    template<typename... Args>
    vec(Args... args)
    {
        assert(C > 0 && C <= __TINY_MAT_MAX_DIM__);
        __for_dec(i, 0, size)
        {
            data[i] = (i == 3 ? 1.0f : 0.0f);
        }
        _init<0>(args...);
    }

    float& operator[](int i) { assert(i >= 0 && i < size); return data[i]; }
    float operator[](int i) const { assert(i >= 0 && i < size); return data[i]; }
    operator float() { assert(size == 1); return data[0]; }

    vec<C>& operator+=(const vec<C>& o);
    vec<C>& operator-=(const vec<C>& o);
    vec<C>& operator*=(const vec<C>& o);
    vec<C>& operator/=(const vec<C>& o);
};

template<int V, int C>
struct mat
{
    // column-major matrix
    vec<C> data[V]{};

    static constexpr int size = V * C;
    static constexpr int width = V;
    static constexpr int height = C;

    template<int I>
    void _init()
    {
        if (I == 1)
        {
            __for_dec(i, 0, width)
            {
                __for_dec(j, 0, height)
                {
                    data[i][j] = (i == j ? data[0][0] : 0.0f);
                }
            }
        }
#ifdef __TINYMAT_STRICT_INIT__
        assert(I <= 1 || I == size);
#endif
    }

    template<int I, typename T, typename... Args>
    void _init(T first, Args... args)
    {
        assert(I < size);
        data[I / height][I % height] = first;
        _init<I + 1>(args...);
    }

    template<int I, int Vc, typename... Args>
    void _init(const vec<Vc>& first, Args... args)
    {
#ifdef __TINYMAT_STRICT_INIT__
        assert(I % C == 0 && Vc == C);
#endif
        __for_dec(i, 0, first.size)
        {
            assert(I + i < size);
            data[(I + i) / height][(I + i) % height] = first[i];
        }
        _init<I + first.size>(args...);
    }

    template<typename... Args>
    mat(Args... args)
    {
        assert(C > 0 && C <= __TINY_MAT_MAX_DIM__ && V > 0 && V <= __TINY_MAT_MAX_DIM__);
        __for_dec(i, 0, width)
        {
            __for_dec(j, 0, height)
            {
                data[i][j] = (i == j ? 1.0f : 0.0f);
            }
        }
        _init<0>(args...);
    }

    struct lineVec
    {
        mat<V, C>& ofw;
        const int lineID;

        float operator[](int i) const
        {
            return ofw.data[i][lineID];
        }

        float& operator[](int i)
        {
            return ofw.data[i][lineID];
        }
    };

    vec<C>& operator[](int i) { assert(i >= 0 && i < width); return data[i]; }
    vec<C> operator[](int i) const { assert(i >= 0 && i < width); return data[i]; }
    operator float() { assert(size == 1); return data[0][0]; }

    lineVec& line(int i) { assert(i >= 0 && i < height); return lineVec{ *this, i }; }
    const lineVec line(int i) const { assert(i >= 0 && i < height); return lineVec{ *const_cast<mat<V, C>* >(this), i }; }
    
    mat<V, C>& operator+=(const mat<V, C>& o);
    mat<V, C>& operator-=(const mat<V, C>& o);
    mat<V, C>& operator*=(const float& o);
    mat<V, C>& operator/=(const float& o);
};

}

#endif