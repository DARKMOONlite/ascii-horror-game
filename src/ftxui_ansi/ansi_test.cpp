#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "color_utils.hpp"
#include "ascii_image.hpp"
#include "ascii_generator.hpp"
#include "ansi_text.hpp"
#include <ansi_paragraph.hpp>
#include <iostream>
#include <sstream>
using namespace ftxui;

int main() {
    auto screen = ScreenInteractive::Fullscreen();
    
    auto generator = AsciiGenerator();
    auto image = generator.generate_ascii_from_file("images/tree.jpg",100,100);
    std::stringstream ss;
    ss << image;
    
    
    auto component = Renderer([&] {
        return vbox({
            ansi_paragraph(ss.str())
        }) | border;
    });
    
    screen.Loop(component);
    
    return 0;
}
