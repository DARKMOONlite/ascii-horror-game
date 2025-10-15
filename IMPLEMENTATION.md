# Implementation Details

## Overview
This implementation creates a lightweight modern C++ system that converts images to ASCII art with colored terminal output using kernel-based image processing.

## Key Features Implemented

### 1. Image Loading
- Uses stb_image header-only library (no external dependencies)
- Supports JPEG, PNG, BMP, TGA, PSD, GIF, HDR, PIC formats
- Handles images with 1, 3, or 4 channels (grayscale, RGB, RGBA)

### 2. Kernel-Based Image Processing
Implements 3x3 convolution kernels:
- **Sharpen**: Enhances edges and details
- **Blur**: Gaussian blur for smoothing
- **Edge Detection**: Highlights edges (perfect for horror aesthetic)

### 3. ASCII Conversion
- Maps pixel brightness to ASCII characters from a gradient of 70+ characters
- Brightness calculation uses standard luminance formula: 0.299R + 0.587G + 0.114B
- Characters range from darkest (space) to brightest ($, @)

### 4. Terminal Color Support
- Uses ANSI 24-bit true color escape codes (\\033[38;2;R;G;B;m)
- Supports modern terminals (iTerm2, Windows Terminal, GNOME Terminal, etc.)
- Color averaging: averages pixel colors for each character position
- The averaged colors approximate the original image when viewed from a distance

### 5. Modern C++ Design
- C++17 standard
- Smart pointers (std::unique_ptr) for memory management
- RAII principles
- Header-based architecture
- Namespace organization

## Architecture

### Components
1. **ImageProcessor** - Image loading, kernel convolution, resizing
2. **AsciiConverter** - ASCII conversion and color mapping
3. **Main Application** - CLI interface

### Data Flow
1. Load image → 2. Apply kernel (optional) → 3. Resize to target width → 4. Convert to ASCII with colors → 5. Output to terminal

## Technical Details

### Color Averaging Algorithm
For each character position:
1. Determine the block of pixels it represents (typically 1x2 pixels)
2. Calculate average R, G, B values across all pixels in the block
3. Apply the averaged color as an ANSI escape code before the character
4. When viewed from a distance, adjacent characters blend to approximate original colors

### Kernel Convolution
- 3x3 kernels applied to each color channel independently
- Boundary handling: clamps to image edges
- Values clamped to [0, 255] range after convolution

### Aspect Ratio Handling
- Terminal characters are ~2x taller than wide
- Automatically accounts for this when resizing images
- Maintains proper aspect ratio of source image

## Building and Usage

### Build
```bash
mkdir build && cd build
cmake ..
make
```

### Usage Examples
```bash
# Basic conversion with color
./build/ascii_converter image.jpg --width 80

# Edge detection (horror aesthetic)
./build/ascii_converter scary.jpg --width 100 --kernel edge

# Monochrome output
./build/ascii_converter image.png --width 60 --no-color

# Sharpen for detail
./build/ascii_converter portrait.jpg --width 120 --kernel sharpen
```

## Performance Characteristics
- O(w×h×k²) for kernel convolution (w=width, h=height, k=kernel size)
- O(w×h) for ASCII conversion
- Minimal memory usage with smart pointers
- Single-pass processing

## Security
- No known vulnerabilities (CodeQL verified)
- No external network access
- No user input injection risks
- Proper error handling for file I/O

## Future Enhancement Possibilities
- Additional kernel types (emboss, outline, etc.)
- Dithering for better detail preservation
- Animation support for video/GIF files
- Custom ASCII character sets
- Background color support
- Unicode block characters for higher resolution
