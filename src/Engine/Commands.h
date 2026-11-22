#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>
#include "GameEngine.h"

class Commands {
    public:
        static std::string execute(GameEngine& engine, const std::string& input);
};

#endif