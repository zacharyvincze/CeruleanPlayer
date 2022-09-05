#include "SpeedExtension.h"

#include "Player.h"
#include "Window.h"

void SpeedExtension::OnInput(char input) {
    switch (input) {
        case 's':
            m_nextSpeedAdjustment = -1;
            break;
        case 'w':
            m_nextSpeedAdjustment = 1;
            break;
    }
}

void SpeedExtension::OnPlayerUpdate(Player& player) {
    if (m_nextSpeedAdjustment != 0) {
        player.adjustSpeed(m_nextSpeedAdjustment);
        m_nextSpeedAdjustment = 0;
    }
    m_currentPlayerSpeed = player.getSpeed();
}

void SpeedExtension::OnWindowDraw(Window& window) {
    if (m_currentPlayerSpeed != 1) {
        mvwprintw(window.GetWindow(), 6, 25, "Speed: %.0f%%", m_currentPlayerSpeed * 100);
    }
}