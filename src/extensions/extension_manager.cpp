#include "extension_manager.h"

#include "window.h"

ExtensionManager::ExtensionManager() {}

ExtensionManager::~ExtensionManager() {
    for (Extension* extension : m_Extensions) {
        delete extension;
    }
    m_Extensions.clear();
}

void ExtensionManager::register_extension(Extension* extension) { m_Extensions.push_back(extension); }

void ExtensionManager::on_input(char input) {
    for (Extension* extension : m_Extensions) {
        extension->on_input(input);
    }
}

void ExtensionManager::on_window_draw(Window& window) {
    for (Extension* extension : m_Extensions) {
        extension->on_window_draw(window);
    }
}

void ExtensionManager::on_player_update(Player& player) {
    for (Extension* extension : m_Extensions) {
        extension->on_player_update(player);
    }
}

void ExtensionManager::on_song_change(const std::string songPath) {
    for (Extension* extension : m_Extensions) {
        extension->on_song_change(songPath);
    }
}

void ExtensionManager::update_elapsed_time(long elapsedTime) {
    for (Extension* extension : m_Extensions) {
        extension->set_elapsed_time(elapsedTime);
    }
}
