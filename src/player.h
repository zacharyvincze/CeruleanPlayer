#pragma once

#include <fmod/fmod.hpp>
#include <string>
#include <vector>

class Player {
   public:
    Player(const std::string filepath);
    ~Player();

    // Player functions
    void play();
    void resume();
    void pause();
    void load(const std::string filepath);
    void movePosition(int delta);
    void setPosition(unsigned int millis);
    bool isPlaying();
    void nextSong();
    void prevSong();
    void adjustPitch(int pitch_increment);

    double getPitch() { return _pitch; }

    void update();

    unsigned int getFmodVersion() { return _fmod_version; }

    unsigned int getCurrentPosition();
    unsigned int getSongLength() { return _song_length; }
    inline std::string getCurrentSong() { return _current_song; }

   private:
    FMOD::System *_system;
    FMOD::Sound *_sound;
    FMOD::Channel *_channel = 0;
    unsigned int _fmod_version;

    // Song attributes
    bool _paused = false;
    double _pitch = 1.0f;
    int _pitch_increment = 0;

    std::string _current_song;
    unsigned int _song_length, _current_ms;

    std::vector<std::string> _song_list;
    int _current_song_num;
};