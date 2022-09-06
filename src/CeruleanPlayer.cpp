#include "CeruleanPlayer.h"

#include "Extensions/Core/SpeedExtension.h"
#include "Extensions/Core/VolumeExtension.h"
#include "Extensions/TestExtension.h"

CeruleanPlayer::CeruleanPlayer(Player& player, Window& window, ExtensionManager& extensionManager)
    : m_extensionManager(extensionManager), player(player), window(window) {
    // Load player extensions
    m_extensionManager.RegisterExtension(new VolumeExtension());
    m_extensionManager.RegisterExtension(new SpeedExtension());
    m_extensionManager.RegisterExtension(new TestExtension());

    running = true;
}

int CeruleanPlayer::run() {
    player.nextSong();

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

        m_extensionManager.OnInput(ch);

        player.Update();
        window.Draw();
        refresh();

        auto end = clock.now();
        auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::this_thread::sleep_for(std::chrono::milliseconds(30) - time_elapsed);
    }
    endwin();
    return 0;
}

CeruleanPlayer::~CeruleanPlayer() {}