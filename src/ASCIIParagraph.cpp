#include "ASCIIParagraph.h"
#include <algorithm>
#include <sstream>
#include <cmath>

namespace ASCIIDisplay {

ASCIIParagraph::ASCIIParagraph(const std::string& text, int scale)
    : text_(text), scale_(scale), color_(Color::WHITE), 
      effect_(TextEffect::NONE), wordSpacing_(2), lineSpacing_(1),
      letterSpacing_(1), maxWidth_(80), alignment_(TextAlign::LEFT),
      animationTime_(0.0) {
    updateWords();
}

void ASCIIParagraph::setText(const std::string& text) {
    if (text_ != text) {
        text_ = text;
        updateWords();
    }
}

void ASCIIParagraph::setScale(int scale) {
    if (scale_ != scale) {
        scale_ = scale;
        for (auto& word : words_) {
            word->setScale(scale);
        }
    }
}

void ASCIIParagraph::setColor(Color color) {
    color_ = color;
    for (auto& word : words_) {
        word->setColor(color);
    }
}

void ASCIIParagraph::setEffect(TextEffect effect) {
    effect_ = effect;
    for (auto& word : words_) {
        word->setEffect(effect);
    }
}

void ASCIIParagraph::setWordSpacing(int spacing) {
    if (spacing < 0) spacing = 0;
    wordSpacing_ = spacing;
}

void ASCIIParagraph::setLineSpacing(int spacing) {
    if (spacing < 0) spacing = 0;
    lineSpacing_ = spacing;
}

void ASCIIParagraph::setLetterSpacing(int spacing) {
    if (spacing < 0) spacing = 0;
    letterSpacing_ = spacing;
    for (auto& word : words_) {
        word->setLetterSpacing(spacing);
    }
}

void ASCIIParagraph::setMaxWidth(int width) {
    if (width > 0) {
        maxWidth_ = width;
    }
}

void ASCIIParagraph::setAlignment(TextAlign align) {
    alignment_ = align;
}

bool ASCIIParagraph::loadFont(const std::string& fontPath) {
    fontPath_ = fontPath;
    bool success = true;
    for (auto& word : words_) {
        success &= word->loadFont(fontPath);
    }
    return success;
}

int ASCIIParagraph::getWidth() const {
    const auto& lines = layoutWords();
    
    int maxWidth = 0;
    for (const auto& line : lines) {
        int lineWidth = 0;
        for (size_t i = 0; i < line.size(); ++i) {
            lineWidth += line[i]->getWidth();
            if (i < line.size() - 1) {
                lineWidth += wordSpacing_;
            }
        }
        maxWidth = std::max(maxWidth, lineWidth);
    }
    
    return maxWidth;
}

int ASCIIParagraph::getHeight() const {
    const auto& lines = layoutWords();
    
    if (lines.empty()) return 0;
    
    int totalHeight = 0;
    for (const auto& line : lines) {
        int lineHeight = 0;
        for (const auto& word : line) {
            lineHeight = std::max(lineHeight, word->getHeight());
        }
        totalHeight += lineHeight + lineSpacing_;
    }
    
    // Remove last line spacing
    if (totalHeight > 0) {
        totalHeight -= lineSpacing_;
    }
    
    return totalHeight;
}

std::shared_ptr<ASCIIWord> ASCIIParagraph::getWord(size_t index) {
    if (index < words_.size()) {
        return words_[index];
    }
    return nullptr;
}

void ASCIIParagraph::renderToPanel(Panel& panel, int row, int col) {
    const auto& lines = renderLines();
    
    for (size_t i = 0; i < lines.size() && (row + i) < panel.getContentHeight(); ++i) {
        panel.writeText(row + i, col, lines[i], color_);
    }
}

std::vector<std::string> ASCIIParagraph::renderLines() const {
    std::vector<std::string> result;
    const auto& wordLines = layoutWords();
    
    if (wordLines.empty()) {
        return result;
    }
    
    for (const auto& line : wordLines) {
        if (line.empty()) continue;
        
        // Get the maximum height for this line
        int lineHeight = 0;
        for (const auto& word : line) {
            lineHeight = std::max(lineHeight, word->getHeight());
        }
        
        // Calculate line width
        int lineWidth = 0;
        for (size_t i = 0; i < line.size(); ++i) {
            lineWidth += line[i]->getWidth();
            if (i < line.size() - 1) {
                lineWidth += wordSpacing_;
            }
        }
        
        // Calculate starting position based on alignment
        int startCol = 0;
        if (alignment_ == TextAlign::CENTER) {
            startCol = (maxWidth_ - lineWidth) / 2;
        } else if (alignment_ == TextAlign::RIGHT) {
            startCol = maxWidth_ - lineWidth;
        }
        
        if (startCol < 0) startCol = 0;
        
        // Create a buffer for this line
        std::vector<std::string> lineBuffer(lineHeight, std::string(maxWidth_, ' '));
        
        int currentCol = startCol;
        for (const auto& word : line) {
            const auto& wordRendered = word->renderLines();
            
            for (size_t r = 0; r < wordRendered.size() && r < lineBuffer.size(); ++r) {
                const std::string& wordLine = wordRendered[r];
                for (size_t c = 0; c < wordLine.length() && (currentCol + c) < lineBuffer[r].length(); ++c) {
                    lineBuffer[r][currentCol + c] = wordLine[c];
                }
            }
            
            currentCol += word->getWidth() + wordSpacing_;
        }
        
        // Add line buffer to result
        for (const auto& bufferLine : lineBuffer) {
            result.push_back(bufferLine);
        }
        
        // Add line spacing
        for (int i = 0; i < lineSpacing_; ++i) {
            result.push_back(std::string(maxWidth_, ' '));
        }
    }
    
    // Remove trailing line spacing
    while (!result.empty() && result.back().find_first_not_of(' ') == std::string::npos) {
        result.pop_back();
    }
    
    return result;
}

void ASCIIParagraph::updateAnimation(double deltaTime) {
    animationTime_ += deltaTime;
    
    // Apply animation effects
    if ((effect_ & TextEffect::WAVE) != 0) {
        // Wave effect implementation (varies color or position based on time)
        for (size_t i = 0; i < words_.size(); ++i) {
            // Could vary properties of each word based on time and position
            // This is a placeholder for more complex wave animations
        }
    }
    
    if ((effect_ & TextEffect::SHAKE) != 0) {
        // Shake effect implementation
        // Could vary position randomly
    }
    
    if ((effect_ & TextEffect::BLINK) != 0) {
        // Blink effect - could toggle visibility
        bool visible = (static_cast<int>(animationTime_ * 2) % 2) == 0;
        // Apply visibility (would need additional state management)
    }
}

void ASCIIParagraph::updateWords() {
    words_.clear();
    
    // Split text into words
    std::istringstream iss(text_);
    std::string wordText;
    
    while (iss >> wordText) {
        auto word = std::make_shared<ASCIIWord>(wordText, scale_);
        word->setColor(color_);
        word->setEffect(effect_);
        word->setLetterSpacing(letterSpacing_);
        
        if (!fontPath_.empty()) {
            word->loadFont(fontPath_);
        }
        
        words_.push_back(word);
    }
}

std::vector<std::vector<std::shared_ptr<ASCIIWord>>> ASCIIParagraph::layoutWords() const {
    std::vector<std::vector<std::shared_ptr<ASCIIWord>>> lines;
    
    if (words_.empty()) {
        return lines;
    }
    
    std::vector<std::shared_ptr<ASCIIWord>> currentLine;
    int currentLineWidth = 0;
    
    for (const auto& word : words_) {
        int wordWidth = word->getWidth();
        int spaceNeeded = currentLine.empty() ? 0 : wordSpacing_;
        
        if (currentLineWidth + spaceNeeded + wordWidth <= maxWidth_ || currentLine.empty()) {
            currentLine.push_back(word);
            currentLineWidth += spaceNeeded + wordWidth;
        } else {
            // Start new line
            lines.push_back(currentLine);
            currentLine.clear();
            currentLine.push_back(word);
            currentLineWidth = wordWidth;
        }
    }
    
    // Add the last line
    if (!currentLine.empty()) {
        lines.push_back(currentLine);
    }
    
    return lines;
}

} // namespace ASCIIDisplay
