#ifndef COLOUR_UTILS_HPP
#define COLOUR_UTILS_HPP

#include <string>

class ColorUtils {
public:
    static std::string rgb_to_ansi(int r, int g, int b);
    static std::string reset_color();
    static char get_ascii_char(int brightness);
    static inline const std::string full_density_range = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.            ";

};



#endif