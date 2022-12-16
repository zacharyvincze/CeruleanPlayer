#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#include "cerulean_player.h"
#include "helpers.h"
#include "metadata.h"

void print_version_number()
{
    printf("CeruleanPlayer v" CERULEAN_PLAYER_VERSION "\n");
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: cerulean_player <playlist/song filepath>\n");
        return -1;
    }

    PlayerOptions options;
    int option = 0;
    while ((option = getopt(argc, argv, "sv")) != -1)
    {
        switch (option)
        {
        case 's':
            options.shuffle = true;
            break;
        case 'v':
            print_version_number();
            return 0;
        default:
            printf("Usage: cerulean-player <playlist/song filepath>\n");
            return -1;
        }
    }

    // Obtain path to music
    for (; optind < argc; optind++)
    {
        options.filepath = argv[optind];
    }

    ExtensionManager extensionManager;
    Player player(options, extensionManager);
    Window window(player, extensionManager);
    CeruleanPlayer ceruleanPlayer(player, window, extensionManager);

    ceruleanPlayer.run();

    return 0;
}
