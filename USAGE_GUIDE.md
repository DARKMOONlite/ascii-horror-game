# Terminal Display Framework Usage Guide

## Introduction

This guide will help you use the Terminal Display Framework to create organized, dynamic terminal UIs for your applications and games.

## Basic Concepts

### 1. Panels
Panels are rectangular regions on the terminal that can display content. Each panel has:
- Position (x, y coordinates)
- Size (width, height)
- Optional border with customizable color
- Optional title
- Independent content buffer

### 2. Panel Manager
The PanelManager coordinates multiple panels and handles:
- Initialization and cleanup of terminal state
- Rendering all panels in order (z-ordering)
- Managing panel lifecycle

### 3. ASCII Images
Convert image data to ASCII art with:
- RGB or grayscale input support
- Automatic character mapping based on brightness
- Color preservation using ANSI color codes
- Resizing capabilities

### 4. ASCII Videos
Animated sequences of ASCII images:
- Frame-based playback
- Configurable frame rate
- Loop support

## Quick Start Example

```cpp
#include "PanelManager.h"
#include "Panel.h"

using namespace ASCIIDisplay;

int main() {
    // Initialize the panel manager
    PanelManager manager;
    manager.initialize();
    
    // Create a panel at position (5, 5) with size 40x10
    auto panel = std::make_shared<Panel>(5, 5, 40, 10, "My First Panel");
    
    // Customize the panel
    panel->setBorderColor(Color::BRIGHT_GREEN);
    panel->writeText(0, 1, "Hello, Terminal UI!", Color::BRIGHT_YELLOW);
    
    // Add to manager and render
    manager.addPanel(panel);
    manager.renderAll();
    
    // Wait for user
    std::cin.get();
    
    // Cleanup
    manager.cleanup();
    return 0;
}
```

## Working with Panels

### Creating and Positioning Panels

```cpp
// Create a panel: Panel(x, y, width, height, title)
auto inventory = std::make_shared<Panel>(2, 2, 30, 15, "Inventory");

// Move panel to new position
inventory->setPosition(10, 10);

// Resize panel
inventory->setSize(35, 20);

// Toggle border
inventory->setBorder(false);  // Hide border
inventory->setBorder(true);   // Show border
```

### Drawing Content

```cpp
// Write text at position (row, col) relative to panel content area
panel->writeText(0, 0, "Item: Sword", Color::BRIGHT_YELLOW);

// Set individual characters
panel->setChar(5, 10, '@', Color::BRIGHT_RED);

// Fill entire panel with a character
panel->fill('.', Color::GREEN);

// Draw a horizontal line
panel->drawLine(5, 0, 30, '-', true);

// Draw a vertical line
panel->drawLine(0, 10, 20, '|', false);

// Draw a box
panel->drawBox(2, 2, 10, 5, '#');

// Clear panel content
panel->clear();
```

### Color Support

Available colors:
- BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE
- BRIGHT_BLACK, BRIGHT_RED, BRIGHT_GREEN, BRIGHT_YELLOW, 
  BRIGHT_BLUE, BRIGHT_MAGENTA, BRIGHT_CYAN, BRIGHT_WHITE

```cpp
// Use colors when writing text or setting characters
panel->writeText(0, 0, "HP:", Color::BRIGHT_RED);
panel->writeText(0, 4, "100/100", Color::WHITE);
```

## Working with Images

### Creating ASCII Images from Text

```cpp
#include "ASCIIImage.h"

// Define ASCII art as text
std::vector<std::string> art = {
    "  /\\_/\\  ",
    " ( o.o ) ",
    "  > ^ <  "
};

ASCIIImage catImage;
catImage.loadFromText(art);

// Render to panel at position (row, col)
catImage.renderToPanel(*panel, 0, 0);
```

### Creating Images from Data

```cpp
// From grayscale data (0-255 per pixel)
std::vector<unsigned char> grayData;
// ... fill with grayscale values ...
ASCIIImage image;
image.loadFromGrayscale(grayData, width, height);

// From RGB data (RGB triplets, 0-255 per component)
std::vector<unsigned char> rgbData;
// ... fill with RGB values ...
image.loadFromRGB(rgbData, width, height);
```

### Manipulating Images

```cpp
// Resize image
image.resize(80, 40);

// Set specific pixels
image.setPixel(row, col, '@', Color::BRIGHT_GREEN);

// Get image properties
int w = image.getWidth();
int h = image.getHeight();
char ch = image.getChar(row, col);
Color color = image.getColor(row, col);
```

## Working with Videos

### Creating Animated Content

```cpp
#include "ASCIIVideo.h"

ASCIIVideo animation;

// Create frames
for (int i = 0; i < 10; ++i) {
    auto frame = std::make_shared<ASCIIImage>(width, height);
    // ... populate frame ...
    animation.addFrame(frame);
}

// Set playback rate
animation.setFrameRate(10.0);  // 10 FPS

// Animation loop
while (running) {
    panel->clear();
    animation.renderToPanel(*panel, 0, 0);
    manager.renderAll();
    animation.nextFrame();
    
    std::this_thread::sleep_for(
        std::chrono::milliseconds(100));
}
```

### Loading Video from Data

```cpp
// Prepare frame data
std::vector<std::vector<unsigned char>> frames;
// ... fill with frame data ...

// Load from grayscale sequence
video.loadFromGrayscaleSequence(frames, width, height);

// Or from RGB sequence
video.loadFromRGBSequence(frames, width, height);
```

## Working with Large ASCII Text

### ASCII Letters

Create large, readable ASCII characters made of multiple terminal characters:

```cpp
#include "ASCIILetter.h"

// Create a large letter 'A' with 3x scale
ASCIILetter letterA('A', 3);
letterA.setColor(Color::BRIGHT_GREEN);

// Apply effects
letterA.setEffect(TextEffect::BOLD);

// Get rendered lines
auto lines = letterA.getRenderedLines();
for (size_t i = 0; i < lines.size(); ++i) {
    panel->writeText(i, 0, lines[i], letterA.getColor());
}
```

### ASCII Words

Combine multiple letters to form words:

```cpp
#include "ASCIIWord.h"

// Create a word with scale 2
ASCIIWord word("HELLO", 2);
word.setColor(Color::BRIGHT_CYAN);
word.setEffect(TextEffect::BOLD);
word.setLetterSpacing(2);  // Space between letters

// Render the word
auto lines = word.renderLines();
for (size_t i = 0; i < lines.size(); ++i) {
    panel->writeText(i, 0, lines[i], word.getColor());
}
```

### ASCII Paragraphs

Create multi-word text with word wrapping and alignment:

```cpp
#include "ASCIIParagraph.h"

// Create a paragraph
ASCIIParagraph para("WELCOME TO THE GAME", 2);
para.setColor(Color::BRIGHT_MAGENTA);
para.setMaxWidth(80);  // Maximum width for wrapping
para.setAlignment(TextAlign::CENTER);  // Center align
para.setWordSpacing(3);   // Space between words
para.setLineSpacing(1);   // Space between lines

// Render directly to panel
para.renderToPanel(*panel, 0, 0);
```

### Text Effects

Available text effects that can be combined:

```cpp
// Single effect
word.setEffect(TextEffect::BOLD);
word.setEffect(TextEffect::ITALIC);

// Combine effects with bitwise OR
word.setEffect(TextEffect::BOLD | TextEffect::ITALIC);

// Available effects:
// - TextEffect::NONE     - No effect
// - TextEffect::BOLD     - Thicker/denser characters
// - TextEffect::ITALIC   - Slanted characters
// - TextEffect::UNDERLINE - Underlined (placeholder)
// - TextEffect::BLINK    - Blinking animation (placeholder)
// - TextEffect::WAVE     - Wave motion (placeholder)
// - TextEffect::SHAKE    - Shake effect (placeholder)
```

### Different Scales

Control the size of your ASCII text:

```cpp
// Small text (scale 1)
ASCIIWord small("SMALL", 1);

// Medium text (scale 2)
ASCIIWord medium("MEDIUM", 2);

// Large text (scale 3)
ASCIIWord large("LARGE", 3);

// Even larger (scale 4+)
ASCIIWord xlarge("HUGE", 5);
```

### Text Alignment

Control how paragraphs are aligned:

```cpp
ASCIIParagraph para("YOUR TEXT HERE", 2);

// Left align (default)
para.setAlignment(TextAlign::LEFT);

// Center align
para.setAlignment(TextAlign::CENTER);

// Right align
para.setAlignment(TextAlign::RIGHT);

// Justify (placeholder for future implementation)
para.setAlignment(TextAlign::JUSTIFY);
```

### Use Cases for Large ASCII Text

1. **Game Titles**: Create eye-catching title screens
   ```cpp
   ASCIIParagraph title("HORROR GAME", 3);
   title.setColor(Color::BRIGHT_RED);
   title.setEffect(TextEffect::BOLD);
   title.setAlignment(TextAlign::CENTER);
   ```

2. **Menu Options**: Make menu items more visible
   ```cpp
   ASCIIWord startOption("START", 2);
   startOption.setColor(Color::BRIGHT_GREEN);
   ```

3. **Game Over Screen**: Display important messages
   ```cpp
   ASCIIParagraph gameOver("GAME OVER", 4);
   gameOver.setColor(Color::BRIGHT_RED);
   gameOver.setEffect(TextEffect::BOLD);
   ```

4. **Level Indicators**: Show level numbers prominently
   ```cpp
   ASCIIWord level("LEVEL 5", 2);
   level.setColor(Color::BRIGHT_YELLOW);
   ```

### TTF Font Support (Future)

The framework includes placeholder support for TTF fonts:

```cpp
// This will be fully implemented in a future version
ASCIILetter letter('A');
letter.loadFont("path/to/font.ttf");  // Currently returns false
```

## Advanced Usage

### Z-Ordering Panels

```cpp
// Move panel to front (render last, appears on top)
manager.movePanelToFront(panel);

// Move panel to back (render first, appears behind)
manager.movePanelToBack(panel);
```

### Creating a Game UI

```cpp
// Create multiple panels for different UI elements
auto gameView = std::make_shared<Panel>(0, 0, 80, 40, "Game");
auto inventory = std::make_shared<Panel>(82, 0, 30, 20, "Inventory");
auto stats = std::make_shared<Panel>(82, 22, 30, 18, "Stats");
auto messages = std::make_shared<Panel>(0, 42, 112, 8, "Messages");

// Add all panels
manager.addPanel(gameView);
manager.addPanel(inventory);
manager.addPanel(stats);
manager.addPanel(messages);

// Update content independently
inventory->writeText(0, 1, "Gold: 250", Color::YELLOW);
stats->writeText(0, 1, "HP: 100/100", Color::BRIGHT_RED);

// Render all at once
manager.renderAll();
```

### Terminal Utilities

```cpp
// Manual terminal control (if needed)
TerminalUtils::clearScreen();
TerminalUtils::moveCursor(row, col);
TerminalUtils::setColor(Color::BRIGHT_GREEN);
TerminalUtils::hideCursor();
TerminalUtils::showCursor();

// Get terminal size
int rows, cols;
TerminalUtils::getTerminalSize(rows, cols);

// Convert colors
Color c = TerminalUtils::rgbToColor(255, 0, 0);  // Red
char ch = TerminalUtils::brightnessToChar(200);  // Bright character
```

## Best Practices

1. **Always cleanup**: Call `manager.cleanup()` before exiting to restore terminal state

2. **Use appropriate panel sizes**: Make sure panels fit within the terminal size

3. **Optimize rendering**: Only call `renderAll()` when content changes

4. **Handle terminal resize**: Get terminal size and adjust panels accordingly

5. **Use colors wisely**: Too many colors can be distracting

6. **Test on different terminals**: ANSI support varies across terminals

## Building Your Application

Add to your CMakeLists.txt:

```cmake
# Include the framework
add_subdirectory(path/to/ascii-horror-game)

# Link your executable
target_link_libraries(your_app ascii_display)
```

Or compile manually:

```bash
g++ -std=c++17 -I/path/to/include your_app.cpp \
    -L/path/to/build -lascii_display -o your_app
```

## Troubleshooting

**Terminal looks garbled after exit:**
- Make sure to call `manager.cleanup()` before exiting

**Colors not showing:**
- Your terminal may not support ANSI colors
- Try a different terminal emulator

**Panels overlap incorrectly:**
- Check z-ordering with `movePanelToFront()` and `movePanelToBack()`

**Cursor visible during rendering:**
- Call `manager.initialize()` to hide cursor
- Make sure you're not manually showing cursor

## Examples

See the `examples/` directory for complete working examples:
- `example_panels.cpp` - Multiple panel layout
- `example_image.cpp` - ASCII image display
- `example_video.cpp` - Animated ASCII video
- `example_full.cpp` - Complete game UI demonstration
- `example_procedural.cpp` - Procedural pattern generation
- `example_text.cpp` - Large ASCII letters, words, and paragraphs with effects
