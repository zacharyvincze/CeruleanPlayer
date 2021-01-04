#include <ncurses.h>

#include <iostream>

#include "cerulean_player.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: cerulean_player <playlist/song filepath>\n";
        return -1;
    }

    Player player(argv[1]);
    Window window(player);
    CeruleanPlayer ceruleanPlayer(player, window);

    ceruleanPlayer.run();

    return 0;
}