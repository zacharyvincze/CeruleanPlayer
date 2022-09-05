#pragma once

#include <vector>

#include "Extension.h"

class ExtensionManager {
   public:
    ExtensionManager();
    ~ExtensionManager();

    void RegisterExtension(Extension* extension);
    void OnWindowDraw(Window& window);

   private:
    std::vector<Extension*> m_Extensions;
};