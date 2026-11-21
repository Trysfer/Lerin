#include <iostream>
#include "src/UI/GameUI.h"
#include "src/Engine/GameEngine.h"


int main() {
    GameEngine ge;
    GameUI ui(ge);
    ui.run();
    std::cout<<"The program has been closed";
    return 0;
}