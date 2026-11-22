cmake_minimum_required(VERSION 3.14)
project(Lerin CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
  GIT_TAG v7.0.3
)
FetchContent_MakeAvailable(ftxui)

add_executable(Lerin 
main.cpp
src/Engine/GameEngine.h
src/Engine/GameEngine.cpp
src/Engine/Level.h
src/Engine/Level.cpp
src/Engine/Player.h
src/UI/GameUI.h
src/UI/GameUI.cpp
src/Engine/Inventory.h
src/Engine/Item.h
src/Engine/Inventory.cpp
src/Engine/Item.cpp
src/Items/Sword.h
src/Items/Sword.cpp
src/Engine/Commands.h
src/Engine/Commands.cpp
src/Items/Potion.h
src/Items/Potion.cpp
src/Engine/Enemy.h
src/Engine/Enemy.cpp
)

target_link_libraries(Lerin PRIVATE
  ftxui::screen
  ftxui::dom
  ftxui::component
)
