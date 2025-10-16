#pragma once

#include <string>
#include <stb_image.h>
#include <image.hpp>
class AsciiGenerator {
public:
    AsciiGenerator(int contrast = 10, int default_width = 100);
    
    void generate_ascii_art(const std::string& image_path, int width = -1);
    void set_contrast(int contrast);
    void set_default_width(int width);

private:
    int contrast_;
    int default_width_;
    std::string density_;
    
    void initialize_density();
    char get_ascii_char(int brightness) const;
    int calculate_ascii_height(int width, int orig_width, int orig_height) const;
};
