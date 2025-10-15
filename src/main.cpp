#include "image_processor.h"
#include "ascii_converter.h"
#include <iostream>
#include <cstring>

void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " <image_file> [options]\n";
    std::cout << "\nOptions:\n";
    std::cout << "  --width <n>      Set output width in characters (default: 80)\n";
    std::cout << "  --no-color       Disable colored output\n";
    std::cout << "  --kernel <type>  Apply kernel before conversion:\n";
    std::cout << "                   - sharpen: Sharpen edges\n";
    std::cout << "                   - blur: Gaussian blur\n";
    std::cout << "                   - edge: Edge detection\n";
    std::cout << "  --help           Show this help message\n";
    std::cout << "\nExample:\n";
    std::cout << "  " << programName << " image.jpg --width 100 --kernel sharpen\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }
    
    std::string filename;
    int targetWidth = 80;
    bool useColor = true;
    std::string kernelType = "none";
    
    // Parse arguments
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--help") == 0) {
            printUsage(argv[0]);
            return 0;
        } else if (std::strcmp(argv[i], "--width") == 0) {
            if (i + 1 < argc) {
                targetWidth = std::atoi(argv[++i]);
                if (targetWidth <= 0) {
                    std::cerr << "Error: Width must be positive\n";
                    return 1;
                }
            } else {
                std::cerr << "Error: --width requires a value\n";
                return 1;
            }
        } else if (std::strcmp(argv[i], "--no-color") == 0) {
            useColor = false;
        } else if (std::strcmp(argv[i], "--kernel") == 0) {
            if (i + 1 < argc) {
                kernelType = argv[++i];
            } else {
                std::cerr << "Error: --kernel requires a type\n";
                return 1;
            }
        } else if (argv[i][0] != '-') {
            filename = argv[i];
        } else {
            std::cerr << "Error: Unknown option " << argv[i] << "\n";
            printUsage(argv[0]);
            return 1;
        }
    }
    
    if (filename.empty()) {
        std::cerr << "Error: No image file specified\n";
        printUsage(argv[0]);
        return 1;
    }
    
    // Load image
    ascii_art::ImageProcessor processor;
    auto img = processor.loadImage(filename);
    
    if (!img) {
        std::cerr << "Error: Failed to load image '" << filename << "'\n";
        std::cerr << "Make sure the file exists and is a valid image format (JPEG, PNG, BMP, etc.)\n";
        return 1;
    }
    
    std::cout << "Loaded image: " << img->width << "x" << img->height 
              << " (" << img->channels << " channels)\n";
    
    // Apply kernel if requested
    if (kernelType != "none") {
        std::vector<float> kernel;
        int kernelSize = 0;
        
        if (kernelType == "sharpen") {
            kernelSize = 3;
            kernel = {
                 0, -1,  0,
                -1,  5, -1,
                 0, -1,  0
            };
            std::cout << "Applying sharpen kernel...\n";
        } else if (kernelType == "blur") {
            kernelSize = 3;
            kernel = {
                1.0f/9, 1.0f/9, 1.0f/9,
                1.0f/9, 1.0f/9, 1.0f/9,
                1.0f/9, 1.0f/9, 1.0f/9
            };
            std::cout << "Applying blur kernel...\n";
        } else if (kernelType == "edge") {
            kernelSize = 3;
            kernel = {
                -1, -1, -1,
                -1,  8, -1,
                -1, -1, -1
            };
            std::cout << "Applying edge detection kernel...\n";
        } else {
            std::cerr << "Warning: Unknown kernel type '" << kernelType << "', ignoring\n";
        }
        
        if (!kernel.empty()) {
            img = processor.applyKernel(*img, kernel, kernelSize);
            if (!img) {
                std::cerr << "Error: Failed to apply kernel\n";
                return 1;
            }
        }
    }
    
    // Convert to ASCII
    ascii_art::AsciiConverter converter;
    std::cout << "Converting to ASCII (width: " << targetWidth << ", color: " 
              << (useColor ? "enabled" : "disabled") << ")...\n\n";
    
    std::string asciiArt = converter.convertToAsciiWithWidth(*img, targetWidth, useColor);
    
    std::cout << asciiArt;
    
    return 0;
}
