#pragma once

#include <chrono>
#include <thread>

#include "extensions/extension.h"
#include "player.h"
#include "window.h"

class CeruleanPlayer
{
  public:
    CeruleanPlayer(Player &player, Window &window, ExtensionManager &extensionManager);
    ~CeruleanPlayer();

    int run();

  private:
    Player &player;
    Window &window;

    bool running;
    std::chrono::high_resolution_clock clock;

    ExtensionManager &m_extensionManager;
};