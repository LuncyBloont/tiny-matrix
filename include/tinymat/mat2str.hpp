#pragma once

#include "matrix.hpp"
#include <iostream>

namespace tinymat
{
    template <int C>
    std::ostream& operator<<(std::ostream& stream, const tinymat::vec<C>& v)
    {
        stream << "vec" << v.size << "(";
        for (int i = 0; i < v.size - 1; ++i)
        {
            stream << v[i] << ",";
        }
        stream << v[v.size - 1] << ")";
        return stream;
    }

    template <int V, int C>
    std::ostream& operator<<(std::ostream& stream, const tinymat::mat<V, C>& m)
    {
        stream << "\n    mat" << V << "x" << C << std::endl;

        for (int c = 0; c < m.height; ++c)
        {
            stream << "        ";
            for (int v = 0; v < m.width - 1; ++v)
            {
                stream << m[v][c] << ",";
            }
            stream << m[m.width - 1][c] << std::endl;
        }

        stream << std::endl;

        return stream;
    }
}
