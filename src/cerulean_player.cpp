#include "cerulean_player.h"

#include "extensions/core/metadata_extension.h"
#include "extensions/core/paused_extension.h"
#include "extensions/core/speed_extension.h"
#include "extensions/core/title_scroller_extension.h"
#include "extensions/core/volume_extension.h"

CeruleanPlayer::CeruleanPlayer(Player& player, Window& window, ExtensionManager& extensionManager)
    : m_extensionManager(extensionManager), player(player), window(window) {
    // Load player extensions
    m_extensionManager.register_extension(new VolumeExtension());
    m_extensionManager.register_extension(new SpeedExtension());
    m_extensionManager.register_extension(new MetadataExtension());
    m_extensionManager.register_extension(new TitleScrollerExtension(37, 500, 3000));
    m_extensionManager.register_extension(new PausedExtension());

    running = true;
}

int CeruleanPlayer::run() {
    auto playerStartTime = clock.now();
    player.next_song();

    while (running) {
        m_extensionManager.update_elapsed_time(
            std::chrono::duration_cast<std::chrono::milliseconds>(clock.now() - playerStartTime).count());
        auto begin = clock.now();
        int ch = window.get_input();
        switch (ch) {
            case 'q':
                running = false;
                break;
            case ' ':
            case 'p':
                player.pause();
                break;
            case KEY_RIGHT:
                player.next_song();
                break;
            case KEY_LEFT:
                player.prev_song();
                break;
            case 'r':
                player.set_position(0);
                break;
            case '.':
                player.move_position(player.get_song_length() / 50);
                break;
            case ',':
                player.move_position(-(player.get_song_length() / 50));
                break;
            case 'a':
                player.move_position(-1000);
                break;
            case 'd':
                player.move_position(1000);
                break;
        }

        m_extensionManager.on_input(ch);

        player.update();
        window.draw();
        refresh();

        auto end = clock.now();
        auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::this_thread::sleep_for(std::chrono::milliseconds(30) - time_elapsed);
    }
    endwin();
    return 0;
}

CeruleanPlayer::~CeruleanPlayer() {}