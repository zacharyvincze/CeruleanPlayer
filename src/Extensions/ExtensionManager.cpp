#include "ExtensionManager.h"

#include "Window.h"

ExtensionManager::ExtensionManager() {}

ExtensionManager::~ExtensionManager() {
    for (Extension* extension : m_Extensions) {
        delete extension;
    }
    m_Extensions.clear();
}

void ExtensionManager::RegisterExtension(Extension* extension) { m_Extensions.push_back(extension); }

void ExtensionManager::OnInput(char input) {
    for (Extension* extension : m_Extensions) {
        extension->OnInput(input);
    }
}

void ExtensionManager::OnWindowDraw(Window& window) {
    for (Extension* extension : m_Extensions) {
        extension->OnWindowDraw(window);
    }
}

void ExtensionManager::OnPlayerUpdate(Player& player) {
    for (Extension* extension : m_Extensions) {
        extension->OnPlayerUpdate(player);
    }
}
void ExtensionManager::OnSongChange(const std::string songPath) {
    for (Extension* extension : m_Extensions) {
        extension->OnSongChange(songPath);
    }
}
