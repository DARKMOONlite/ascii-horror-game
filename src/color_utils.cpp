#include "color_utils.hpp"
#include <sstream>

std::string ColorUtils::rgb_to_ansi(int r, int g, int b) {
    std::ostringstream oss;
    oss << "\033[38;2;" << r << ";" << g << ";" << b << "m";
    return oss.str();
}

std::string ColorUtils::reset_color() {
    return "\033[0m";
}
