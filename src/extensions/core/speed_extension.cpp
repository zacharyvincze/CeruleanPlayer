#include "speed_extension.h"

#include "player.h"
#include "window.h"

void SpeedExtension::on_input(char input) {
    switch (input) {
        case 's':
            m_nextSpeedAdjustment = -1;
            break;
        case 'w':
            m_nextSpeedAdjustment = 1;
            break;
    }
}

void SpeedExtension::on_player_update(Player& player) {
    if (m_nextSpeedAdjustment != 0) {
        player.adjust_speed(m_nextSpeedAdjustment);
        m_nextSpeedAdjustment = 0;
    }
    m_currentPlayerSpeed = player.get_speed();
}

void SpeedExtension::on_window_draw(Window& window) {
    if (m_currentPlayerSpeed != 1) {
        mvwprintw(window.get_window(), 6, 25, "Speed: %.0f%%", m_currentPlayerSpeed * 100);
    }
}