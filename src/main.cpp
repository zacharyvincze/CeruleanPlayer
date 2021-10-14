#include <ncurses.h>
#include <string.h>

#include <iostream>

#include "cerulean_player.h"
#include "helpers.h"

// Parse command line options and modify PlayerOptions accordingly
PlayerOptions parseOptions(int argc, char** argv) {
    PlayerOptions options;

    for (int i = 1; i < argc; i++) {
        if (helper::isOption(argv[i])) {
            if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--shuffle") == 0)
                options.shuffle = true;
        } else {
            options.filepath = argv[i];
        }
    }

    return options;
}

int main(int argc, char** argv) {
    PlayerOptions options = parseOptions(argc, argv);

    if (argc < 2 || options.filepath == "") {
        std::cerr << "Usage: cerulean_player <playlist/song filepath>\n";
        return -1;
    }

    Player player(options);
    Window window(player);
    CeruleanPlayer ceruleanPlayer(player, window);

    ceruleanPlayer.run();

    return 0;
}