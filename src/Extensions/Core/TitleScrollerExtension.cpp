#include "TitleScrollerExtension.h"

#include "Window.h"

TitleScrollerExtension::TitleScrollerExtension(int titleLength, int scrollingDelay, int scrollingResetDelay)
    : m_titleLength(titleLength), m_scrollingDelay(scrollingDelay), m_scrollingResetDelay(scrollingResetDelay) {
    m_currentScrollingDelay = m_scrollingResetDelay;
}

void TitleScrollerExtension::OnWindowDraw(Window& window) {
    std::string currentTitle = window.GetSongTitle();
    // Do not scroll if the entire title fits
    if (currentTitle.length() <= m_titleLength) return;

    while (m_elapsedTime - m_lastUpdate >= m_currentScrollingDelay) {
        m_currentStringIndex = m_scrollForward ? m_currentStringIndex + 1 : m_currentStringIndex - 1;
        m_lastUpdate += m_currentScrollingDelay;
        m_currentScrollingDelay = m_scrollingDelay;

        if (m_currentStringIndex >= currentTitle.length() - m_titleLength) {
            m_scrollForward = false;
            m_currentScrollingDelay = m_scrollingResetDelay;
        }

        if (m_currentStringIndex == 0) {
            m_currentScrollingDelay = m_scrollingResetDelay;
            m_scrollForward = true;
        }
    }

    window.SetSongTitle(currentTitle.substr(m_currentStringIndex, m_titleLength));
}

void TitleScrollerExtension::OnSongChange(const std::string songPath) { Reset(); }

void TitleScrollerExtension::Reset() {
    m_currentStringIndex = 0;
    m_lastUpdate = m_elapsedTime;
    m_currentScrollingDelay = m_scrollingResetDelay;
    m_scrollForward = true;
}
