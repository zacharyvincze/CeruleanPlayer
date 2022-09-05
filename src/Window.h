#pragma once
#include <ncurses.h>

#include "Extensions/ExtensionManager.h"
#include "Player.h"

class Window {
    Player& _player;
    int _rows, _cols, _center_row, _center_col;
    WINDOW* _win;

   public:
    Window(Player& player);
    void Draw(ExtensionManager& extentionManager);
    int GetInput();
    inline WINDOW* GetWindow() { return _win; }
};