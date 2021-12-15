#include <ncurses.h>
#include <string.h>

#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include "cerulean_player.h"
#include "helpers.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: cerulean_player <playlist/song filepath>\n";
        return -1;
    }

    int option = 0;

    PlayerOptions options;
    printf("Something is wrong...\n");

    // Parse command line arguments
    while ((option = getopt(argc, argv, "s")) != -1) {
        switch (option) {
            case 's':
                options.shuffle = true;
                break;
            default:
                printf("Usage: cerulean-player <playlist/song filepath>\n");
        }
    }

    // Obtain path to music
    for (; optind < argc; optind++) {
        options.filepath = argv[optind];
    }

    Player player(options);
    Window window(player);
    CeruleanPlayer ceruleanPlayer(player, window);

    ceruleanPlayer.run();

    return 0;
}