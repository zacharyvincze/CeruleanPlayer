#pragma once
#include <ncurses.h>

#include "extensions/extension_manager.h"
#include "player.h"

class Window
{
    Player &_player;
    int _rows, _cols, _center_row, _center_col;
    WINDOW *_win;

    std::string m_songTitle;
    std::string m_infoSection;
    ExtensionManager &m_extensionManager;

  public:
    Window(Player &player, ExtensionManager &extensionManager);
    void draw();
    int get_input();

    inline void set_song_title(const std::string &songTitle)
    {
        m_songTitle = songTitle;
    }
    inline std::string get_song_title()
    {
        return m_songTitle;
    }
    inline void set_info_section(const std::string &infoSection)
    {
        m_infoSection = infoSection;
    }
    inline std::string get_info_section()
    {
        return m_infoSection;
    }

    inline WINDOW *get_window()
    {
        return _win;
    }
};