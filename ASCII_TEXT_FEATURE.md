# ASCII Text Rendering Feature

## Overview

This implementation adds support for creating large, readable ASCII text made up of multiple terminal characters. This solves the problem of regular ASCII characters being too small to read by rendering each letter as a larger ASCII art representation.

## Key Components

### 1. ASCIILetter Class
- **Purpose**: Renders a single character as large ASCII art
- **Features**:
  - Scalable from 1x to any size
  - Built-in 5x5 bitmap font for all letters, numbers, and common symbols
  - Color support
  - Text effects (BOLD, ITALIC)
  - Placeholder for TTF font loading

### 2. ASCIIWord Class
- **Purpose**: Manages multiple ASCIILetters to form words
- **Features**:
  - Automatically spaces letters
  - Configurable letter spacing
  - Applies uniform styling to all letters
  - Color and effect support

### 3. ASCIIParagraph Class
- **Purpose**: Manages multiple ASCIIWords with advanced layout
- **Features**:
  - Word wrapping based on maximum width
  - Text alignment (LEFT, CENTER, RIGHT, JUSTIFY)
  - Configurable word and line spacing
  - Direct rendering to panels
  - Animation support (placeholder)

## Text Effects

The following effects are supported:

- **BOLD**: Uses denser characters (@) instead of (#)
- **ITALIC**: Applies a skew/slant to characters
- **UNDERLINE**: Placeholder for future implementation
- **BLINK**: Placeholder for animation
- **WAVE**: Placeholder for wave motion effect
- **SHAKE**: Placeholder for shake effect

Effects can be combined using bitwise OR: `TextEffect::BOLD | TextEffect::ITALIC`

## Scale Options

Text can be scaled to different sizes:
- **Scale 1**: 5x5 pixels per character (compact)
- **Scale 2**: 10x10 pixels per character (medium)
- **Scale 3**: 15x15 pixels per character (large)
- **Scale 4+**: Even larger for dramatic title screens

## Alignment Options

Paragraphs support multiple alignment modes:
- **LEFT**: Default left alignment
- **CENTER**: Centers text within max width
- **RIGHT**: Right-aligns text
- **JUSTIFY**: Placeholder for justified text

## Usage Example

```cpp
#include "ASCIIParagraph.h"
#include "Panel.h"

// Create a panel
auto panel = std::make_shared<Panel>(10, 10, 100, 30, "Title");

// Create large ASCII text
ASCIIParagraph title("HORROR GAME", 3);
title.setColor(Color::BRIGHT_RED);
title.setEffect(TextEffect::BOLD);
title.setAlignment(TextAlign::CENTER);
title.setMaxWidth(100);

// Render to panel
title.renderToPanel(*panel, 5, 0);
```

## Character Set

The built-in font includes:
- Uppercase letters A-Z
- Numbers 0-9
- Special characters: ! ? . , ' " - + and space
- Unknown characters are rendered as a filled box

## Future Enhancements

### TTF Font Support
The classes include placeholder methods for loading TTF fonts using FreeType library. This would allow:
- Custom fonts for unique styles
- More character sets (Unicode)
- Anti-aliased rendering
- Better typography

### Animation Effects
Placeholder methods exist for:
- Wave motion effects
- Shake/vibrate effects
- Blinking text
- Color cycling
- Typewriter effects

### Implementation Plan for TTF
To add TTF support in the future:
1. Add FreeType library dependency to CMakeLists.txt
2. Implement font loading in `ASCIILetter::loadFont()`
3. Rasterize TTF glyphs to ASCII art
4. Cache rendered characters for performance
5. Support multiple fonts simultaneously

## Performance Considerations

- **Memory**: Each letter is stored as vector of strings
- **Rendering**: Rendering is done once, cached in the object
- **Scaling**: Scaling regenerates the ASCII art
- **Text Changes**: Changing text rebuilds the internal structure

## Testing

A comprehensive example program (`example_text.cpp`) demonstrates:
- Single letters with different scales
- Words with effects
- Paragraphs with alignment
- Multiple scales comparison
- Word wrapping demonstration

Run with:
```bash
cd build
./example_text
```

## Integration with Existing Framework

The ASCII text classes integrate seamlessly with the existing framework:
- Renders to Panel objects
- Uses existing Color enum
- Compatible with PanelManager
- Follows same design patterns
- Included in the ascii_display library

## Build Instructions

The new classes are automatically included when building:

```bash
mkdir build
cd build
cmake ..
make
```

The library will include the new components without any additional configuration.

## API Additions

See `API_REFERENCE.md` for complete API documentation of:
- ASCIILetter class
- ASCIIWord class
- ASCIIParagraph class
- TextEffect enum
- TextAlign enum

See `USAGE_GUIDE.md` for usage examples and best practices.
