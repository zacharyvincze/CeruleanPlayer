#pragma once

struct Window;
struct Player;

// Provides extensions to CeruleanPlayer capabilities. This should provide access to various sections
// of the player as required.

class Extension {
   public:
    Extension() {}
    ~Extension() {}
    virtual void OnPlayerUpdate(Player& player) = 0;
    virtual void OnWindowDraw(Window& window) = 0;
};