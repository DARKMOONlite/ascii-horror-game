#ifndef ASCII_IMAGE_H
#define ASCII_IMAGE_H

#include <string>
#include <vector>
#include "TerminalUtils.h"

namespace ASCIIDisplay {

// Represents an ASCII art image converted from pixel data
class ASCIIImage {
public:
    // Constructor
    ASCIIImage();
    ASCIIImage(int width, int height);
    
    // Load from raw RGB data (simplified interface)
    // data format: width * height * 3 (RGB values 0-255)
    void loadFromRGB(const std::vector<unsigned char>& data, int width, int height);
    
    // Load from grayscale data
    // data format: width * height (grayscale values 0-255)
    void loadFromGrayscale(const std::vector<unsigned char>& data, int width, int height);
    
    // Create from text pattern
    void loadFromText(const std::vector<std::string>& lines);
    
    // Set a pixel/character at position
    void setPixel(int row, int col, char ch, Color color = Color::WHITE);
    
    // Get character at position
    char getChar(int row, int col) const;
    
    // Get color at position
    Color getColor(int row, int col) const;
    
    // Resize image (simple nearest neighbor)
    void resize(int newWidth, int newHeight);
    
    // Render to a panel at specified position
    void renderToPanel(class Panel& panel, int row = 0, int col = 0) const;
    
    // Get dimensions
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    
    // Clear image
    void clear();

private:
    int width_, height_;
    
    struct Pixel {
        char ch = ' ';
        Color color = Color::WHITE;
    };
    std::vector<std::vector<Pixel>> pixels_;
    
    void initPixels();
};

} // namespace ASCIIDisplay

#endif // ASCII_IMAGE_H
