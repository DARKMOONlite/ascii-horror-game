#ifndef ASCII_PARAGRAPH_H
#define ASCII_PARAGRAPH_H

#include <string>
#include <vector>
#include <memory>
#include "ASCIIWord.h"
#include "Panel.h"
#include "TerminalUtils.h"

namespace ASCIIDisplay {

// Text alignment options
enum class TextAlign {
    LEFT,
    CENTER,
    RIGHT,
    JUSTIFY
};

// Represents a paragraph made of multiple ASCII words
class ASCIIParagraph {
public:
    // Constructor
    ASCIIParagraph(const std::string& text = "", int scale = 3);
    
    // Set the paragraph text
    void setText(const std::string& text);
    
    // Get the paragraph text
    std::string getText() const { return text_; }
    
    // Set scale for all words
    void setScale(int scale);
    
    // Get current scale
    int getScale() const { return scale_; }
    
    // Set color for all words
    void setColor(Color color);
    
    // Get color
    Color getColor() const { return color_; }
    
    // Set text effect for all words
    void setEffect(TextEffect effect);
    
    // Get current effect
    TextEffect getEffect() const { return effect_; }
    
    // Set word spacing
    void setWordSpacing(int spacing);
    
    // Get word spacing
    int getWordSpacing() const { return wordSpacing_; }
    
    // Set line spacing
    void setLineSpacing(int spacing);
    
    // Get line spacing
    int getLineSpacing() const { return lineSpacing_; }
    
    // Set letter spacing for all words
    void setLetterSpacing(int spacing);
    
    // Get letter spacing
    int getLetterSpacing() const { return letterSpacing_; }
    
    // Set maximum width for text wrapping
    void setMaxWidth(int width);
    
    // Get maximum width
    int getMaxWidth() const { return maxWidth_; }
    
    // Set text alignment
    void setAlignment(TextAlign align);
    
    // Get text alignment
    TextAlign getAlignment() const { return alignment_; }
    
    // Load custom font for all words
    bool loadFont(const std::string& fontPath);
    
    // Get dimensions
    int getWidth() const;
    int getHeight() const;
    
    // Get individual word
    std::shared_ptr<ASCIIWord> getWord(size_t index);
    
    // Get number of words
    size_t getWordCount() const { return words_.size(); }
    
    // Render to panel
    void renderToPanel(Panel& panel, int row = 0, int col = 0);
    
    // Render all words
    std::vector<std::string> renderLines() const;
    
    // Animation update (for animated effects)
    void updateAnimation(double deltaTime);
    
private:
    std::string text_;
    std::vector<std::shared_ptr<ASCIIWord>> words_;
    int scale_;
    Color color_;
    TextEffect effect_;
    int wordSpacing_;
    int lineSpacing_;
    int letterSpacing_;
    int maxWidth_;
    TextAlign alignment_;
    std::string fontPath_;
    double animationTime_;
    
    // Update words array from text
    void updateWords();
    
    // Layout words into lines
    std::vector<std::vector<std::shared_ptr<ASCIIWord>>> layoutWords() const;
};

} // namespace ASCIIDisplay

#endif // ASCII_PARAGRAPH_H
