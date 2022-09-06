#pragma once
#include <ncurses.h>

#include "Extensions/ExtensionManager.h"
#include "Player.h"

class Window {
    Player& _player;
    int _rows, _cols, _center_row, _center_col;
    WINDOW* _win;

    std::string m_songTitle;
    ExtensionManager& m_extensionManager;

   public:
    Window(Player& player, ExtensionManager& extensionManager);
    void Draw();
    int GetInput();

    void SetSongTitle(const std::string& songTitle) { m_songTitle = songTitle; }
    std::string GetSongTitle() { return m_songTitle; }

    inline WINDOW* GetWindow() { return _win; }
};