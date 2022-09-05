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

void ExtensionManager::OnWindowDraw(Window& window) {
    for (Extension* extension : m_Extensions) {
        extension->OnWindowDraw(window);
    }
}