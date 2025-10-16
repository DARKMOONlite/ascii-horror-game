#ifndef GAME_MENU_HPP
#define GAME_MENU_HPP
#include <memory>
#include "ftxui/component/captured_mouse.hpp"      // for ftxui
#include "ftxui/component/component.hpp"           // for Menu
#include "ftxui/component/component_options.hpp"   // for MenuOption
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
using namespace ftxui;

class DisplayHUD{
public:
    DisplayHUD();


    void loop();



private:

    std::vector<Component> components;
    ScreenInteractive screen;
    Component top_level_component;
    Component renderer;
    
    // Size variables for resizable splits (must be class members)
    int left_size = 20;
    int right_size = 20;
    int top_size = 10;
    int bottom_size = 10;

};



#endif