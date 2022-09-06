#pragma once

#include <string>

struct Window;
struct Player;

// Provides extensions to CeruleanPlayer capabilities. This should provide access to various sections
// of the player as required.

class Extension {
   public:
    Extension() {}
    ~Extension() {}

    virtual void OnInput(char input) {}
    virtual void OnPlayerUpdate(Player& player) {}
    virtual void OnWindowDraw(Window& window) {}
    virtual void OnSongChange(const std::string songPath) {}
};