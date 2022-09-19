#include "volume_extension.h"

#include "player.h"
#include "window.h"

void VolumeExtension::on_input(char input) {
    switch (input) {
        case '-':
            m_nextVolumeAdjustment = -1;
            break;
        case '=':
            m_nextVolumeAdjustment = 1;
            break;
    }
}

void VolumeExtension::on_player_update(Player& player) {
    if (m_nextVolumeAdjustment != 0) {
        player.adjust_volume(m_nextVolumeAdjustment);
        m_nextVolumeAdjustment = 0;
    }
    m_currentPlayerVolume = player.get_volume();
}

void VolumeExtension::on_window_draw(Window& window) {
    if (m_currentPlayerVolume != 1) {
        mvwprintw(window.get_window(), 5, 25, "Vol: %.0f%%", m_currentPlayerVolume * 100);
    }
}