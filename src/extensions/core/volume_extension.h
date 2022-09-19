#pragma once

#include "extensions/extension.h"

class VolumeExtension : public Extension {
   public:
    virtual void on_input(char input) override;
    virtual void on_window_draw(Window& window) override;
    virtual void on_player_update(Player& player) override;

   private:
    float m_currentPlayerVolume = 0.0f;
    float m_nextVolumeAdjustment = 0.0f;
};