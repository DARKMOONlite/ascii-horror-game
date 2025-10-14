#ifndef TERMINAL_UTILS_H
#define TERMINAL_UTILS_H

#include <string>
#include <vector>

namespace ASCIIDisplay {

// ANSI color codes
enum class Color {
    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37,
    BRIGHT_BLACK = 90,
    BRIGHT_RED = 91,
    BRIGHT_GREEN = 92,
    BRIGHT_YELLOW = 93,
    BRIGHT_BLUE = 94,
    BRIGHT_MAGENTA = 95,
    BRIGHT_CYAN = 96,
    BRIGHT_WHITE = 97,
    RESET = 0
};

// Terminal manipulation utilities
class TerminalUtils {
public:
    // Clear the entire terminal
    static void clearScreen();
    
    // Move cursor to specific position (0-indexed)
    static void moveCursor(int row, int col);
    
    // Hide/show cursor
    static void hideCursor();
    static void showCursor();
    
    // Set text color
    static void setColor(Color fg, Color bg = Color::RESET);
    
    // Reset all formatting
    static void resetFormat();
    
    // Get terminal size
    static void getTerminalSize(int& rows, int& cols);
    
    // Save/restore cursor position
    static void saveCursor();
    static void restoreCursor();
    
    // Enable/disable alternative screen buffer
    static void enableAltScreen();
    static void disableAltScreen();
    
    // Convert RGB to nearest ANSI color
    static Color rgbToColor(int r, int g, int b);
    
    // Get grayscale character for brightness (0-255)
    static char brightnessToChar(int brightness);
};

} // namespace ASCIIDisplay

#endif // TERMINAL_UTILS_H
