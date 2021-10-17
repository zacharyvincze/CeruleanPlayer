#pragma once

#include <fmod.hpp>
#include <string>
#include <vector>

struct PlayerOptions {
    bool shuffle = false;
    std::string filepath = "";
};

class Player {
   public:
    Player(PlayerOptions options);
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
    void adjustSpeed(int speed_increment);
    void adjustVolume(int volume_increment);

    double getSpeed() { return _speed; }
    double getVolume() { return _volume; }

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
    double _speed = 1.0f;
    int _speed_increment = 0;
    int _volume_increment = 0;
    double _volume = 1.0f;

    std::string _current_song;
    unsigned int _song_length, _current_ms;

    std::vector<std::string> _song_list;
    int _current_song_num;
};