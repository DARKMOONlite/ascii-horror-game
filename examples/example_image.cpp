#include "PanelManager.h"
#include "Panel.h"
#include "ASCIIImage.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace ASCIIDisplay;

int main() {
    PanelManager manager;
    manager.initialize();
    
    // Create a panel to display the image
    auto imagePanel = std::make_shared<Panel>(2, 2, 52, 22, "ASCII Image Demo");
    imagePanel->setBorderColor(Color::BRIGHT_CYAN);
    
    // Create an ASCII image from text (a simple smiley face)
    std::vector<std::string> smileyLines = {
        "         .:::::::::.         ",
        "      .:::.     .:::.      ",
        "    .::               ::.    ",
        "   ::   ##         ##   ::   ",
        "  ::    ##         ##    ::  ",
        " ::                       :: ",
        " ::                       :: ",
        "::                         ::",
        "::   #                #    ::",
        "::    #              #     ::",
        "::     ##          ##      ::",
        " ::      ##########       :: ",
        " ::                       :: ",
        "  ::                     ::  ",
        "   ::                   ::   ",
        "    ::.               .::    ",
        "      :::.         .:::      ",
        "         .:::::::::.         "
    };
    
    ASCIIImage smiley;
    smiley.loadFromText(smileyLines);
    
    // Add some color variations
    for (int y = 0; y < smiley.getHeight(); ++y) {
        for (int x = 0; x < smiley.getWidth(); ++x) {
            char ch = smiley.getChar(y, x);
            if (ch == ':' || ch == '.') {
                smiley.setPixel(y, x, ch, Color::BRIGHT_YELLOW);
            } else if (ch == '#') {
                smiley.setPixel(y, x, ch, Color::BRIGHT_BLUE);
            }
        }
    }
    
    // Render image to panel
    smiley.renderToPanel(*imagePanel, 1, 1);
    
    // Add panel to manager
    manager.addPanel(imagePanel);
    
    // Render all panels
    manager.renderAll();
    
    // Wait for user input
    std::cout << std::endl;
    TerminalUtils::moveCursor(25, 0);
    std::cout << "Press Enter to exit...";
    std::cout.flush();
    std::cin.get();
    
    manager.cleanup();
    return 0;
}
