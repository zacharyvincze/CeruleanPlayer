#include "VolumeExtension.h"

#include "Player.h"
#include "Window.h"

void VolumeExtension::OnInput(char input) {
    switch (input) {
        case '-':
            m_nextVolumeAdjustment = -1;
            break;
        case '=':
            m_nextVolumeAdjustment = 1;
            break;
    }
}

void VolumeExtension::OnPlayerUpdate(Player& player) {
    if (m_nextVolumeAdjustment != 0) {
        player.adjustVolume(m_nextVolumeAdjustment);
        m_nextVolumeAdjustment = 0;
    }
    m_currentPlayerVolume = player.getVolume();
}

void VolumeExtension::OnWindowDraw(Window& window) {
    if (m_currentPlayerVolume != 1) {
        mvwprintw(window.GetWindow(), 5, 25, "Vol: %.0f%%", m_currentPlayerVolume * 100);
    }
}