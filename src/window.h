#pragma once
#include <ncurses.h>

#include "extensions/extension_manager.h"
#include "player.h"

class Window {
    Player& _player;
    int _rows, _cols, _center_row, _center_col;
    WINDOW* _win;

    std::string m_songTitle;
    ExtensionManager& m_extensionManager;

   public:
    Window(Player& player, ExtensionManager& extensionManager);
    void draw();
    int get_input();

    void set_song_title(const std::string& songTitle) { m_songTitle = songTitle; }
    std::string get_song_title() { return m_songTitle; }

    inline WINDOW* get_window() { return _win; }
};