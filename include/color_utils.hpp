#pragma once

#include <string>

class ColorUtils {
public:
    static std::string rgb_to_ansi(int r, int g, int b);
    static std::string reset_color();
};
