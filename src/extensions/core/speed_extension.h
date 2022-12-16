#pragma once

#include "extensions/extension.h"

class SpeedExtension : public Extension
{
  public:
    virtual void on_input(char input) override;
    virtual void on_window_draw(Window &window) override;
    virtual void on_player_update(Player &player) override;

  private:
    float m_currentPlayerSpeed = 0.0f;
    float m_nextSpeedAdjustment = 0.0f;
};