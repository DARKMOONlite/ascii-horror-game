#include "ASCIIImage.h"
#include "Panel.h"
#include <algorithm>

namespace ASCIIDisplay {

ASCIIImage::ASCIIImage() : width_(0), height_(0) {
}

ASCIIImage::ASCIIImage(int width, int height) : width_(width), height_(height) {
    initPixels();
}

void ASCIIImage::loadFromRGB(const std::vector<unsigned char>& data, int width, int height) {
    width_ = width;
    height_ = height;
    initPixels();
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = (y * width + x) * 3;
            if (idx + 2 < static_cast<int>(data.size())) {
                int r = data[idx];
                int g = data[idx + 1];
                int b = data[idx + 2];
                
                // Convert to brightness
                int brightness = static_cast<int>(0.299 * r + 0.587 * g + 0.114 * b);
                
                pixels_[y][x].ch = TerminalUtils::brightnessToChar(brightness);
                pixels_[y][x].color = TerminalUtils::rgbToColor(r, g, b);
            }
        }
    }
}

void ASCIIImage::loadFromGrayscale(const std::vector<unsigned char>& data, int width, int height) {
    width_ = width;
    height_ = height;
    initPixels();
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = y * width + x;
            if (idx < static_cast<int>(data.size())) {
                int brightness = data[idx];
                pixels_[y][x].ch = TerminalUtils::brightnessToChar(brightness);
                
                // Set color based on brightness
                if (brightness < 64) pixels_[y][x].color = Color::BLACK;
                else if (brightness < 128) pixels_[y][x].color = Color::BRIGHT_BLACK;
                else if (brightness < 192) pixels_[y][x].color = Color::WHITE;
                else pixels_[y][x].color = Color::BRIGHT_WHITE;
            }
        }
    }
}

void ASCIIImage::loadFromText(const std::vector<std::string>& lines) {
    if (lines.empty()) return;
    
    height_ = lines.size();
    width_ = 0;
    for (const auto& line : lines) {
        width_ = std::max(width_, static_cast<int>(line.length()));
    }
    
    initPixels();
    
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < static_cast<int>(lines[y].length()); ++x) {
            pixels_[y][x].ch = lines[y][x];
            pixels_[y][x].color = Color::WHITE;
        }
    }
}

void ASCIIImage::setPixel(int row, int col, char ch, Color color) {
    if (row >= 0 && row < height_ && col >= 0 && col < width_) {
        pixels_[row][col].ch = ch;
        pixels_[row][col].color = color;
    }
}

char ASCIIImage::getChar(int row, int col) const {
    if (row >= 0 && row < height_ && col >= 0 && col < width_) {
        return pixels_[row][col].ch;
    }
    return ' ';
}

Color ASCIIImage::getColor(int row, int col) const {
    if (row >= 0 && row < height_ && col >= 0 && col < width_) {
        return pixels_[row][col].color;
    }
    return Color::WHITE;
}

void ASCIIImage::resize(int newWidth, int newHeight) {
    if (newWidth <= 0 || newHeight <= 0) return;
    
    std::vector<std::vector<Pixel>> newPixels(newHeight, std::vector<Pixel>(newWidth));
    
    // Simple nearest neighbor sampling
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            int srcY = (y * height_) / newHeight;
            int srcX = (x * width_) / newWidth;
            
            if (srcY < height_ && srcX < width_) {
                newPixels[y][x] = pixels_[srcY][srcX];
            }
        }
    }
    
    width_ = newWidth;
    height_ = newHeight;
    pixels_ = std::move(newPixels);
}

void ASCIIImage::renderToPanel(Panel& panel, int row, int col) const {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            panel.setChar(row + y, col + x, pixels_[y][x].ch, pixels_[y][x].color);
        }
    }
}

void ASCIIImage::clear() {
    for (auto& row : pixels_) {
        for (auto& pixel : row) {
            pixel.ch = ' ';
            pixel.color = Color::WHITE;
        }
    }
}

void ASCIIImage::initPixels() {
    pixels_.clear();
    pixels_.resize(height_, std::vector<Pixel>(width_));
}

} // namespace ASCIIDisplay
