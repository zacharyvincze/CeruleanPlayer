#pragma once

#include <vector>

#include "extension.h"

class ExtensionManager
{
  public:
    ExtensionManager();
    ~ExtensionManager();

    void register_extension(Extension *extension);

    void on_input(char input);
    void on_player_update(Player &player);
    void on_window_draw(Window &window);
    void on_song_change(const std::string songPath);
    void update_elapsed_time(long elapsedTime);

  private:
    std::vector<Extension *> m_Extensions;
};