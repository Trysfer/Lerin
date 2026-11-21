#ifndef GAMEUI_H
#define GAMEUI_H
#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include "../Engine/GameEngine.h"

class GameUI{
    private:
        GameEngine& engine;
        ftxui::App screen;

        int current_GameStage = 0;
        int menu_chosen;
        std::string command_value;
        std::string logs;

        ftxui::Component create_menu_view();
        ftxui::Component create_game_view();
    public:
        GameUI(GameEngine& ge);
        void run();
};

#endif