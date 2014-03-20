#include "error.hpp"
#include <stdexcept>
#include <cstdio>
#include <cstdarg>
#include <vector>

namespace gomu
{

void error(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    auto size = vsnprintf(nullptr, 0, fmt, args);
    std::vector<char> buf(size + 1);
    va_end(args);
    va_start(args, fmt);
    vsnprintf(buf.data(), buf.size(), fmt, args);
    va_end(args);
    throw std::runtime_error(buf.data());
}

}
