#include "CeruleanPlayer.h"

#include "Extensions/Core/SpeedExtension.h"
#include "Extensions/Core/VolumeExtension.h"

CeruleanPlayer::CeruleanPlayer(Player& player, Window& window) : player(player), window(window), m_ExtensionManager() {
    // Load player extensions
    m_ExtensionManager.RegisterExtension(new VolumeExtension());
    m_ExtensionManager.RegisterExtension(new SpeedExtension());

    running = true;
}

int CeruleanPlayer::run() {
    while (running) {
        auto begin = clock.now();
        int ch = window.GetInput();
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
            case 'a':
                player.movePosition(-1000);
                break;
            case 'd':
                player.movePosition(1000);
                break;
        }

        m_ExtensionManager.OnInput(ch);

        player.Update(m_ExtensionManager);
        window.Draw(m_ExtensionManager);
        refresh();

        auto end = clock.now();
        auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::this_thread::sleep_for(std::chrono::milliseconds(30) - time_elapsed);
    }
    endwin();
    return 0;
}

CeruleanPlayer::~CeruleanPlayer() {}