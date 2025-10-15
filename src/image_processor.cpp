#include "image_processor.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

#include <algorithm>
#include <cmath>

namespace ascii_art {

Color Image::getPixel(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return Color(0, 0, 0);
    }
    
    int index = (y * width + x) * channels;
    if (channels >= 3) {
        return Color(data[index], data[index + 1], data[index + 2]);
    } else if (channels == 1) {
        unsigned char gray = data[index];
        return Color(gray, gray, gray);
    }
    return Color(0, 0, 0);
}

std::unique_ptr<Image> ImageProcessor::loadImage(const std::string& filename) {
    auto img = std::make_unique<Image>();
    
    unsigned char* imageData = stbi_load(filename.c_str(), &img->width, &img->height, &img->channels, 0);
    
    if (!imageData) {
        return nullptr;
    }
    
    // Copy data to vector
    size_t dataSize = img->width * img->height * img->channels;
    img->data.resize(dataSize);
    std::copy(imageData, imageData + dataSize, img->data.begin());
    
    stbi_image_free(imageData);
    
    return img;
}

float ImageProcessor::applyKernelAtPosition(const Image& img, int x, int y, int channel,
                                            const std::vector<float>& kernel, int kernelSize) {
    float sum = 0.0f;
    int halfSize = kernelSize / 2;
    
    for (int ky = 0; ky < kernelSize; ++ky) {
        for (int kx = 0; kx < kernelSize; ++kx) {
            int px = x + kx - halfSize;
            int py = y + ky - halfSize;
            
            // Clamp to image boundaries
            px = std::max(0, std::min(img.width - 1, px));
            py = std::max(0, std::min(img.height - 1, py));
            
            int pixelIndex = (py * img.width + px) * img.channels + channel;
            int kernelIndex = ky * kernelSize + kx;
            
            sum += img.data[pixelIndex] * kernel[kernelIndex];
        }
    }
    
    return sum;
}

std::unique_ptr<Image> ImageProcessor::applyKernel(const Image& img, 
                                                   const std::vector<float>& kernel, 
                                                   int kernelSize) {
    if (kernelSize * kernelSize != static_cast<int>(kernel.size())) {
        return nullptr;
    }
    
    auto result = std::make_unique<Image>();
    result->width = img.width;
    result->height = img.height;
    result->channels = img.channels;
    result->data.resize(img.data.size());
    
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            for (int c = 0; c < img.channels; ++c) {
                float value = applyKernelAtPosition(img, x, y, c, kernel, kernelSize);
                
                // Clamp to [0, 255]
                value = std::max(0.0f, std::min(255.0f, value));
                
                int index = (y * img.width + x) * img.channels + c;
                result->data[index] = static_cast<unsigned char>(value);
            }
        }
    }
    
    return result;
}

std::unique_ptr<Image> ImageProcessor::resize(const Image& img, int newWidth, int newHeight) {
    auto result = std::make_unique<Image>();
    result->width = newWidth;
    result->height = newHeight;
    result->channels = img.channels;
    result->data.resize(newWidth * newHeight * img.channels);
    
    float xRatio = static_cast<float>(img.width) / newWidth;
    float yRatio = static_cast<float>(img.height) / newHeight;
    
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // Simple nearest neighbor sampling
            int srcX = static_cast<int>(x * xRatio);
            int srcY = static_cast<int>(y * yRatio);
            
            srcX = std::max(0, std::min(img.width - 1, srcX));
            srcY = std::max(0, std::min(img.height - 1, srcY));
            
            for (int c = 0; c < img.channels; ++c) {
                int srcIndex = (srcY * img.width + srcX) * img.channels + c;
                int dstIndex = (y * newWidth + x) * img.channels + c;
                result->data[dstIndex] = img.data[srcIndex];
            }
        }
    }
    
    return result;
}

} // namespace ascii_art
