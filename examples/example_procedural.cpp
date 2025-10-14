#include "PanelManager.h"
#include "Panel.h"
#include "ASCIIImage.h"
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <random>

using namespace ASCIIDisplay;

// Helper function to create a checkerboard pattern
ASCIIImage createCheckerboard(int width, int height, int squareSize) {
    std::vector<unsigned char> data(width * height);
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            bool isBlack = ((x / squareSize) + (y / squareSize)) % 2 == 0;
            data[y * width + x] = isBlack ? 0 : 255;
        }
    }
    
    ASCIIImage image;
    image.loadFromGrayscale(data, width, height);
    return image;
}

// Helper function to create a gradient pattern
ASCIIImage createGradient(int width, int height, bool horizontal) {
    std::vector<unsigned char> data(width * height);
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char brightness;
            if (horizontal) {
                brightness = static_cast<unsigned char>((x * 255) / (width - 1));
            } else {
                brightness = static_cast<unsigned char>((y * 255) / (height - 1));
            }
            data[y * width + x] = brightness;
        }
    }
    
    ASCIIImage image;
    image.loadFromGrayscale(data, width, height);
    return image;
}

// Helper function to create a circular pattern
ASCIIImage createCircle(int width, int height) {
    std::vector<unsigned char> data(width * height);
    
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;
    float radius = std::min(width, height) / 2.0f;
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float dx = x - centerX;
            float dy = y - centerY;
            float dist = std::sqrt(dx * dx + dy * dy);
            
            unsigned char brightness;
            if (dist <= radius) {
                brightness = static_cast<unsigned char>(255 * (1.0f - dist / radius));
            } else {
                brightness = 0;
            }
            data[y * width + x] = brightness;
        }
    }
    
    ASCIIImage image;
    image.loadFromGrayscale(data, width, height);
    return image;
}

// Helper function to create a wave pattern
ASCIIImage createWaves(int width, int height, float frequency) {
    std::vector<unsigned char> data(width * height);
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float value = std::sin(x * frequency) * std::cos(y * frequency);
            unsigned char brightness = static_cast<unsigned char>((value + 1.0f) * 127.5f);
            data[y * width + x] = brightness;
        }
    }
    
    ASCIIImage image;
    image.loadFromGrayscale(data, width, height);
    return image;
}

// Helper function to create random noise
ASCIIImage createNoise(int width, int height, unsigned int seed = 42) {
    std::vector<unsigned char> data(width * height);
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(0, 255);
    
    for (int i = 0; i < width * height; ++i) {
        data[i] = static_cast<unsigned char>(dis(gen));
    }
    
    ASCIIImage image;
    image.loadFromGrayscale(data, width, height);
    return image;
}

// Helper function to create RGB color pattern
ASCIIImage createColorPattern(int width, int height) {
    std::vector<unsigned char> data(width * height * 3);
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = (y * width + x) * 3;
            data[idx] = static_cast<unsigned char>((x * 255) / (width - 1));     // R
            data[idx + 1] = static_cast<unsigned char>((y * 255) / (height - 1)); // G
            data[idx + 2] = 128;                                                   // B
        }
    }
    
    ASCIIImage image;
    image.loadFromRGB(data, width, height);
    return image;
}

int main() {
    PanelManager manager;
    manager.initialize();
    
    // Create panels for different patterns
    auto panel1 = std::make_shared<Panel>(2, 2, 42, 12, "Checkerboard");
    auto panel2 = std::make_shared<Panel>(46, 2, 42, 12, "Gradient");
    auto panel3 = std::make_shared<Panel>(2, 15, 42, 12, "Circle");
    auto panel4 = std::make_shared<Panel>(46, 15, 42, 12, "Waves");
    auto panel5 = std::make_shared<Panel>(2, 28, 42, 12, "Noise");
    auto panel6 = std::make_shared<Panel>(46, 28, 42, 12, "RGB Pattern");
    
    // Set border colors
    panel1->setBorderColor(Color::BRIGHT_CYAN);
    panel2->setBorderColor(Color::BRIGHT_GREEN);
    panel3->setBorderColor(Color::BRIGHT_YELLOW);
    panel4->setBorderColor(Color::BRIGHT_BLUE);
    panel5->setBorderColor(Color::BRIGHT_MAGENTA);
    panel6->setBorderColor(Color::BRIGHT_RED);
    
    // Create and render patterns
    auto checkerboard = createCheckerboard(38, 8, 4);
    checkerboard.renderToPanel(*panel1, 1, 1);
    
    auto gradient = createGradient(38, 8, true);
    gradient.renderToPanel(*panel2, 1, 1);
    
    auto circle = createCircle(38, 8);
    circle.renderToPanel(*panel3, 1, 1);
    
    auto waves = createWaves(38, 8, 0.3f);
    waves.renderToPanel(*panel4, 1, 1);
    
    auto noise = createNoise(38, 8);
    noise.renderToPanel(*panel5, 1, 1);
    
    auto colorPattern = createColorPattern(38, 8);
    colorPattern.renderToPanel(*panel6, 1, 1);
    
    // Add all panels
    manager.addPanel(panel1);
    manager.addPanel(panel2);
    manager.addPanel(panel3);
    manager.addPanel(panel4);
    manager.addPanel(panel5);
    manager.addPanel(panel6);
    
    // Render
    manager.renderAll();
    
    // Wait for user
    std::cout << std::endl;
    TerminalUtils::moveCursor(42, 0);
    std::cout << "Procedural pattern examples - Press Enter to exit...";
    std::cout.flush();
    std::cin.get();
    
    manager.cleanup();
    return 0;
}
