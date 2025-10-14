#include "PanelManager.h"
#include "Panel.h"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

using namespace ASCIIDisplay;

int main() {
    PanelManager manager;
    manager.initialize();
    
    // Create an inventory panel
    auto inventory = std::make_shared<Panel>(2, 2, 30, 12, "Inventory");
    inventory->setBorderColor(Color::BRIGHT_GREEN);
    inventory->writeText(0, 1, "1. Sword", Color::BRIGHT_YELLOW);
    inventory->writeText(1, 1, "2. Shield", Color::BRIGHT_YELLOW);
    inventory->writeText(2, 1, "3. Potion x5", Color::BRIGHT_CYAN);
    inventory->writeText(3, 1, "4. Key", Color::BRIGHT_MAGENTA);
    inventory->writeText(5, 1, "Gold: 150", Color::YELLOW);
    
    // Create a map panel
    auto mapPanel = std::make_shared<Panel>(35, 2, 40, 12, "Map");
    mapPanel->setBorderColor(Color::BRIGHT_BLUE);
    mapPanel->fill('.', Color::GREEN);
    mapPanel->drawBox(5, 5, 10, 5, '#');
    mapPanel->setChar(7, 9, '@', Color::BRIGHT_RED);
    mapPanel->writeText(0, 1, "You are here: @", Color::WHITE);
    
    // Create a status panel
    auto status = std::make_shared<Panel>(2, 16, 73, 8, "Status");
    status->setBorderColor(Color::BRIGHT_YELLOW);
    status->writeText(0, 1, "HP: [##########] 100/100", Color::BRIGHT_RED);
    status->writeText(1, 1, "MP: [########--] 80/100", Color::BRIGHT_BLUE);
    status->writeText(2, 1, "XP: [#####-----] 50/100", Color::BRIGHT_GREEN);
    status->drawLine(3, 0, status->getContentWidth(), '-');
    status->writeText(4, 1, "Location: Dark Forest", Color::WHITE);
    status->writeText(5, 1, "Time: 23:45", Color::BRIGHT_CYAN);
    
    // Add all panels to manager
    manager.addPanel(inventory);
    manager.addPanel(mapPanel);
    manager.addPanel(status);
    
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
