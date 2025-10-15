# ASCII Horror Game

A testing ground for creating a terminal-based ASCII horror game.

## ASCII Image Converter

This project includes a modern C++ system that converts images to ASCII art with colored terminal output using kernel-based image processing.

### Features

- **Image Loading**: Supports common image formats (JPEG, PNG, BMP, TGA, etc.) using the stb_image library
- **Kernel-based Processing**: Apply various image processing kernels:
  - Sharpen: Enhance edges and details
  - Blur: Gaussian blur effect
  - Edge Detection: Highlight edges in the image
- **Colored ASCII Output**: Uses ANSI 24-bit true color escape codes to display ASCII art with colors that average to the original pixel colors
- **Configurable Width**: Adjust output width to fit your terminal
- **Modern C++17**: Clean, header-based architecture

### Building

```bash
mkdir build
cd build
cmake ..
make
```

### Usage

Basic usage:
```bash
./build/ascii_converter <image_file>
```

With options:
```bash
./build/ascii_converter image.jpg --width 100 --kernel sharpen
```

#### Options

- `--width <n>`: Set output width in characters (default: 80)
- `--no-color`: Disable colored output (monochrome ASCII)
- `--kernel <type>`: Apply image processing kernel before conversion
  - `sharpen`: Sharpen edges and enhance details
  - `blur`: Apply Gaussian blur
  - `edge`: Edge detection filter
- `--help`: Show help message

### Examples

Convert an image to colored ASCII art:
```bash
./build/ascii_converter test_image.ppm --width 60
```

Convert with edge detection (great for horror aesthetic):
```bash
./build/ascii_converter scary.jpg --width 80 --kernel edge
```

Convert with sharpening for better detail:
```bash
./build/ascii_converter portrait.png --width 100 --kernel sharpen
```

Black and white ASCII:
```bash
./build/ascii_converter image.jpg --width 80 --no-color
```

### How It Works

1. **Image Loading**: The system loads images using the stb_image header-only library
2. **Kernel Processing** (optional): Applies a 3x3 convolution kernel to the image for effects like sharpening or edge detection
3. **Color Averaging**: For each character position, the system averages the color of the corresponding pixels
4. **Brightness Mapping**: Converts pixel brightness to ASCII characters from a gradient (dark to bright)
5. **Color Application**: Applies ANSI 24-bit RGB color codes to each character to match the original image colors
6. **Terminal Output**: Outputs colored ASCII art that approximates the original image

### Architecture

The project is organized into three main components:

- **ImageProcessor** (`image_processor.h/cpp`): Handles image loading, kernel convolution, and resizing
- **AsciiConverter** (`ascii_converter.h/cpp`): Converts images to ASCII with color support
- **Main Application** (`main.cpp`): Command-line interface and user interaction

### Testing

A test image (`test_image.ppm`) is included. Try different kernels and settings:

```bash
# Original with color
./build/ascii_converter test_image.ppm --width 60

# Edge detection
./build/ascii_converter test_image.ppm --width 60 --kernel edge

# Sharpened
./build/ascii_converter test_image.ppm --width 60 --kernel sharpen

# Blurred
./build/ascii_converter test_image.ppm --width 60 --kernel blur
```

### Color Output

The ASCII converter uses ANSI escape codes to display colors in the terminal. For best results, use a terminal that supports 24-bit true color (most modern terminals do):

- iTerm2 (macOS)
- Terminal.app (macOS)
- Windows Terminal (Windows 10+)
- GNOME Terminal (Linux)
- Konsole (Linux)
- Most modern terminal emulators

The color averaging algorithm ensures that nearby ASCII characters blend to approximate the original image colors.
