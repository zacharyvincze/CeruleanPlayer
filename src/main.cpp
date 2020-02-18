#include <ncurses.h>
#include <chrono>
#include <thread>
#include "player.h"
#include "window.h"

int main(int argc, char **argv) {
    Player player(argv[1]);
    Window window(player);

    bool running = true;
    while (running) {
        int ch = window.getInput();
        switch (ch) {
            case 'q':
                running = false;
                break;
            case ' ':
                player.pause();
                break;
            case KEY_RIGHT:
                player.nextSong();
                break;
            case KEY_LEFT:
                player.prevSong();
                break;
            case KEY_DOWN:
                player.setPosition(0);
                break;
            case '.':
                player.movePosition(player.getSongLength() / 50);
                break;
            case ',':
                player.movePosition(-(player.getSongLength() / 50));
                break;
            case 's':
                player.adjustPitch(-0.05f);
                break;
            case 'w':
                player.adjustPitch(0.05f);
                break;
        }
        player.update();

        window.draw();
        refresh();

        // Improved CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    endwin();

    return 0;
}