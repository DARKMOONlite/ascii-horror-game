# Terminal Display Framework - Project Summary

## Overview

This project provides a comprehensive C++ framework for creating organized, dynamic terminal-based user interfaces. It's designed specifically for terminal games and applications that need multiple display regions, ASCII art, and animations.

## Project Structure

```
ascii-horror-game/
├── include/                    # Header files
│   ├── TerminalUtils.h        # Terminal control utilities
│   ├── Panel.h                # Panel class
│   ├── PanelManager.h         # Panel management
│   ├── ASCIIImage.h           # ASCII image handling
│   └── ASCIIVideo.h           # ASCII video handling
├── src/                       # Implementation files
│   ├── TerminalUtils.cpp
│   ├── Panel.cpp
│   ├── PanelManager.cpp
│   ├── ASCIIImage.cpp
│   └── ASCIIVideo.cpp
├── examples/                  # Example programs
│   ├── example_panels.cpp     # Multiple panel layout
│   ├── example_image.cpp      # ASCII image rendering
│   ├── example_video.cpp      # Animation demo
│   ├── example_full.cpp       # Complete UI demo
│   └── example_procedural.cpp # Procedural patterns
├── CMakeLists.txt            # Build configuration
├── README.md                 # Quick start guide
├── USAGE_GUIDE.md           # Comprehensive usage guide
└── API_REFERENCE.md         # Complete API documentation
```

## Key Features

### 1. Panel System
- Create rectangular display regions at any position
- Each panel has its own content buffer
- Optional borders with customizable colors
- Optional titles
- Independent rendering

### 2. ASCII Image Support
- Convert RGB image data to ASCII art
- Convert grayscale data to ASCII art
- Load from text/ASCII art directly
- Automatic brightness-to-character mapping
- Color preservation using ANSI codes
- Image resizing support

### 3. ASCII Video Support
- Frame-based animation system
- Support for RGB and grayscale frame sequences
- Configurable frame rate
- Frame navigation (next, set frame)
- Loop support

### 4. Terminal Control
- ANSI color support (16 colors + bright variants)
- Cursor positioning and visibility control
- Screen clearing and management
- Terminal size detection
- Alternative screen buffer support

### 5. Easy Integration
- Header-only style usage
- CMake build system
- Static library output
- Clean C++17 API

## Technical Details

### Supported Platforms
- Linux (full support)
- macOS (full support)
- Windows 10+ (requires ANSI support or Windows Terminal)

### Requirements
- C++17 compatible compiler
- CMake 3.10 or higher
- Terminal with ANSI escape sequence support

### Color System
The framework uses ANSI color codes:
- 8 basic colors (black, red, green, yellow, blue, magenta, cyan, white)
- 8 bright variants
- Automatic RGB to ANSI color conversion
- Per-character color control

### ASCII Gradient
Characters are mapped by brightness:
- Space (darkest)
- . : - = + * # % @
- @ (brightest)

## Examples Output

### example_panels
Demonstrates a game UI with:
- Inventory panel (30x12)
- Map panel (40x12)
- Status panel (73x8)

Shows item lists, character position on map, HP/MP/XP bars, and game info.

### example_image
Displays a smiley face made from ASCII art with colored features.

### example_video
Animated bouncing ball (20 frames at 10 FPS):
- Ball bounces vertically
- Ground line at bottom
- Colored ball and ground

### example_full
Complete game UI demonstration:
- Game view with procedural gradient
- Inventory with items and equipment
- Character stats with progress bars
- Message log

### example_procedural
Six different procedurally generated patterns:
- Checkerboard pattern
- Horizontal gradient
- Circular gradient
- Wave interference pattern
- Random noise
- RGB color gradient

## Use Cases

1. **Terminal Games**: Create multi-panel UIs for roguelikes, RPGs, adventure games
2. **System Monitors**: Display real-time data in organized panels
3. **Terminal Applications**: Build rich TUIs for CLI tools
4. **ASCII Art Viewers**: Display and animate ASCII art
5. **Data Visualization**: Create charts and graphs in the terminal

## Performance Characteristics

- **Rendering**: Optimized for terminal output with minimal flicker
- **Memory**: Each panel maintains its own content buffer
- **Threading**: Not thread-safe; use from single thread or add synchronization
- **Refresh Rate**: Limited by terminal output speed (typically 30-60 FPS max)

## Building and Running

```bash
# Build
mkdir build && cd build
cmake ..
make

# Run examples
./example_panels
./example_image
./example_video
./example_full
./example_procedural
```

## Integration Example

```cpp
#include "PanelManager.h"
#include "Panel.h"

using namespace ASCIIDisplay;

int main() {
    PanelManager mgr;
    mgr.initialize();
    
    auto panel = std::make_shared<Panel>(10, 10, 40, 10, "Hello");
    panel->writeText(0, 1, "Hello World!", Color::BRIGHT_GREEN);
    
    mgr.addPanel(panel);
    mgr.renderAll();
    
    std::cin.get();
    mgr.cleanup();
}
```

## Future Enhancement Possibilities

1. Input handling system
2. Mouse support
3. More advanced text formatting (bold, underline)
4. Panel animations (move, resize)
5. Layout managers
6. Event system
7. True color (24-bit RGB) support
8. Unicode character support
9. Image loading from files (PNG, JPEG)
10. Video file playback

## License

This project is part of the ascii-horror-game repository.

## Contributing

When contributing:
- Follow existing code style
- Add examples for new features
- Update documentation
- Ensure cross-platform compatibility
- Write clear commit messages

## Credits

Created as a comprehensive terminal display framework for the ascii-horror-game project.
