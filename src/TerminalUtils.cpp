#include "TerminalUtils.h"
#include <iostream>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

namespace ASCIIDisplay {

void TerminalUtils::clearScreen() {
    std::cout << "\033[2J";
    std::cout.flush();
}

void TerminalUtils::moveCursor(int row, int col) {
    std::cout << "\033[" << (row + 1) << ";" << (col + 1) << "H";
    std::cout.flush();
}

void TerminalUtils::hideCursor() {
    std::cout << "\033[?25l";
    std::cout.flush();
}

void TerminalUtils::showCursor() {
    std::cout << "\033[?25h";
    std::cout.flush();
}

void TerminalUtils::setColor(Color fg, Color bg) {
    if (fg != Color::RESET) {
        std::cout << "\033[" << static_cast<int>(fg) << "m";
    }
    if (bg != Color::RESET) {
        std::cout << "\033[" << (static_cast<int>(bg) + 10) << "m";
    }
    std::cout.flush();
}

void TerminalUtils::resetFormat() {
    std::cout << "\033[0m";
    std::cout.flush();
}

void TerminalUtils::getTerminalSize(int& rows, int& cols) {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    rows = w.ws_row;
    cols = w.ws_col;
#endif
}

void TerminalUtils::saveCursor() {
    std::cout << "\033[s";
    std::cout.flush();
}

void TerminalUtils::restoreCursor() {
    std::cout << "\033[u";
    std::cout.flush();
}

void TerminalUtils::enableAltScreen() {
    std::cout << "\033[?1049h";
    std::cout.flush();
}

void TerminalUtils::disableAltScreen() {
    std::cout << "\033[?1049l";
    std::cout.flush();
}

Color TerminalUtils::rgbToColor(int r, int g, int b) {
    // Simple conversion: find dominant color
    int max_val = std::max(r, std::max(g, b));
    int min_val = std::min(r, std::min(g, b));
    
    // Check for grayscale
    if (max_val - min_val < 30) {
        if (max_val < 64) return Color::BLACK;
        else if (max_val < 128) return Color::BRIGHT_BLACK;
        else if (max_val < 192) return Color::WHITE;
        else return Color::BRIGHT_WHITE;
    }
    
    // Determine dominant color
    bool bright = max_val > 128;
    
    if (r > g && r > b) {
        return bright ? Color::BRIGHT_RED : Color::RED;
    } else if (g > r && g > b) {
        return bright ? Color::BRIGHT_GREEN : Color::GREEN;
    } else if (b > r && b > g) {
        return bright ? Color::BRIGHT_BLUE : Color::BLUE;
    } else if (r > 100 && g > 100 && b < 100) {
        return bright ? Color::BRIGHT_YELLOW : Color::YELLOW;
    } else if (r > 100 && b > 100 && g < 100) {
        return bright ? Color::BRIGHT_MAGENTA : Color::MAGENTA;
    } else if (g > 100 && b > 100 && r < 100) {
        return bright ? Color::BRIGHT_CYAN : Color::CYAN;
    }
    
    return Color::WHITE;
}

char TerminalUtils::brightnessToChar(int brightness) {
    // ASCII gradient from dark to light
    const char gradient[] = " .:-=+*#%@";
    const int gradientSize = sizeof(gradient) - 1;
    
    int index = (brightness * gradientSize) / 256;
    if (index >= gradientSize) index = gradientSize - 1;
    if (index < 0) index = 0;
    
    return gradient[index];
}

} // namespace ASCIIDisplay
