#ifndef ANSI_TEXT_HPP
#define ANSI_TEXT_HPP

#include "ftxui/dom/node.hpp"                      // for Node
#include "ftxui/dom/elements.hpp"                  // for Element
#include "ftxui/screen/screen.hpp"                 // for Screen
#include "ftxui/dom/selection.hpp"                 // for Selection
#include "ftxui/screen/box.hpp"                    // for Box
#include "ftxui/screen/string.hpp"                 // for Utf8ToGlyphs, string_width
#include <string>
#include <sstream>
#include <vector>



namespace ftxui {

// Structure to hold parsed ANSI text with color information
struct AnsiSegment {
    std::string text;
    std::string ansi_code;  // The ANSI escape sequence
};

class AnsiText : public Node {
public:
    explicit AnsiText(std::string text);

    void ComputeRequirement() override;
    void Select(Selection& selection) override;
    void Render(Screen& screen) override;
private:
    void ParseAnsiText();
    static int CalculateVisibleWidth(const std::string& text);// Calculate visible width (excluding ANSI escape codes
    static std::string StripAnsiCodes(const std::string& text);// Strip ANSI codes from text

    std::string text_;
    std::vector<AnsiSegment> segments_;
    int visible_width_;
    bool has_selection = false;
    int selection_start_ = 0;
    int selection_end_ = -1;
    

};

// Factory function to create an ANSI text element
Element ansi_text(std::string text);

}  // namespace ftxui

#endif