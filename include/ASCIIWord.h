#ifndef ASCII_WORD_H
#define ASCII_WORD_H

#include <string>
#include <vector>
#include <memory>
#include "ASCIILetter.h"
#include "TerminalUtils.h"

namespace ASCIIDisplay {

// Represents a word made of multiple ASCII letters
class ASCIIWord {
public:
    // Constructor
    ASCIIWord(const std::string& text = "", int scale = 3);
    
    // Set the word text
    void setText(const std::string& text);
    
    // Get the word text
    std::string getText() const { return text_; }
    
    // Set scale for all letters
    void setScale(int scale);
    
    // Get current scale
    int getScale() const { return scale_; }
    
    // Set color for all letters
    void setColor(Color color);
    
    // Get color
    Color getColor() const { return color_; }
    
    // Set text effect for all letters
    void setEffect(TextEffect effect);
    
    // Get current effect
    TextEffect getEffect() const { return effect_; }
    
    // Set letter spacing (pixels between letters)
    void setLetterSpacing(int spacing);
    
    // Get letter spacing
    int getLetterSpacing() const { return letterSpacing_; }
    
    // Load custom font for all letters
    bool loadFont(const std::string& fontPath);
    
    // Get dimensions
    int getWidth() const;
    int getHeight() const;
    
    // Get individual letter
    std::shared_ptr<ASCIILetter> getLetter(size_t index);
    
    // Get number of letters
    size_t getLetterCount() const { return letters_.size(); }
    
    // Render to a buffer (row-major order)
    void renderToBuffer(std::vector<std::vector<char>>& buffer, int startRow, int startCol) const;
    
    // Render all letters
    std::vector<std::string> renderLines() const;
    
private:
    std::string text_;
    std::vector<std::shared_ptr<ASCIILetter>> letters_;
    int scale_;
    Color color_;
    TextEffect effect_;
    int letterSpacing_;
    std::string fontPath_;
    
    // Update letters array from text
    void updateLetters();
};

} // namespace ASCIIDisplay

#endif // ASCII_WORD_H
