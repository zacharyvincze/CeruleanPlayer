#pragma once

#include "extensions/extension.h"

class TitleScrollerExtension : public Extension
{
  public:
    TitleScrollerExtension(int titleLength, int scrollingDelay, int scrollingResetDelay);
    virtual void on_song_change(const std::string songPath) override;
    virtual void on_window_draw(Window &window) override;

  private:
    void reset();

    int m_currentStringIndex = 0;
    long m_lastUpdate = 0;

    int m_titleLength;
    int m_scrollingDelay;
    int m_scrollingResetDelay;

    int m_currentScrollingDelay;

    bool m_scrollForward = true;

    std::string m_updatedSongName;
};