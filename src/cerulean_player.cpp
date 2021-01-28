#include "cerulean_player.h"

CeruleanPlayer::CeruleanPlayer(Player& player, Window& window)
    : player(player), window(window) {
    running = true;
}

int CeruleanPlayer::run() {
    while (running) {
        auto begin = clock.now();
        int ch = window.getInput();
        switch (ch) {
            case 'q':
                running = false;
                break;
            case ' ':
            case 'p':
                player.pause();
                break;
            case KEY_RIGHT:
                player.nextSong();
                break;
            case KEY_LEFT:
                player.prevSong();
                break;
            case 'r':
                player.setPosition(0);
                break;
            case '.':
                player.movePosition(player.getSongLength() / 50);
                break;
            case ',':
                player.movePosition(-(player.getSongLength() / 50));
                break;
            case 's':
                player.adjustPitch(-1);
                break;
            case 'w':
                player.adjustPitch(1);
                break;
            case 'a':
                player.movePosition(-1000);
                break;
            case 'd':
                player.movePosition(1000);
                break;
            case '-':
                player.adjustVolume(-1);
                break;
            case '=':
                player.adjustVolume(1);
                break;
        }
        player.update();

        window.draw();
        refresh();

        auto end = clock.now();
        auto time_elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::this_thread::sleep_for(std::chrono::milliseconds(30) -
                                    time_elapsed);
    }
    endwin();
    return 0;
}

CeruleanPlayer::~CeruleanPlayer() {}