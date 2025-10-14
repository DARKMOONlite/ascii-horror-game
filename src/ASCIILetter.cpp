#include "ASCIILetter.h"
#include <algorithm>
#include <cmath>

namespace ASCIIDisplay {

// Simple 5x5 bitmap font for basic ASCII characters
const char* ASCIILetter::getFontData(char c) {
    // Convert to uppercase for simplicity
    c = toupper(c);
    
    // Return 5x5 bitmap patterns (1 = filled, 0 = empty)
    switch (c) {
        case 'A': return "01110"
                         "10001"
                         "11111"
                         "10001"
                         "10001";
        case 'B': return "11110"
                         "10001"
                         "11110"
                         "10001"
                         "11110";
        case 'C': return "01110"
                         "10001"
                         "10000"
                         "10001"
                         "01110";
        case 'D': return "11110"
                         "10001"
                         "10001"
                         "10001"
                         "11110";
        case 'E': return "11111"
                         "10000"
                         "11110"
                         "10000"
                         "11111";
        case 'F': return "11111"
                         "10000"
                         "11110"
                         "10000"
                         "10000";
        case 'G': return "01110"
                         "10001"
                         "10011"
                         "10001"
                         "01110";
        case 'H': return "10001"
                         "10001"
                         "11111"
                         "10001"
                         "10001";
        case 'I': return "11111"
                         "00100"
                         "00100"
                         "00100"
                         "11111";
        case 'J': return "11111"
                         "00010"
                         "00010"
                         "10010"
                         "01100";
        case 'K': return "10001"
                         "10010"
                         "11100"
                         "10010"
                         "10001";
        case 'L': return "10000"
                         "10000"
                         "10000"
                         "10000"
                         "11111";
        case 'M': return "10001"
                         "11011"
                         "10101"
                         "10001"
                         "10001";
        case 'N': return "10001"
                         "11001"
                         "10101"
                         "10011"
                         "10001";
        case 'O': return "01110"
                         "10001"
                         "10001"
                         "10001"
                         "01110";
        case 'P': return "11110"
                         "10001"
                         "11110"
                         "10000"
                         "10000";
        case 'Q': return "01110"
                         "10001"
                         "10001"
                         "10101"
                         "01111";
        case 'R': return "11110"
                         "10001"
                         "11110"
                         "10010"
                         "10001";
        case 'S': return "01111"
                         "10000"
                         "01110"
                         "00001"
                         "11110";
        case 'T': return "11111"
                         "00100"
                         "00100"
                         "00100"
                         "00100";
        case 'U': return "10001"
                         "10001"
                         "10001"
                         "10001"
                         "01110";
        case 'V': return "10001"
                         "10001"
                         "10001"
                         "01010"
                         "00100";
        case 'W': return "10001"
                         "10001"
                         "10101"
                         "11011"
                         "10001";
        case 'X': return "10001"
                         "01010"
                         "00100"
                         "01010"
                         "10001";
        case 'Y': return "10001"
                         "01010"
                         "00100"
                         "00100"
                         "00100";
        case 'Z': return "11111"
                         "00010"
                         "00100"
                         "01000"
                         "11111";
        case '0': return "01110"
                         "10011"
                         "10101"
                         "11001"
                         "01110";
        case '1': return "00100"
                         "01100"
                         "00100"
                         "00100"
                         "01110";
        case '2': return "01110"
                         "10001"
                         "00010"
                         "01000"
                         "11111";
        case '3': return "11110"
                         "00001"
                         "01110"
                         "00001"
                         "11110";
        case '4': return "10010"
                         "10010"
                         "11111"
                         "00010"
                         "00010";
        case '5': return "11111"
                         "10000"
                         "11110"
                         "00001"
                         "11110";
        case '6': return "01110"
                         "10000"
                         "11110"
                         "10001"
                         "01110";
        case '7': return "11111"
                         "00010"
                         "00100"
                         "01000"
                         "10000";
        case '8': return "01110"
                         "10001"
                         "01110"
                         "10001"
                         "01110";
        case '9': return "01110"
                         "10001"
                         "01111"
                         "00001"
                         "01110";
        case '!': return "00100"
                         "00100"
                         "00100"
                         "00000"
                         "00100";
        case '?': return "01110"
                         "10001"
                         "00010"
                         "00000"
                         "00100";
        case '.': return "00000"
                         "00000"
                         "00000"
                         "00000"
                         "00100";
        case ',': return "00000"
                         "00000"
                         "00000"
                         "00100"
                         "01000";
        case '\'': return "00100"
                          "00100"
                          "00000"
                          "00000"
                          "00000";
        case '"': return "01010"
                         "01010"
                         "00000"
                         "00000"
                         "00000";
        case '-': return "00000"
                         "00000"
                         "11111"
                         "00000"
                         "00000";
        case '+': return "00000"
                         "00100"
                         "01110"
                         "00100"
                         "00000";
        case ' ': return "00000"
                         "00000"
                         "00000"
                         "00000"
                         "00000";
        default:  return "11111"
                         "10001"
                         "10001"
                         "10001"
                         "11111"; // Default box for unknown chars
    }
}

ASCIILetter::ASCIILetter(char letter, int scale)
    : letter_(letter), scale_(scale), color_(Color::WHITE), 
      effect_(TextEffect::NONE), width_(5), height_(5) {
    generateASCII();
}

void ASCIILetter::setChar(char letter) {
    if (letter_ != letter) {
        letter_ = letter;
        generateASCII();
    }
}

void ASCIILetter::setScale(int scale) {
    if (scale < 1) scale = 1;
    if (scale_ != scale) {
        scale_ = scale;
        generateASCII();
    }
}

void ASCIILetter::setColor(Color color) {
    color_ = color;
}

void ASCIILetter::setEffect(TextEffect effect) {
    if (effect_ != effect) {
        effect_ = effect;
        applyEffects();
    }
}

bool ASCIILetter::loadFont(const std::string& fontPath) {
    // For now, TTF support is a placeholder
    // In a full implementation, this would use FreeType library
    fontPath_ = fontPath;
    // TODO: Implement TTF loading with FreeType
    return false; // Not implemented yet
}

void ASCIILetter::generateASCII() {
    const char* bitmap = getFontData(letter_);
    lines_.clear();
    
    // Calculate actual dimensions based on scale
    width_ = 5 * scale_;
    height_ = 5 * scale_;
    
    // Generate scaled ASCII art
    for (int row = 0; row < 5; ++row) {
        std::string scaledLine = "";
        for (int col = 0; col < 5; ++col) {
            char pixel = bitmap[row * 5 + col];
            char asciiChar = (pixel == '1') ? '#' : ' ';
            
            // Apply scale horizontally
            for (int s = 0; s < scale_; ++s) {
                scaledLine += asciiChar;
            }
        }
        
        // Apply scale vertically
        for (int s = 0; s < scale_; ++s) {
            lines_.push_back(scaledLine);
        }
    }
    
    applyEffects();
}

void ASCIILetter::applyEffects() {
    if (effect_ == TextEffect::NONE) {
        return;
    }
    
    std::vector<std::string> effectLines = lines_;
    
    // Apply bold effect (make characters denser)
    if ((effect_ & TextEffect::BOLD) != 0) {
        for (auto& line : effectLines) {
            for (size_t i = 0; i < line.length(); ++i) {
                if (line[i] == '#') {
                    line[i] = '@'; // Use a denser character
                }
            }
        }
    }
    
    // Apply italic effect (skew to the right)
    if ((effect_ & TextEffect::ITALIC) != 0) {
        for (size_t i = 0; i < effectLines.size(); ++i) {
            int skew = (effectLines.size() - i - 1) / 3; // Skew based on row
            effectLines[i] = std::string(skew, ' ') + effectLines[i];
        }
    }
    
    lines_ = effectLines;
}

void ASCIILetter::renderToBuffer(std::vector<std::vector<char>>& buffer, 
                                  int startRow, int startCol) const {
    for (size_t r = 0; r < lines_.size() && (startRow + r) < buffer.size(); ++r) {
        const std::string& line = lines_[r];
        for (size_t c = 0; c < line.length() && (startCol + c) < buffer[startRow + r].size(); ++c) {
            buffer[startRow + r][startCol + c] = line[c];
        }
    }
}

} // namespace ASCIIDisplay
