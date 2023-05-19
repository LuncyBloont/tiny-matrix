#include <iostream>
#include <ctime>
// ReSharper disable once IdentifierTypo
#define _TINYMAT_USE_FAST_SQRT_  // NOLINT(bugprone-reserved-identifier, clang-diagnostic-reserved-macro-identifier)
// ReSharper disable once IdentifierTypo
#define _TINYMAT_STRICT_INIT_  // NOLINT(bugprone-reserved-identifier, clang-diagnostic-reserved-macro-identifier)
#include "matrix.hpp"
#include "mat2str.hpp"

using namespace tinymat;

#define _DEBUG_MACRO(s) #s
#define DEBUG_MACRO(s) _DEBUG_MACRO(s)

template <int C>
void _printVec(const vec<C>& v)
{
    std::cout << "vec" << C << "( ";
    for (int i = 0; i < C; ++i)
    {
        std::cout << v[i] << (i != C - 1 ? ", " : "");
    }
    std::cout << " )\n";
}

template <int V, int C>
void _printMat(const mat<V, C>& m)
{
    std::cout << "mat" << m.width << "x" << m.height << ":\n";
    for (int i = 0; i < m.height; ++i)
    {
        std::cout << "    | ";
        for (int j = 0; j < m.width; ++j)
        {
            std::cout << m[j][i] << (j != m.width - 1 ? ", " : "");
        }
        std::cout << " |\n";
    }
}

#define printVec(...) do { std::cout << "( line " << __LINE__ << " ) " << #__VA_ARGS__ << ": "; _printVec(__VA_ARGS__); } while (0)
#define printVec1(...) do { std::cout << "( line " << __LINE__ << " ) " << #__VA_ARGS__ << ": "; _printVec<1>(__VA_ARGS__); } while (0)
#define printMat(...) do { std::cout << "( line " << __LINE__ << " ) " << #__VA_ARGS__ << ": "; _printMat(__VA_ARGS__); } while (0)

int main()
{
    vec2 v0(2.0f, 3.0f);
    vec3 v1(6.0f, v0);
    vec4 v3(5.4f, -3.2f, 1.0f, 2.3f);

    printVec(v0);
    v0.y() = 7.0f;
    printVec(v0);
    printVec(v1);
    // printVec(vec4(v0, 5.6f));
    // printVec(vec4(v0, 5.6f, 2.3f));
    printVec(vec4());
    printVec(vec4(4.5f));
    printVec(vec4(4.5f));
    printVec(v3 * 2.0f);
    printVec(v3 + 3.0f);
    printVec(v3 * 10.0f);
    printVec(0.1f * v3);
    printVec(0.1f / v3);
    printVec(vec4(10.0f) + v3);
    printVec(sqrt(vec3(4.0f)));
    printVec(normalize(v0));

    printVec(v3);
    printVec(v3 += 3.0f);
    printVec(v3);

    printVec(cross(vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f)));
    printVec1(dot(v1, cross(v1, vec3(3.4f, 2.6f, 0.3f))));

    printVec(abs(v3));
    printVec(fract(v3));
    printVec(min(v3, vec4(2.0f, 4.7f, 7.2f, 0.0f)));
    printVec(max(v3, vec4(2.0f, 4.7f, 7.2f, 0.0f)));

    std::cout << sqrt<1>(4.0f) << std::endl;
    std::cout << length(v1) << std::endl;
    std::cout << distance(vec2(3.0f, 2.0f), vec2(7.0f, 5.0f)) << std::endl;
    std::cout << length(normalize(v0)) << std::endl;

    std::cout << DEBUG_MACRO(__for_dec(i, 5, 6)) << std::endl;

    printMat(mat3());
    printMat(mat3(4.5f));
    printMat(mat3(vec3(3.0f), vec3(0.4f, 1.0f, 0.0f), vec3(6.0f)));
    // printMat(mat3(vec4(3.0f), vec3(0.4f, 1.0f, 0.0f), vec2(6.0f)));
    // printMat(mat3(vec4(3.0f), vec2(4.5f, 1.2f)));
    printMat(mat3(vec3(3.0f), vec3(4.5f, 1.2f, 5.0f), 1.3f, 1.5f, 1.6f));

    mat3 m0(1.0f, 0.0f, 3.0f, 0.0f, 1.0f, 2.3f, 0.0f, 0.0f, 2.0f);

    printVec(v1);
    printVec(mul(mat3(), v1));
    printVec(mul(v1, mat3()));
    printMat(m0);
    printVec(v1);

    vec3 tmp;
    vec3 tmpv(2.0f, 2.5f, 1.3f);
    clock_t t = clock();
    for (int i = 0; i < 10000; ++i)
    {
        tmpv += mul(tmpv, m0);
        tmp += tmpv;
        tmp += 2.0f;
    }
    std::cout << "m * v: " << float(clock() - t) * 1.0f / CLOCKS_PER_SEC * 1000.0f << "ms" << std::endl;
    printVec(tmp);

    t = clock();
    tmpv = vec3(1.4f, 1.6f, 1.3f);
    for (int i = 0; i < 10000; ++i)
    {
        tmpv += mul(tmpv, m0);
        tmp += tmpv;
        tmp += 2.0f;
    }
    std::cout << "v * m: " << float(clock() - t) * 1.0f / CLOCKS_PER_SEC * 1000.0f << "ms" << std::endl;
    printVec(tmp);

    printVec(mul(m0, v1));
    printVec(mul(v1, m0));

    mat3 ma(3.0f, 1.1f, -1.4f, 9.2f, 7.0f, 6.2f, 4.0f, 3.6f, 0.5f);
    mat3 mb(1.3f, 4.3f, 10.0f, 1.8f, 7.7f, 6.0f, 0.4f, 0.5f, 3.2f);
    mat3 mr = ma * mb;
    vec3 mv0(3.0f, 2.4f, 1.3f);
    printMat(ma);
    printMat(mb);
    printMat(mr);
    printVec(mul(mv0, mb));
    printVec(mul(mb, mv0));
    printMat(ma * mat3());
    printMat(mat3() * mb);
    printVec(atan(vec2(3.4f, 1.0f), vec2(3.4f * pow(3.0f, 0.5f), 1.0f)) / 2.0f / 3.1415926534f * 360.0f);

    printVec(mix<2>(vec2(0.3f, 5.3f), vec2(10.0f, 4.0f), 0.2f));
    printVec(mix<2>(vec2(0.3f, 5.3f), vec2(10.0f, 4.0f), 0.2f));

    printMat(mat2x1());
    printMat(mat1x2() * mat2x1());
    printMat(mat2x1() * mat1x2());
    printMat(mat3x2() * mat2x3());
    printMat(mat2x3() * mat3x2());
    printMat(mat2x3());
    printMat(mat3x2());

    mat3x2 m32 = mat3x2(vec2(3.4f, 5.5f), vec2(3.0f, 0.8f), vec2(0.1f, 0.2f));
    printMat(m32);
    printMat(m32 += mat3x2(1.0f));
    printMat(transpose(m32));

    std::cout << det(mat3(3.0f, 4.5f, 6.7f, 7.0f, 1.0f, 3.2f, 2.0f, 0.7f, 0.5f)) << std::endl;

    mat3 mx = mat3(4.5f, 7.2f, 6.7f, 3.2f, 0.3f, 1.1f, 6.4f, -4.5f, 10.0f);
    printMat(mx);
    std::cout << det(mx) << std::endl;
    printMat(inverse(mx));
    printMat(inverse(mx) * mx);
    printMat(mx * inverse(mx));
    printMat(mx * inverse(mx) * mx);

    printVec(mod(vec3(1.5f, 2.3f, 0.8f), vec3(2.0f)));
    printVec(floor(vec3(1.5f, 2.3f, 0.8f)));

    vec2 v00 = vec2(0.5f, 1.34f);
    vec3 p00 = vec3(v00, 0.2f);
    printVec(v00);
    printVec(p00);

    std::cout << v3 << std::endl;
    std::cout << m32 << std::endl;
    std::cout << mr << std::endl;

    std::cout << "exp: " << exp<1>(2.74f) << std::endl;
    std::cout << "exp: " << exp(vec3(2.738f)) << std::endl;
    
    std::cout << "exp2: " << exp2<1>(4.0f) << std::endl;
    std::cout << "exp2: " << exp2(vec3(3.0f)) << std::endl;

    std::cout << "log: " << log<1>(2.74f) << std::endl;
    std::cout << "log: " << log(vec3(2.738f)) << std::endl;

    std::cout << "log2: " << log2<1>(2.74f) << std::endl;
    std::cout << "log2: " << log2(vec3(2.738f)) << std::endl;

    std::cout << "fract: " << fract<1>(2.74f) << std::endl;
    std::cout << "fract: " << fract(vec3(2.738f)) << std::endl;

    std::cout << "mod: " << mod<1>(2.74f, 1.1f) << std::endl;
    std::cout << "mod: " << mod<3>(vec3(2.738f), 2.0f) << std::endl;

    std::cout << "end\n";

    return 0;
}
