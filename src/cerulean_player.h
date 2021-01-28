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
    Player& player;
    Window& window;

    bool running;
    std::chrono::high_resolution_clock clock;
};