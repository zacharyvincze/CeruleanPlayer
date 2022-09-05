#pragma once

#include "Extensions/Extension.h"

class VolumeExtension : public Extension {
   public:
    virtual void OnInput(char input) override;
    virtual void OnWindowDraw(Window& window) override;
    virtual void OnPlayerUpdate(Player& player) override;

   private:
    float m_currentPlayerVolume = 0.0f;
    float m_nextVolumeAdjustment = 0.0f;
};