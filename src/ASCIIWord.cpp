#include "ASCIIWord.h"
#include <algorithm>

namespace ASCIIDisplay {

ASCIIWord::ASCIIWord(const std::string& text, int scale)
    : text_(text), scale_(scale), color_(Color::WHITE), 
      effect_(TextEffect::NONE), letterSpacing_(1) {
    updateLetters();
}

void ASCIIWord::setText(const std::string& text) {
    if (text_ != text) {
        text_ = text;
        updateLetters();
    }
}

void ASCIIWord::setScale(int scale) {
    if (scale_ != scale) {
        scale_ = scale;
        for (auto& letter : letters_) {
            letter->setScale(scale);
        }
    }
}

void ASCIIWord::setColor(Color color) {
    color_ = color;
    for (auto& letter : letters_) {
        letter->setColor(color);
    }
}

void ASCIIWord::setEffect(TextEffect effect) {
    effect_ = effect;
    for (auto& letter : letters_) {
        letter->setEffect(effect);
    }
}

void ASCIIWord::setLetterSpacing(int spacing) {
    if (spacing < 0) spacing = 0;
    letterSpacing_ = spacing;
}

bool ASCIIWord::loadFont(const std::string& fontPath) {
    fontPath_ = fontPath;
    bool success = true;
    for (auto& letter : letters_) {
        success &= letter->loadFont(fontPath);
    }
    return success;
}

int ASCIIWord::getWidth() const {
    if (letters_.empty()) return 0;
    
    int width = 0;
    for (size_t i = 0; i < letters_.size(); ++i) {
        width += letters_[i]->getWidth();
        if (i < letters_.size() - 1) {
            width += letterSpacing_;
        }
    }
    return width;
}

int ASCIIWord::getHeight() const {
    if (letters_.empty()) return 0;
    
    int maxHeight = 0;
    for (const auto& letter : letters_) {
        maxHeight = std::max(maxHeight, letter->getHeight());
    }
    return maxHeight;
}

std::shared_ptr<ASCIILetter> ASCIIWord::getLetter(size_t index) {
    if (index < letters_.size()) {
        return letters_[index];
    }
    return nullptr;
}

void ASCIIWord::renderToBuffer(std::vector<std::vector<char>>& buffer, 
                                int startRow, int startCol) const {
    int currentCol = startCol;
    
    for (const auto& letter : letters_) {
        letter->renderToBuffer(buffer, startRow, currentCol);
        currentCol += letter->getWidth() + letterSpacing_;
    }
}

std::vector<std::string> ASCIIWord::renderLines() const {
    std::vector<std::string> result;
    
    if (letters_.empty()) {
        return result;
    }
    
    int height = getHeight();
    int width = getWidth();
    
    // Initialize result with empty lines
    result.resize(height, std::string(width, ' '));
    
    int currentCol = 0;
    for (const auto& letter : letters_) {
        const auto& letterLines = letter->getRenderedLines();
        
        for (size_t row = 0; row < letterLines.size() && row < result.size(); ++row) {
            const std::string& line = letterLines[row];
            for (size_t col = 0; col < line.length() && (currentCol + col) < result[row].length(); ++col) {
                result[row][currentCol + col] = line[col];
            }
        }
        
        currentCol += letter->getWidth() + letterSpacing_;
    }
    
    return result;
}

void ASCIIWord::updateLetters() {
    letters_.clear();
    
    for (char c : text_) {
        auto letter = std::make_shared<ASCIILetter>(c, scale_);
        letter->setColor(color_);
        letter->setEffect(effect_);
        if (!fontPath_.empty()) {
            letter->loadFont(fontPath_);
        }
        letters_.push_back(letter);
    }
}

} // namespace ASCIIDisplay
