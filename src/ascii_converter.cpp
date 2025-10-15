#include "ascii_converter.h"
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cstring>

namespace ascii_art {

char AsciiConverter::brightnessToAscii(float brightness) const {
    // Brightness is in range [0, 1]
    static const int numChars = std::strlen(ASCII_CHARS);
    int index = static_cast<int>(brightness * (numChars - 1));
    index = std::max(0, std::min(numChars - 1, index));
    return ASCII_CHARS[index];
}

std::string AsciiConverter::getAnsiColorCode(const Color& color) const {
    // Use ANSI 24-bit true color escape codes
    std::stringstream ss;
    ss << "\033[38;2;" << static_cast<int>(color.r) << ";" 
       << static_cast<int>(color.g) << ";" << static_cast<int>(color.b) << "m";
    return ss.str();
}

float AsciiConverter::getBrightness(const Color& color) const {
    // Use luminance formula (weighted average)
    return (0.299f * color.r + 0.587f * color.g + 0.114f * color.b) / 255.0f;
}

Color AsciiConverter::getAverageColor(const Image& img, int startX, int startY, 
                                     int blockWidth, int blockHeight) const {
    long sumR = 0, sumG = 0, sumB = 0;
    int count = 0;
    
    for (int y = startY; y < startY + blockHeight && y < img.height; ++y) {
        for (int x = startX; x < startX + blockWidth && x < img.width; ++x) {
            Color pixel = img.getPixel(x, y);
            sumR += pixel.r;
            sumG += pixel.g;
            sumB += pixel.b;
            count++;
        }
    }
    
    if (count == 0) {
        return Color(0, 0, 0);
    }
    
    return Color(
        static_cast<unsigned char>(sumR / count),
        static_cast<unsigned char>(sumG / count),
        static_cast<unsigned char>(sumB / count)
    );
}

std::string AsciiConverter::convertToAscii(const Image& img, bool useColor) {
    std::stringstream result;
    
    // Characters are roughly twice as tall as they are wide, so we sample every 2 rows
    constexpr int BLOCK_HEIGHT = 2;
    constexpr int BLOCK_WIDTH = 1;
    
    for (int y = 0; y < img.height; y += BLOCK_HEIGHT) {
        for (int x = 0; x < img.width; x += BLOCK_WIDTH) {
            // Get average color for this block
            Color avgColor = getAverageColor(img, x, y, BLOCK_WIDTH, BLOCK_HEIGHT);
            
            // Calculate brightness
            float brightness = getBrightness(avgColor);
            
            // Convert to ASCII character
            char asciiChar = brightnessToAscii(brightness);
            
            // Apply color if requested
            if (useColor) {
                result << getAnsiColorCode(avgColor);
            }
            
            result << asciiChar;
        }
        
        // Reset color at end of line
        if (useColor) {
            result << "\033[0m";
        }
        result << '\n';
    }
    
    return result.str();
}

std::string AsciiConverter::convertToAsciiWithWidth(const Image& img, int targetWidth, bool useColor) {
    // Calculate target height maintaining aspect ratio
    // Account for character aspect ratio (characters are ~2x taller than wide)
    constexpr float CHARACTER_ASPECT_RATIO = 0.5f;
    constexpr int BLOCK_HEIGHT = 2;
    
    float aspectRatio = static_cast<float>(img.height) / static_cast<float>(img.width);
    int targetHeight = static_cast<int>(targetWidth * aspectRatio * CHARACTER_ASPECT_RATIO);
    
    ImageProcessor processor;
    auto resized = processor.resize(img, targetWidth, targetHeight * BLOCK_HEIGHT);
    
    if (!resized) {
        return "";
    }
    
    return convertToAscii(*resized, useColor);
}

} // namespace ascii_art
