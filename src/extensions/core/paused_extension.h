#pragma once

#include "extensions/extension.h"

class PausedExtension : public Extension
{
  public:
    void on_window_draw(Window &window) override;
    void on_player_update(Player &player) override;

  private:
    std::string m_pauseText;
};