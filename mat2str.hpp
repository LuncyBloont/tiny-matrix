#pragma once

#include <iostream>

template<int C>
std::ostream& operator<<(std::ostream& stream, const tinymat::vec<C>& v)
{
    stream << "vec" << v.size << "(";
    for (int i = 0; i < v.size - 1; ++i) { stream << v[i] << ","; }
    stream << v[v.size - 1] << ")";
    return stream;
}

template<int V, int C>
std::ostream& operator<<(std::ostream& stream, const tinymat::mat<V, C>& m)
{
    stream << "mat" << V << "x" << C << "{";
    for (int i = 0; i < m.height; ++i)
    {
        stream << "    " << "| ";
        for (int j = 0; j < m.width; ++j)
        {
            steam << m[j][i] << " ";
        }
        stream << "\n";
    }
}

