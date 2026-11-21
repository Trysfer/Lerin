#include "GameUI.h"
#include <ftxui/dom/elements.hpp>

GameUI::GameUI(GameEngine& ge): engine(ge), screen(ftxui::App::Fullscreen()){}

ftxui::Component GameUI::create_menu_view(){
    static std::vector<std::string> menu_entries = {"New Game", "Exit"};
    ftxui::MenuOption menu_options;
    menu_options.on_enter = [&] {
        if(menu_chosen == 0){
            current_GameStage = 1;
        }else if(menu_chosen == 1){
            screen.Exit();
        }
    };
    ftxui::Component menu = Menu(&menu_entries, &menu_chosen, menu_options);
    return Renderer(menu, [this,menu] {
        return ftxui::vbox({
            ftxui::hbox({
                ftxui::vbox({
                    ftxui::text("██╗     ███████╗██████╗ ██╗███╗   ██╗"),
                    ftxui::text("██║     ██╔════╝██╔══██╗██║████╗  ██║"),
                    ftxui::text("██║     █████╗  ██████╔╝██║██╔██╗ ██║"),
                    ftxui::text("██║     ██╔══╝  ██╔══██╗██║██║╚██╗██║"),
                    ftxui::text("███████╗███████╗██║  ██║██║██║ ╚████║"),
                    ftxui::text("╚══════╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝")
                })
            }) | ftxui::center | size(ftxui::HEIGHT, ftxui::EQUAL, 10),
            ftxui::hbox({
                ftxui::text("")   
            }) | size(ftxui::HEIGHT, ftxui::EQUAL, 10),
            ftxui::hbox({
                menu->Render()
            }) |ftxui::hcenter
        })| ftxui::borderDouble;
    });
}
ftxui::Component GameUI::create_game_view(){
    ftxui::InputOption LOG_options;
    LOG_options.on_enter = [this] {
        command_value.erase(0, command_value.find_first_not_of(" \t\r\n"));
        auto last = command_value.find_last_not_of(" \t\r\n");
        if (last != std::string::npos) {
            command_value.erase(last + 1);
        }
        try {
            if (command_value == "w")      logs = "\n--> " + engine.move_player(0, -1);
            else if (command_value == "s") logs = "\n--> " + engine.move_player(0, 1);
            else if (command_value == "a") logs = "\n--> " + engine.move_player(-1, 0);
            else if (command_value == "d") logs = "\n--> " + engine.move_player(1, 0);
            else                           logs = "\n--> Unknown command: " + command_value;
        } catch (const std::exception& e) {
            logs = std::string("\n--> ") + e.what();
        }
        command_value.clear();
    };
    ftxui::Component command_input = Input(&command_value, "", LOG_options);
    return Renderer(command_input,[this,command_input]{
        ftxui::Elements map_rows;
        const auto& grid = engine.get_current_level().get_grid();

        for (int y = 0; y < static_cast<int>(grid.size()); ++y) {
            std::string row = grid[y];
            if (y == engine.get_player().get_y()) {
                row[engine.get_player().get_x()] = '@';
            }
            map_rows.push_back(ftxui::text(row));
        }
        auto game_bar = ftxui::vbox({
            ftxui::vbox(std::move(map_rows)) | ftxui::center | ftxui::flex
        }) | ftxui::border | ftxui::flex;
        auto inventory_bar = ftxui::vbox({
            ftxui::text("Inventory:")
        }) | ftxui::border | size(ftxui::WIDTH,ftxui::EQUAL, 30);
        auto log_bar = ftxui::vbox({
            ftxui::text("LOG:"+logs),
            hbox(ftxui::text("->>"),command_input -> Render())
        }) | ftxui::border | size(ftxui::HEIGHT,ftxui::EQUAL,6);
        return ftxui::vbox({
            ftxui::hbox({
                game_bar,
                inventory_bar
            }) | ftxui::flex,
            log_bar
        })| ftxui::borderDouble;
    });
}
void GameUI::run(){
    auto menu_view = GameUI::create_menu_view();
    auto game_view = GameUI::create_game_view();
    auto main_container = ftxui::Container::Tab({
        menu_view,
        game_view
    }, &current_GameStage);
    screen.Loop(main_container);
}