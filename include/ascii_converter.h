#pragma once

#include "image_processor.h"
#include <string>
#include <vector>

namespace ascii_art {

class AsciiConverter {
public:
    AsciiConverter() = default;
    ~AsciiConverter() = default;
    
    // Convert image to ASCII art with colors
    std::string convertToAscii(const Image& img, bool useColor = true);
    
    // Convert image to ASCII with specified width (maintains aspect ratio)
    std::string convertToAsciiWithWidth(const Image& img, int targetWidth, bool useColor = true);
    
private:
    // Map brightness to ASCII character
    char brightnessToAscii(float brightness) const;
    
    // Generate ANSI color code for RGB color
    std::string getAnsiColorCode(const Color& color) const;
    
    // Calculate average color for a block of pixels
    Color getAverageColor(const Image& img, int startX, int startY, int blockWidth, int blockHeight) const;
    
    // Calculate brightness of a pixel
    float getBrightness(const Color& color) const;
    
    // ASCII characters from darkest to brightest
    static constexpr const char* ASCII_CHARS = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
};

} // namespace ascii_art
