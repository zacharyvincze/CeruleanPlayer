#pragma once

#include "extensions/extension.h"

class MetadataExtension : public Extension {
   public:
    virtual void on_song_change(const std::string songTitle) override;
    virtual void on_window_draw(Window& window) override;

   private:
    std::string m_songName;
};