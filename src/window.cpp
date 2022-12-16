#include "window.h"

#include <ncurses.h>

#include <string>

#include "metadata.h"

Window::Window(Player &player, ExtensionManager &extensionManager)
    : _player(player), m_extensionManager(extensionManager)
{
    initscr();
    cbreak();
    noecho();
    getmaxyx(stdscr, _rows, _cols);
    _center_col = _cols / 2;
    _center_row = _rows / 2;
    _win = newwin(10, 40, _center_row - 5, _center_col - 20);
    curs_set(0);
    nodelay(_win, true);
    keypad(_win, true);

    // Initialize color pairs
    start_color();
    use_default_colors();
    init_pair(1, COLOR_CYAN, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_WHITE, COLOR_WHITE);
}

void Window::draw()
{
    werase(_win);
    box(_win, 0, 0);

    m_songTitle = _player.get_current_song();

    m_extensionManager.on_window_draw(*this);

    wattron(_win, COLOR_PAIR(1));
    mvwprintw(_win, 0, 1, "CeruleanPlayer v" CERULEAN_PLAYER_VERSION " (FMOD v%i)", _player.get_fmod_version());
    wattroff(_win, COLOR_PAIR(1));
    mvwprintw(_win, 2, 2, "Now Playing:");
    wattron(_win, COLOR_PAIR(2));
    mvwprintw(_win, 3, 2, "%s", m_songTitle.c_str());
    wattroff(_win, COLOR_PAIR(2));

    // Info section (for any general type of information)
    mvwprintw(_win, 5, 2, "%s", m_infoSection.c_str());

    // Progress bar
    unsigned int current_position = _player.get_current_position();
    unsigned int song_length = _player.get_song_length();
    mvwprintw(_win, 6, 2, "%i:%02i/%i:%02i", (int)current_position / 1000 / 60, (int)current_position / 1000 % 60,
              (int)song_length / 1000 / 60, (int)song_length / 1000 % 60);

    mvwprintw(_win, 7, 2, "[");
    wattron(_win, COLOR_PAIR(3));
    for (int i = 0; i < (current_position / (float)song_length) * 34; i++)
    {
        mvwaddch(_win, 7, 3 + i, ACS_CKBOARD);
    }
    wattroff(_win, COLOR_PAIR(3));
    mvwprintw(_win, 7, 37, "]");
    mvwprintw(_win, 9, 1, "Developed by " DEVELOPER_NAME);

    wrefresh(_win);
}

int Window::get_input()
{
    return wgetch(_win);
}