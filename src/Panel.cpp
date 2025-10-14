#include "Panel.h"
#include <iostream>
#include <algorithm>

namespace ASCIIDisplay {

Panel::Panel(int x, int y, int width, int height, const std::string& title)
    : x_(x), y_(y), width_(width), height_(height), title_(title), 
      border_(true), borderColor_(Color::WHITE) {
    initContent();
}

void Panel::setPosition(int x, int y) {
    x_ = x;
    y_ = y;
}

void Panel::setSize(int width, int height) {
    width_ = width;
    height_ = height;
    initContent();
}

void Panel::setTitle(const std::string& title) {
    title_ = title;
}

void Panel::setBorder(bool enabled) {
    border_ = enabled;
}

void Panel::setBorderColor(Color color) {
    borderColor_ = color;
}

void Panel::clear() {
    for (auto& row : content_) {
        for (auto& cell : row) {
            cell.ch = ' ';
            cell.color = Color::WHITE;
        }
    }
}

void Panel::writeText(int row, int col, const std::string& text, Color fg) {
    int contentHeight = getContentHeight();
    int contentWidth = getContentWidth();
    
    if (row < 0 || row >= contentHeight) return;
    
    for (size_t i = 0; i < text.length() && (col + static_cast<int>(i)) < contentWidth; ++i) {
        if (col + static_cast<int>(i) >= 0) {
            content_[row][col + i].ch = text[i];
            content_[row][col + i].color = fg;
        }
    }
}

void Panel::setChar(int row, int col, char ch, Color fg) {
    int contentHeight = getContentHeight();
    int contentWidth = getContentWidth();
    
    if (row >= 0 && row < contentHeight && col >= 0 && col < contentWidth) {
        content_[row][col].ch = ch;
        content_[row][col].color = fg;
    }
}

void Panel::fill(char ch, Color fg) {
    for (auto& row : content_) {
        for (auto& cell : row) {
            cell.ch = ch;
            cell.color = fg;
        }
    }
}

void Panel::drawLine(int row, int col, int length, char ch, bool horizontal) {
    if (horizontal) {
        for (int i = 0; i < length; ++i) {
            setChar(row, col + i, ch);
        }
    } else {
        for (int i = 0; i < length; ++i) {
            setChar(row + i, col, ch);
        }
    }
}

void Panel::drawBox(int row, int col, int width, int height, char ch) {
    // Draw top and bottom
    for (int i = 0; i < width; ++i) {
        setChar(row, col + i, ch);
        setChar(row + height - 1, col + i, ch);
    }
    
    // Draw sides
    for (int i = 0; i < height; ++i) {
        setChar(row + i, col, ch);
        setChar(row + i, col + width - 1, ch);
    }
}

void Panel::render() const {
    // Draw border if enabled
    if (border_) {
        TerminalUtils::setColor(borderColor_);
        
        // Draw corners and edges
        TerminalUtils::moveCursor(y_, x_);
        std::cout << "┌";
        for (int i = 0; i < width_ - 2; ++i) std::cout << "─";
        std::cout << "┐";
        
        for (int i = 1; i < height_ - 1; ++i) {
            TerminalUtils::moveCursor(y_ + i, x_);
            std::cout << "│";
            TerminalUtils::moveCursor(y_ + i, x_ + width_ - 1);
            std::cout << "│";
        }
        
        TerminalUtils::moveCursor(y_ + height_ - 1, x_);
        std::cout << "└";
        for (int i = 0; i < width_ - 2; ++i) std::cout << "─";
        std::cout << "┘";
        
        // Draw title if present
        if (!title_.empty() && width_ > static_cast<int>(title_.length()) + 2) {
            TerminalUtils::moveCursor(y_, x_ + 2);
            std::cout << " " << title_ << " ";
        }
        
        TerminalUtils::resetFormat();
    }
    
    // Draw content
    int startRow = border_ ? 1 : 0;
    int startCol = border_ ? 1 : 0;
    int contentHeight = getContentHeight();
    int contentWidth = getContentWidth();
    
    for (int i = 0; i < contentHeight; ++i) {
        TerminalUtils::moveCursor(y_ + startRow + i, x_ + startCol);
        Color currentColor = Color::RESET;
        
        for (int j = 0; j < contentWidth; ++j) {
            if (content_[i][j].color != currentColor) {
                TerminalUtils::setColor(content_[i][j].color);
                currentColor = content_[i][j].color;
            }
            std::cout << content_[i][j].ch;
        }
        
        if (currentColor != Color::RESET) {
            TerminalUtils::resetFormat();
        }
    }
    
    std::cout.flush();
}

void Panel::initContent() {
    int contentHeight = border_ ? height_ - 2 : height_;
    int contentWidth = border_ ? width_ - 2 : width_;
    
    if (contentHeight < 0) contentHeight = 0;
    if (contentWidth < 0) contentWidth = 0;
    
    content_.clear();
    content_.resize(contentHeight, std::vector<Cell>(contentWidth));
}

} // namespace ASCIIDisplay
