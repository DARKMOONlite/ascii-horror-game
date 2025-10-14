#ifndef ASCII_LETTER_H
#define ASCII_LETTER_H

#include <string>
#include <vector>
#include <memory>
#include "TerminalUtils.h"

namespace ASCIIDisplay {

// Text effects for ASCII letters
enum class TextEffect {
    NONE = 0,
    BOLD = 1,
    ITALIC = 2,
    UNDERLINE = 4,
    BLINK = 8,
    WAVE = 16,
    SHAKE = 32
};

// Combine effects using bitwise OR
inline TextEffect operator|(TextEffect a, TextEffect b) {
    return static_cast<TextEffect>(static_cast<int>(a) | static_cast<int>(b));
}

inline int operator&(TextEffect a, TextEffect b) {
    return static_cast<int>(a) & static_cast<int>(b);
}

// Represents a single large ASCII character made of multiple terminal characters
class ASCIILetter {
public:
    // Constructor
    ASCIILetter(char letter = ' ', int scale = 3);
    
    // Set the character to display
    void setChar(char letter);
    
    // Get the character
    char getChar() const { return letter_; }
    
    // Set scale (size multiplier)
    void setScale(int scale);
    
    // Get current scale
    int getScale() const { return scale_; }
    
    // Set color
    void setColor(Color color);
    
    // Get color
    Color getColor() const { return color_; }
    
    // Set text effects
    void setEffect(TextEffect effect);
    
    // Get current effect
    TextEffect getEffect() const { return effect_; }
    
    // Get dimensions
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    
    // Load custom font from TTF file
    bool loadFont(const std::string& fontPath);
    
    // Get the rendered character data
    const std::vector<std::string>& getRenderedLines() const { return lines_; }
    
    // Render to a buffer (row-major order)
    void renderToBuffer(std::vector<std::vector<char>>& buffer, int startRow, int startCol) const;
    
private:
    char letter_;
    int scale_;
    Color color_;
    TextEffect effect_;
    int width_;
    int height_;
    std::vector<std::string> lines_;
    std::string fontPath_;
    
    // Generate ASCII art for the character
    void generateASCII();
    
    // Apply effects to rendered lines
    void applyEffects();
    
    // Built-in 5x5 font data (simple bitmap font)
    static const char* getFontData(char c);
};

} // namespace ASCIIDisplay

#endif // ASCII_LETTER_H
