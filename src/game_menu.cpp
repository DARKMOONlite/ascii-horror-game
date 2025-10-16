#include <game_menu.hpp>


DisplayHUD::DisplayHUD(): 
screen(ScreenInteractive::Fullscreen())
{
    components.push_back( Renderer([] { return text("middle") | center; }));
    components.push_back( Renderer([] { return text("Left") | center; }));
    components.push_back( Renderer([] { return text("right") | center; }));
    components.push_back( Renderer([] { return text("top") | center; }));
    components.push_back( Renderer([] { return text("bottom") | center; }));
    top_level_component = components.at(0);
    top_level_component = ResizableSplitLeft(components.at(1), top_level_component, &left_size);
    top_level_component = ResizableSplitRight(components.at(2), top_level_component, &right_size);
    top_level_component = ResizableSplitTop(components.at(3), top_level_component, &top_size);
    top_level_component = ResizableSplitBottom(components.at(4), top_level_component, &bottom_size);
    renderer = Renderer(top_level_component,[&]{return top_level_component->Render()|border;});
}

void DisplayHUD::loop(){
    screen.Loop(renderer);
}