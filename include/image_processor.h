#pragma once

#include <vector>
#include <string>
#include <memory>

namespace ascii_art {

struct Color {
    unsigned char r, g, b;
    
    Color() : r(0), g(0), b(0) {}
    Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}
};

struct Image {
    int width;
    int height;
    int channels;
    std::vector<unsigned char> data;
    
    Color getPixel(int x, int y) const;
};

class ImageProcessor {
public:
    ImageProcessor() = default;
    ~ImageProcessor() = default;
    
    // Load image from file
    std::unique_ptr<Image> loadImage(const std::string& filename);
    
    // Apply kernel to image (for edge detection, blurring, etc.)
    std::unique_ptr<Image> applyKernel(const Image& img, const std::vector<float>& kernel, int kernelSize);
    
    // Resize image to fit terminal
    std::unique_ptr<Image> resize(const Image& img, int newWidth, int newHeight);
    
private:
    float applyKernelAtPosition(const Image& img, int x, int y, int channel, 
                               const std::vector<float>& kernel, int kernelSize);
};

} // namespace ascii_art
