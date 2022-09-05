#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#include "CeruleanPlayer.h"
#include "Helpers.h"
#include "Metadata.h"

void PrintVersionNumber() {
    printf("CeruleanPlayer v%i.%i.%i\n", CERULEAN_VERSION_MAJOR,
           CERULEAN_VERSION_MINOR, CERULEAN_PATCH_NUMBER);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: cerulean_player <playlist/song filepath>\n");
        return -1;
    }

    PlayerOptions options;
    int option = 0;
    while ((option = getopt(argc, argv, "sv")) != -1) {
        switch (option) {
            case 's':
                options.shuffle = true;
                break;
            case 'v':
                PrintVersionNumber();
                return 0;
            default:
                printf("Usage: cerulean-player <playlist/song filepath>\n");
                return -1;
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
