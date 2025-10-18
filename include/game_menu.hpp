#ifndef GAME_MENU_HPP
#define GAME_MENU_HPP
#include <memory>
#include "ftxui/component/captured_mouse.hpp"      // for ftxui
#include "ftxui/component/component.hpp"           // for Menu
#include "ftxui/component/component_options.hpp"   // for MenuOption
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"                  // for color, bgcolor, etc.
#include <ascii_generator.hpp>
#include <ansi_paragraph.hpp>
#include "ansi_text.hpp"
using namespace ftxui;



struct MenuStructure{

public:
    Component Top_Component(){
        return(top_level);
    }    MenuStructure():
    inventory_renderer(Renderer([this] { 
        return ansi_paragraph(inventory_text) | reflect(inventory_box); 
    })),
    screen_renderer( Renderer([this] { 
        return ansi_paragraph(screen_text) | reflect(screen_box); 
    })),
    action_renderer(Renderer([this] { 
        return ansi_paragraph(action_text) | reflect(action_box); 
    }))
    {
    top_level = screen_renderer;
    top_level = ResizableSplitLeft(action_renderer,top_level,&left_size);
    top_level = ResizableSplitBottom(inventory_renderer,top_level,&bottom_size);
    }
public:
    Component inventory_renderer;
    Box inventory_box;
    Component screen_renderer;
    Box screen_box;
    Component action_renderer;
    Box action_box;
    Component top_level;
public:
std::string inventory_text = "inventory\n- items";
std::string screen_text = "screen\n- images";
std::string action_text = "action\n- menu";
int left_size = 20;
int bottom_size = 10;


};

class DisplayHUD{
public:
    DisplayHUD();


    void loop();
    Element render();
    void updateScreen();


private:

    MenuStructure menu;
    ScreenInteractive screen;
    Component top_level_component;
    Component renderer;
    AsciiGenerator generator;
    
    // Size variables for resizable splits (must be class members)


};



#endif