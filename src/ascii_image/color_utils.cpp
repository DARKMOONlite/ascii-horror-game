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

char ColorUtils::get_ascii_char(int brightness) {
    int n = full_density_range.length();
    int k = static_cast<int>(brightness / 256.0 * n);
    k = std::min(k, n - 1);  // Ensure k doesn't exceed bounds
    return full_density_range[n - 1 - k];
}