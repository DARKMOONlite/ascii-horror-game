#include "ascii_generator.hpp"
#include <iostream>
#include <string>

void print_usage(const char* program_name) {
    std::cout << "Usage: " << program_name << " <image_path> [width]" << std::endl;
    std::cout << "  image_path: Path to the input image file" << std::endl;
    std::cout << "  width:      Optional ASCII art width (default: 100)" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    std::string image_path = argv[1];
    int width = -1;  // Use default width
    
    if (argc >= 3) {
        try {
            width = std::stoi(argv[2]);
        } catch (const std::exception& e) {
            std::cerr << "Error: Invalid width parameter. Using default width." << std::endl;
            width = -1;
        }
    }
    
    // Create ASCII generator with contrast=10 (matching Python version)
    AsciiGenerator generator(10, 100);
    
    try {
        generator.generate_ascii_art(image_path, width);
    } catch (const std::exception& e) {
        std::cerr << "Error generating ASCII art: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
