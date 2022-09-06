#pragma once

#include <vector>

#include "Extension.h"

class ExtensionManager {
   public:
    ExtensionManager();
    ~ExtensionManager();

    void RegisterExtension(Extension* extension);

    void OnInput(char input);
    void OnPlayerUpdate(Player& player);
    void OnWindowDraw(Window& window);
    void OnSongChange(const std::string songPath);

   private:
    std::vector<Extension*> m_Extensions;
};