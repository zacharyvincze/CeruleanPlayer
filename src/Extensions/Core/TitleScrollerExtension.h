#pragma once

#include "Extensions/Extension.h"

class TitleScrollerExtension : public Extension {
   public:
    TitleScrollerExtension(int titleLength, int scrollingDelay, int scrollingResetDelay);
    virtual void OnSongChange(const std::string songPath) override;
    virtual void OnWindowDraw(Window& window) override;

   private:
    int m_currentStringIndex = 0;
    long m_lastUpdate = 0;

    int m_titleLength;
    int m_scrollingDelay;
    int m_scrollingResetDelay;

    int m_currentScrollingDelay;

    std::string m_updatedSongName;
};