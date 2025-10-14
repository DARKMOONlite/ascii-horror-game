#include "PanelManager.h"
#include "Panel.h"
#include "ASCIIImage.h"
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

using namespace ASCIIDisplay;

int main() {
    PanelManager manager;
    manager.initialize();
    
    // Create multiple panels demonstrating the full framework
    
    // 1. Game view panel with procedural content
    auto gameView = std::make_shared<Panel>(2, 2, 50, 15, "Game View");
    gameView->setBorderColor(Color::BRIGHT_GREEN);
    
    // Create a simple procedural image (gradient pattern)
    std::vector<unsigned char> gradientData;
    int imgWidth = 46;
    int imgHeight = 11;
    
    for (int y = 0; y < imgHeight; ++y) {
        for (int x = 0; x < imgWidth; ++x) {
            // Create a circular gradient
            float dx = x - imgWidth / 2.0f;
            float dy = y - imgHeight / 2.0f;
            float dist = std::sqrt(dx * dx + dy * dy);
            float maxDist = std::sqrt((imgWidth/2.0f)*(imgWidth/2.0f) + (imgHeight/2.0f)*(imgHeight/2.0f));
            
            unsigned char brightness = static_cast<unsigned char>(255 * (1.0f - std::min(1.0f, dist / maxDist)));
            gradientData.push_back(brightness);
        }
    }
    
    ASCIIImage gradient;
    gradient.loadFromGrayscale(gradientData, imgWidth, imgHeight);
    gradient.renderToPanel(*gameView, 1, 1);
    
    // 2. Inventory panel
    auto inventory = std::make_shared<Panel>(54, 2, 30, 15, "Inventory");
    inventory->setBorderColor(Color::BRIGHT_YELLOW);
    inventory->writeText(1, 2, "Items:", Color::BRIGHT_WHITE);
    inventory->writeText(2, 2, "- Rusty Sword", Color::YELLOW);
    inventory->writeText(3, 2, "- Health Potion x3", Color::BRIGHT_RED);
    inventory->writeText(4, 2, "- Old Map", Color::CYAN);
    inventory->drawLine(5, 0, inventory->getContentWidth(), '-', true);
    inventory->writeText(6, 2, "Equipment:", Color::BRIGHT_WHITE);
    inventory->writeText(7, 2, "Head: None", Color::BRIGHT_BLACK);
    inventory->writeText(8, 2, "Body: Leather Armor", Color::GREEN);
    inventory->writeText(9, 2, "Weapon: Dagger", Color::BRIGHT_BLUE);
    
    // 3. Stats panel
    auto stats = std::make_shared<Panel>(2, 19, 50, 8, "Character Stats");
    stats->setBorderColor(Color::BRIGHT_CYAN);
    stats->writeText(0, 2, "HP: 85/100  [#########-]", Color::BRIGHT_RED);
    stats->writeText(1, 2, "MP: 45/60   [#######---]", Color::BRIGHT_BLUE);
    stats->writeText(2, 2, "STR: 15  DEX: 12  INT: 10", Color::WHITE);
    stats->drawLine(3, 0, stats->getContentWidth(), '=', true);
    stats->writeText(4, 2, "Level: 5  XP: 450/500", Color::BRIGHT_GREEN);
    stats->writeText(5, 2, "Gold: 250", Color::YELLOW);
    
    // 4. Message log panel
    auto messageLog = std::make_shared<Panel>(54, 19, 30, 8, "Messages");
    messageLog->setBorderColor(Color::BRIGHT_MAGENTA);
    messageLog->writeText(0, 1, "> You enter a room", Color::WHITE);
    messageLog->writeText(1, 1, "> It's dark here...", Color::BRIGHT_BLACK);
    messageLog->writeText(2, 1, "> You found a key!", Color::BRIGHT_YELLOW);
    messageLog->writeText(3, 1, "> Enemy appeared!", Color::BRIGHT_RED);
    
    // Add all panels to manager
    manager.addPanel(gameView);
    manager.addPanel(inventory);
    manager.addPanel(stats);
    manager.addPanel(messageLog);
    
    // Render all panels
    manager.renderAll();
    
    // Wait for user input
    std::cout << std::endl;
    TerminalUtils::moveCursor(28, 0);
    std::cout << "Full framework demonstration - Press Enter to exit...";
    std::cout.flush();
    std::cin.get();
    
    manager.cleanup();
    return 0;
}
