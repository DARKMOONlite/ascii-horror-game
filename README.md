# ascii-horror-game
a testing ground for creating a terminal based ascii horror game.

## Terminal Display Framework

This project includes a comprehensive C++ framework for organizing and managing terminal-based displays with support for panels, ASCII images, and ASCII videos.

### Features

- **Panel System**: Create and manage multiple rectangular panels on the terminal
- **Panel Manager**: Organize panels with z-ordering and batch rendering
- **ASCII Images**: Convert image data to ASCII art with color support
- **ASCII Videos**: Handle sequences of ASCII frames for animations
- **ASCII Text**: Large ASCII letters, words, and paragraphs with effects and formatting
- **Terminal Utilities**: Colors, cursor control, and screen management
- **Flexible Layout**: Move and resize panels dynamically

### Building

```bash
mkdir build
cd build
cmake ..
make
```

### Examples

The framework includes several example programs:

1. **example_panels** - Demonstrates creating multiple panels (inventory, map, status)
2. **example_image** - Shows how to create and display ASCII images
3. **example_video** - Animates ASCII art as a video
4. **example_full** - Full demonstration with all features
5. **example_procedural** - Procedural pattern generation examples
6. **example_text** - Large ASCII text with letters, words, and paragraphs

Run examples from the build directory:
```bash
./example_panels
./example_image
./example_video
./example_full
./example_procedural
./example_text
```

### Quick Start

```cpp
#include "PanelManager.h"
#include "Panel.h"
#include "ASCIIImage.h"
#include "ASCIIParagraph.h"

using namespace ASCIIDisplay;

int main() {
    PanelManager manager;
    manager.initialize();
    
    // Create a panel
    auto panel = std::make_shared<Panel>(10, 10, 40, 15, "My Panel");
    panel->setBorderColor(Color::BRIGHT_GREEN);
    panel->writeText(0, 1, "Hello, World!", Color::BRIGHT_YELLOW);
    
    // Create large ASCII text
    ASCIIParagraph title("WELCOME", 2);
    title.setColor(Color::BRIGHT_CYAN);
    title.setAlignment(TextAlign::CENTER);
    title.renderToPanel(*panel, 3, 0);
    
    // Add to manager and render
    manager.addPanel(panel);
    manager.renderAll();
    
    std::cin.get();
    manager.cleanup();
    return 0;
}
```

### API Overview

#### PanelManager
- `initialize()` - Prepare terminal for rendering
- `addPanel(panel)` - Add a panel to be managed
- `renderAll()` - Render all panels to screen
- `cleanup()` - Restore terminal state

#### Panel
- `Panel(x, y, width, height, title)` - Create a panel
- `writeText(row, col, text, color)` - Write text in panel
- `setChar(row, col, char, color)` - Set individual character
- `drawLine(row, col, length, char)` - Draw a line
- `drawBox(row, col, width, height, char)` - Draw a box
- `clear()` - Clear panel content

#### ASCIIImage
- `loadFromRGB(data, width, height)` - Load from RGB image data
- `loadFromGrayscale(data, width, height)` - Load from grayscale data
- `loadFromText(lines)` - Load from text/ASCII art
- `renderToPanel(panel, row, col)` - Render to a panel
- `resize(width, height)` - Resize the image

#### ASCIIVideo
- `addFrame(image)` - Add a frame to the video
- `loadFromRGBSequence(frames, width, height)` - Load from RGB frames
- `nextFrame()` - Advance to next frame
- `renderToPanel(panel, row, col)` - Render current frame

#### ASCIILetter
- `ASCIILetter(char, scale)` - Create a large ASCII letter
- `setChar(char)` - Set the character to display
- `setScale(scale)` - Set size multiplier (1x, 2x, 3x, etc.)
- `setColor(color)` - Set text color
- `setEffect(effect)` - Apply text effects (BOLD, ITALIC, etc.)

#### ASCIIWord
- `ASCIIWord(text, scale)` - Create a word from multiple letters
- `setText(text)` - Set the word text
- `setScale(scale)` - Set size for all letters
- `setColor(color)` - Set color for all letters
- `setEffect(effect)` - Apply effects to all letters
- `setLetterSpacing(spacing)` - Set spacing between letters

#### ASCIIParagraph
- `ASCIIParagraph(text, scale)` - Create a paragraph
- `setText(text)` - Set the paragraph text
- `setScale(scale)` - Set size for all words
- `setColor(color)` - Set color for all words
- `setEffect(effect)` - Apply effects to all words
- `setAlignment(align)` - Set alignment (LEFT, CENTER, RIGHT, JUSTIFY)
- `setMaxWidth(width)` - Set maximum width for word wrapping
- `renderToPanel(panel, row, col)` - Render to a panel
- `renderToPanel(panel, row, col)` - Render current frame

### Use Cases

- Terminal-based games with multiple UI panels
- ASCII art display and animation
- Converting images/videos to ASCII for terminal display
- Creating HUDs for command-line applications
- Building text-based user interfaces
