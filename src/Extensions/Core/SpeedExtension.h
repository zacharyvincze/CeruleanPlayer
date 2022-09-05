#pragma once

#include "Extensions/Extension.h"

class SpeedExtension : public Extension {
   public:
    virtual void OnInput(char input) override;
    virtual void OnWindowDraw(Window& window) override;
    virtual void OnPlayerUpdate(Player& player) override;

   private:
    float m_currentPlayerSpeed = 0.0f;
    float m_nextSpeedAdjustment = 0.0f;
};