#pragma once

#include "Extensions/Extension.h"

class MetadataExtension : public Extension {
   public:
    virtual void OnSongChange(const std::string songTitle) override;
    virtual void OnWindowDraw(Window& window) override;

   private:
    std::string m_songName;
};