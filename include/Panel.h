#ifndef PANEL_H
#define PANEL_H

#include <string>
#include <vector>
#include "TerminalUtils.h"

namespace ASCIIDisplay {

// Represents a rectangular panel on the terminal
class Panel {
public:
    // Constructor
    Panel(int x, int y, int width, int height, const std::string& title = "");
    
    // Set panel position
    void setPosition(int x, int y);
    
    // Set panel size
    void setSize(int width, int height);
    
    // Set panel title
    void setTitle(const std::string& title);
    
    // Set border visibility
    void setBorder(bool enabled);
    
    // Set border color
    void setBorderColor(Color color);
    
    // Clear panel content
    void clear();
    
    // Write text at position within panel (relative to panel's top-left corner)
    void writeText(int row, int col, const std::string& text, Color fg = Color::WHITE);
    
    // Set a character at position within panel
    void setChar(int row, int col, char ch, Color fg = Color::WHITE);
    
    // Fill panel with a character
    void fill(char ch, Color fg = Color::WHITE);
    
    // Draw a line within panel
    void drawLine(int row, int col, int length, char ch = '-', bool horizontal = true);
    
    // Draw a box within panel
    void drawBox(int row, int col, int width, int height, char ch = '#');
    
    // Render the panel to the terminal
    void render() const;
    
    // Get panel dimensions
    int getX() const { return x_; }
    int getY() const { return y_; }
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    int getContentWidth() const { return border_ ? width_ - 2 : width_; }
    int getContentHeight() const { return border_ ? height_ - 2 : height_; }

private:
    int x_, y_;           // Position on terminal
    int width_, height_;  // Size of panel
    std::string title_;   // Panel title
    bool border_;         // Whether to draw border
    Color borderColor_;   // Border color
    
    // Content buffer (row, col) - stores character and color
    struct Cell {
        char ch = ' ';
        Color color = Color::WHITE;
    };
    std::vector<std::vector<Cell>> content_;
    
    void initContent();
};

} // namespace ASCIIDisplay

#endif // PANEL_H
