#include "ansi_text.hpp"
#include <regex>
#include <memory>
#include <algorithm>

namespace ftxui {

AnsiText::AnsiText(std::string text) : text_(std::move(text)) {
    ParseAnsiText();
    visible_width_ = CalculateVisibleWidth(text_);
}

void AnsiText::ParseAnsiText() {
    segments_.clear();
    
    std::string current_text;
    std::string current_ansi;
    bool in_escape = false;
    std::string escape_buffer;
    
    for (size_t i = 0; i < text_.length(); ++i) {
        char c = text_[i];
        
        // Detect start of ANSI escape sequence (\033 or \x1b)
        if (c == '\033' || c == '\x1b') {
            // Save any accumulated text with current ANSI code
            if (!current_text.empty()) {
                segments_.push_back({current_text, current_ansi});
                current_text.clear();
            }
            
            in_escape = true;
            escape_buffer = std::string(1, c);
            continue;
        }
        
        // If we're in an escape sequence, accumulate it
        if (in_escape) {
            escape_buffer += c;
            // ANSI SGR codes end with 'm'
            if (c == 'm') {
                current_ansi = escape_buffer;
                in_escape = false;
                escape_buffer.clear();
            }
            continue;
        }
        
        // Regular character - add to current text
        if (c == '\n') {
            // Don't include newlines (AnsiText is single-line like Text)
            continue;
        }
        current_text += c;
    }
    
    // Save any remaining text
    if (!current_text.empty()) {
        segments_.push_back({current_text, current_ansi});
    }
}

int AnsiText::CalculateVisibleWidth(const std::string& text) {
    std::string stripped = StripAnsiCodes(text);
    // Remove newlines for width calculation
    stripped.erase(std::remove(stripped.begin(), stripped.end(), '\n'), stripped.end());
    return string_width(stripped);
}

std::string AnsiText::StripAnsiCodes(const std::string& text) {
    // Remove ANSI escape sequences: \033[...m or \x1b[...m
    std::regex ansi_regex(R"(\x1b\[[0-9;]*m|\033\[[0-9;]*m)");
    return std::regex_replace(text, ansi_regex, "");
}

void AnsiText::ComputeRequirement() {
    requirement_.min_x = visible_width_;
    requirement_.min_y = 1;
    has_selection = false;
}

void AnsiText::Select(Selection& selection) {
    if (Box::Intersection(selection.GetBox(), box_).IsEmpty()) {
        return;
    }

    const Selection selection_saturated = selection.SaturateHorizontal(box_);

    has_selection = true;
    selection_start_ = selection_saturated.GetBox().x_min;
    selection_end_ = selection_saturated.GetBox().x_max;

    std::stringstream ss;
    int x = box_.x_min;
    
    // Only select visible characters
    std::string visible = StripAnsiCodes(text_);
    for (const auto& cell : Utf8ToGlyphs(visible)) {
        if (cell == "\n") {
            continue;
        }
        if (selection_start_ <= x && x <= selection_end_) {
            ss << cell;
        }
        x++;
    }
    selection.AddPart(ss.str(), box_.y_min, selection_start_, selection_end_);
}

void AnsiText::Render(Screen& screen) {
    int x = box_.x_min;
    const int y = box_.y_min;

    if (y > box_.y_max) {
        return;
    }

    // Render each segment with its ANSI code
    for (const auto& segment : segments_) {
        // Convert segment text to glyphs
        for (const auto& cell : Utf8ToGlyphs(segment.text)) {
            if (x > box_.x_max) {
                return;  // Don't render beyond bounds
            }
            
            auto& pixel = screen.PixelAt(x, y);
            
            // Set the character
            pixel.character = cell;
            
            // Apply ANSI color by embedding it in the character string
            // When FTXUI outputs to terminal, it will preserve the ANSI codes
            if (!segment.ansi_code.empty()) {
                // Embed ANSI code with character
                pixel.character = segment.ansi_code + cell + "\033[0m";
            }
            
            // Handle selection
            if (has_selection) {
                auto selectionTransform = screen.GetSelectionStyle();
                if ((x >= selection_start_) && (x <= selection_end_)) {
                    selectionTransform(pixel);
                }
            }

            ++x;
        }
    }
}

Element ansi_text(std::string text) {
    return std::make_shared<AnsiText>(std::move(text));
}

}  // namespace ftxui
