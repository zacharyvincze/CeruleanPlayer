#include "window.h"

#include <ncurses.h>

#include <string>

Window::Window(Player& player) : _player(player) {
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
    // start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
}

void Window::setPlayerVersion(unsigned int major, unsigned int minor) {
    version_major = major;
    version_minor = minor;
}

void Window::draw() {
    werase(_win);
    box(_win, 0, 0);
    wattron(_win, COLOR_PAIR(1));
    mvwprintw(_win, 0, 1, "CeruleanPlayer v%i.%i", version_major,
              version_minor);
    wattroff(_win, COLOR_PAIR(1));
    mvwprintw(_win, 2, 2, "Now Playing:");
    wattron(_win, COLOR_PAIR(2));
    mvwprintw(_win, 3, 2, "%s", _player.getCurrentSong().c_str());
    wattroff(_win, COLOR_PAIR(2));

    float pitch = _player.getPitch();
    if (pitch != 1) {
        std::string modifier;
        if (pitch > 1.0f) modifier = "+";
        mvwprintw(_win, 6, 25, "Pitch: %s%.2f", modifier.c_str(), pitch - 1.0f);
    }

    // Progress bar
    unsigned int current_position = _player.getCurrentPosition();
    unsigned int song_length = _player.getSongLength();
    mvwprintw(_win, 6, 2, "%i:%02i/%i:%02i", (int)current_position / 1000 / 60,
              (int)current_position / 1000 % 60, (int)song_length / 1000 / 60,
              (int)song_length / 1000 % 60);

    mvwprintw(_win, 7, 2, "[");
    wattron(_win, COLOR_PAIR(3));
    for (int i = 0; i < (current_position / (float)song_length) * 34; i++) {
        mvwaddch(_win, 7, 3 + i, ACS_CKBOARD);
    }
    wattroff(_win, COLOR_PAIR(3));
    mvwprintw(_win, 7, 37, "]");
    mvwprintw(_win, 9, 1, "Developed by Zachary Vincze");

    wrefresh(_win);
}

int Window::getInput() { return wgetch(_win); }