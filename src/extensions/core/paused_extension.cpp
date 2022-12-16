#include "paused_extension.h"

#include "player.h"
#include "window.h"

void PausedExtension::on_window_draw(Window &window)
{
    window.set_info_section(m_pauseText);
}

void PausedExtension::on_player_update(Player &player)
{
    if (player.is_paused())
    {
        m_pauseText = "Paused";
    }
    else
    {
        m_pauseText = "";
    }
}
