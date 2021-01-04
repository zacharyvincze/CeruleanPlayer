#pragma once

#include <chrono>
#include <thread>

#include "player.h"
#include "window.h"

class CeruleanPlayer {
   public:
    CeruleanPlayer(Player& player, Window& window);
    ~CeruleanPlayer();

    int run();

   private:
    const unsigned int VERSION_MAJOR = 1;
    const unsigned int VERSION_MINOR = 0;

    Player& player;
    Window& window;

    bool running;
    std::chrono::high_resolution_clock clock;
};