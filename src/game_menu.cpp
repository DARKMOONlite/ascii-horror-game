#include <game_menu.hpp>

#include <thread>
#include <chrono>
using namespace std::chrono_literals;

DisplayHUD::DisplayHUD(): 
screen(ScreenInteractive::Fullscreen())
{
    top_level_component = menu.Top_Component();


    renderer = Renderer(top_level_component,[this](){
        return(this->render());
    });
}

void DisplayHUD::loop(){
    // Start a background thread to update the menu content
    std::thread update_thread([this]() {this->updateScreen();});
    // Detach the thread so it runs independently
    update_thread.detach();
    
    // Start the main UI loop
    screen.Loop(renderer);
}

Element DisplayHUD::render(){
    // Simply return the rendered component without any delays
    //! Can add stuff here if necessary in the future.
    return top_level_component->Render();
}

void DisplayHUD::updateScreen(){
int i = 0;
        while (true) {
            std::this_thread::sleep_for(1000ms);
            
            // Update the menu text
            menu.inventory_text = "inventory size : " 
            + std::to_string(menu.inventory_box.y_max-menu.inventory_box.y_min)+"   " 
            + std::to_string(menu.inventory_box.x_max-menu.inventory_box.x_min);
            
            menu.action_text = "action size : " 
            + std::to_string(menu.action_box.y_max-menu.action_box.y_min)+"   " 
            + std::to_string(menu.action_box.x_max-menu.action_box.x_min);


            auto ascii = generator.generate_ascii_from_file("images/tree.jpg", menu.screen_box.x_max-menu.screen_box.x_min,menu.screen_box.y_max-menu.screen_box.y_min);
            std::stringstream ss;
            ss << ascii;
            menu.screen_text = ss.str();


            i++;
            
            // Trigger a screen refresh
            screen.PostEvent(Event::Custom);
        }
}