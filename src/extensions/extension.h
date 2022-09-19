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

    virtual void on_input(char input) {}
    virtual void on_player_update(Player& player) {}
    virtual void on_window_draw(Window& window) {}
    virtual void on_song_change(const std::string songPath) {}

    inline void set_elapsed_time(long elapsedTime) { m_elapsedTime = elapsedTime; }

   protected:
    long m_elapsedTime;
};