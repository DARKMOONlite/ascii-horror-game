#include "PanelManager.h"
#include "Panel.h"
#include "ASCIIVideo.h"
#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>

using namespace ASCIIDisplay;

int main() {
    PanelManager manager;
    manager.initialize();
    
    // Create a panel to display the video
    auto videoPanel = std::make_shared<Panel>(2, 2, 42, 14, "ASCII Video Demo");
    videoPanel->setBorderColor(Color::BRIGHT_MAGENTA);
    
    // Create a simple animation - a bouncing ball
    ASCIIVideo video;
    
    // Create frames for the animation
    for (int frame = 0; frame < 20; ++frame) {
        std::vector<std::string> frameLines(10, std::string(38, ' '));
        
        // Calculate ball position (bouncing vertically)
        int ballY = frame < 10 ? frame : 20 - frame - 1;
        int ballX = 19; // Center horizontally
        
        // Draw ball
        if (ballY >= 0 && ballY < 10) {
            frameLines[ballY][ballX] = 'O';
            if (ballX > 0) frameLines[ballY][ballX - 1] = '(';
            if (ballX < 37) frameLines[ballY][ballX + 1] = ')';
        }
        
        // Draw ground
        for (int x = 0; x < 38; ++x) {
            frameLines[9][x] = '=';
        }
        
        auto image = std::make_shared<ASCIIImage>();
        image->loadFromText(frameLines);
        
        // Color the ball
        for (int y = 0; y < image->getHeight(); ++y) {
            for (int x = 0; x < image->getWidth(); ++x) {
                char ch = image->getChar(y, x);
                if (ch == 'O' || ch == '(' || ch == ')') {
                    image->setPixel(y, x, ch, Color::BRIGHT_RED);
                } else if (ch == '=') {
                    image->setPixel(y, x, ch, Color::BRIGHT_GREEN);
                }
            }
        }
        
        video.addFrame(image);
    }
    
    video.setFrameRate(10.0);
    
    // Add panel to manager
    manager.addPanel(videoPanel);
    
    // Animation loop
    std::cout << std::endl;
    TerminalUtils::moveCursor(20, 0);
    std::cout << "Playing animation... Press Ctrl+C to exit";
    std::cout.flush();
    
    for (int i = 0; i < 100; ++i) {  // Play for 100 frames (5 loops)
        videoPanel->clear();
        video.renderToPanel(*videoPanel, 1, 1);
        manager.renderAll();
        
        video.nextFrame();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    // Wait a bit before cleanup
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    manager.cleanup();
    return 0;
}
