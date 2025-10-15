#include "ascii_converter.h"
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cstring>

namespace ascii_art {

char AsciiConverter::brightnessToAscii(float brightness) const {
    // Brightness is in range [0, 1]
    int numChars = std::strlen(ASCII_CHARS);
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
    int blockHeight = 2;
    int blockWidth = 1;
    
    for (int y = 0; y < img.height; y += blockHeight) {
        for (int x = 0; x < img.width; x += blockWidth) {
            // Get average color for this block
            Color avgColor = getAverageColor(img, x, y, blockWidth, blockHeight);
            
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
    float aspectRatio = static_cast<float>(img.height) / static_cast<float>(img.width);
    int targetHeight = static_cast<int>(targetWidth * aspectRatio * 0.5f); // 0.5 for character aspect
    
    ImageProcessor processor;
    auto resized = processor.resize(img, targetWidth, targetHeight * 2); // *2 because we sample every 2 rows
    
    if (!resized) {
        return "";
    }
    
    return convertToAscii(*resized, useColor);
}

} // namespace ascii_art
