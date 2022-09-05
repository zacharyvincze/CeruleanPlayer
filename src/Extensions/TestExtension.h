#pragma once

#include "Extensions/Extension.h"

class TestExtension : public Extension {
   public:
    void OnPlayerUpdate(Player& player) {}
    void OnWindowDraw(Window& window) { mvwprintw(window.GetWindow(), 8, 1, "Test Extension"); }
};