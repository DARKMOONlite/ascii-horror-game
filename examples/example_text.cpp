#include "PanelManager.h"
#include "Panel.h"
#include "ASCIILetter.h"
#include "ASCIIWord.h"
#include "ASCIIParagraph.h"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

using namespace ASCIIDisplay;

int main() {
    PanelManager manager;
    manager.initialize();
    
    // Create a panel for displaying ASCII text
    auto textPanel = std::make_shared<Panel>(2, 2, 120, 50, "ASCII Text Demo");
    textPanel->setBorderColor(Color::BRIGHT_CYAN);
    manager.addPanel(textPanel);
    
    std::cout << "\n=== ASCII Letter Demo ===\n";
    
    // Demo 1: Single ASCII Letter
    textPanel->clear();
    textPanel->writeText(0, 1, "Demo 1: Single ASCII Letter (scale 2)", Color::BRIGHT_YELLOW);
    
    ASCIILetter letterA('A', 2);
    letterA.setColor(Color::BRIGHT_GREEN);
    
    auto letterLines = letterA.getRenderedLines();
    for (size_t i = 0; i < letterLines.size(); ++i) {
        textPanel->writeText(2 + i, 2, letterLines[i], letterA.getColor());
    }
    
    manager.renderAll();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // Demo 2: ASCII Letter with Bold Effect
    textPanel->clear();
    textPanel->writeText(0, 1, "Demo 2: ASCII Letter with BOLD effect (scale 3)", Color::BRIGHT_YELLOW);
    
    ASCIILetter letterB('B', 3);
    letterB.setColor(Color::BRIGHT_RED);
    letterB.setEffect(TextEffect::BOLD);
    
    letterLines = letterB.getRenderedLines();
    for (size_t i = 0; i < letterLines.size(); ++i) {
        textPanel->writeText(2 + i, 2, letterLines[i], letterB.getColor());
    }
    
    manager.renderAll();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // Demo 3: ASCII Letter with Italic Effect
    textPanel->clear();
    textPanel->writeText(0, 1, "Demo 3: ASCII Letter with ITALIC effect (scale 3)", Color::BRIGHT_YELLOW);
    
    ASCIILetter letterC('C', 3);
    letterC.setColor(Color::BRIGHT_MAGENTA);
    letterC.setEffect(TextEffect::ITALIC);
    
    letterLines = letterC.getRenderedLines();
    for (size_t i = 0; i < letterLines.size(); ++i) {
        textPanel->writeText(2 + i, 2, letterLines[i], letterC.getColor());
    }
    
    manager.renderAll();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "\n=== ASCII Word Demo ===\n";
    
    // Demo 4: ASCII Word
    textPanel->clear();
    textPanel->writeText(0, 1, "Demo 4: ASCII Word (scale 2)", Color::BRIGHT_YELLOW);
    
    ASCIIWord word("HELLO", 2);
    word.setColor(Color::BRIGHT_BLUE);
    
    auto wordLines = word.renderLines();
    for (size_t i = 0; i < wordLines.size(); ++i) {
        textPanel->writeText(2 + i, 2, wordLines[i], word.getColor());
    }
    
    manager.renderAll();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // Demo 5: ASCII Word with Effects
    textPanel->clear();
    textPanel->writeText(0, 1, "Demo 5: ASCII Word with BOLD effect (scale 2)", Color::BRIGHT_YELLOW);
    
    ASCIIWord word2("WORLD", 2);
    word2.setColor(Color::BRIGHT_GREEN);
    word2.setEffect(TextEffect::BOLD);
    
    wordLines = word2.renderLines();
    for (size_t i = 0; i < wordLines.size(); ++i) {
        textPanel->writeText(2 + i, 2, wordLines[i], word2.getColor());
    }
    
    manager.renderAll();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "\n=== ASCII Paragraph Demo ===\n";
    
    // Demo 6: ASCII Paragraph
    textPanel->clear();
    textPanel->writeText(0, 1, "Demo 6: ASCII Paragraph (scale 1)", Color::BRIGHT_YELLOW);
    
    ASCIIParagraph para("WELCOME TO ASCII HORROR", 1);
    para.setColor(Color::BRIGHT_RED);
    para.setMaxWidth(100);
    para.setAlignment(TextAlign::LEFT);
    
    auto paraLines = para.renderLines();
    for (size_t i = 0; i < paraLines.size() && (i + 2) < textPanel->getContentHeight(); ++i) {
        textPanel->writeText(2 + i, 2, paraLines[i], para.getColor());
    }
    
    manager.renderAll();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // Demo 7: Centered Paragraph
    textPanel->clear();
    textPanel->writeText(0, 1, "Demo 7: Centered ASCII Paragraph (scale 1)", Color::BRIGHT_YELLOW);
    
    ASCIIParagraph para2("HORROR GAME", 2);
    para2.setColor(Color::BRIGHT_MAGENTA);
    para2.setMaxWidth(100);
    para2.setAlignment(TextAlign::CENTER);
    
    paraLines = para2.renderLines();
    for (size_t i = 0; i < paraLines.size() && (i + 2) < textPanel->getContentHeight(); ++i) {
        textPanel->writeText(2 + i, 2, paraLines[i], para2.getColor());
    }
    
    manager.renderAll();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // Demo 8: Multiple effects
    textPanel->clear();
    textPanel->writeText(0, 1, "Demo 8: ASCII Text with Multiple Scales", Color::BRIGHT_YELLOW);
    
    // Show different scales
    int currentRow = 2;
    for (int scale = 1; scale <= 3; ++scale) {
        ASCIIWord scaleDemo("SCALE" + std::to_string(scale), scale);
        scaleDemo.setColor(scale == 1 ? Color::BRIGHT_GREEN : 
                          scale == 2 ? Color::BRIGHT_CYAN : Color::BRIGHT_YELLOW);
        
        auto lines = scaleDemo.renderLines();
        for (size_t i = 0; i < lines.size() && (currentRow + i) < textPanel->getContentHeight(); ++i) {
            textPanel->writeText(currentRow + i, 2, lines[i], scaleDemo.getColor());
        }
        currentRow += lines.size() + 1;
    }
    
    manager.renderAll();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    // Demo 9: Word wrapping
    textPanel->clear();
    textPanel->writeText(0, 1, "Demo 9: Word Wrapping with Small Width (scale 1)", Color::BRIGHT_YELLOW);
    
    ASCIIParagraph para3("WELCOME TO THE DARK WORLD OF ASCII", 1);
    para3.setColor(Color::BRIGHT_WHITE);
    para3.setMaxWidth(40); // Small width to force wrapping
    para3.setAlignment(TextAlign::LEFT);
    
    paraLines = para3.renderLines();
    for (size_t i = 0; i < paraLines.size() && (i + 2) < textPanel->getContentHeight(); ++i) {
        textPanel->writeText(2 + i, 2, paraLines[i], para3.getColor());
    }
    
    manager.renderAll();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    // Demo 10: Final demo with all features
    textPanel->clear();
    textPanel->writeText(0, 1, "Demo 10: Complete Feature Demo", Color::BRIGHT_YELLOW);
    
    ASCIIParagraph finalPara("ASCII TEXT", 2);
    finalPara.setColor(Color::BRIGHT_CYAN);
    finalPara.setEffect(TextEffect::BOLD);
    finalPara.setMaxWidth(100);
    finalPara.setAlignment(TextAlign::CENTER);
    
    paraLines = finalPara.renderLines();
    for (size_t i = 0; i < paraLines.size() && (i + 2) < textPanel->getContentHeight(); ++i) {
        textPanel->writeText(2 + i, 2, paraLines[i], finalPara.getColor());
    }
    
    manager.renderAll();
    
    // Wait for user input
    std::cout << std::endl;
    TerminalUtils::moveCursor(55, 0);
    std::cout << "Press Enter to exit...";
    std::cout.flush();
    std::cin.get();
    
    manager.cleanup();
    
    std::cout << "\n\nAll demos completed!\n";
    std::cout << "Features demonstrated:\n";
    std::cout << "- ASCIILetter: Single large ASCII characters\n";
    std::cout << "- ASCIIWord: Multiple letters forming words\n";
    std::cout << "- ASCIIParagraph: Word wrapping and alignment\n";
    std::cout << "- Text effects: BOLD, ITALIC\n";
    std::cout << "- Scaling: 1x, 2x, 3x sizes\n";
    std::cout << "- Alignment: LEFT, CENTER, RIGHT\n";
    std::cout << "- Color support for all text elements\n";
    
    return 0;
}
