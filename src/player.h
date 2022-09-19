#pragma once

#include <fmod.hpp>
#include <string>
#include <vector>

struct PlayerOptions {
    bool shuffle = false;
    std::string filepath = "";
};

struct ExtensionManager;

class Player {
   public:
    Player(PlayerOptions options, ExtensionManager &extensionManager);
    ~Player();

    // Player functions
    void play();
    void resume();
    void pause();
    void load(const std::string filepath);
    void move_position(int delta);
    void set_position(unsigned int millis);
    bool is_playing();
    void next_song();
    void prev_song();
    void adjust_speed(int speed_increment);
    void adjust_volume(int volume_increment);

    double get_speed() { return _speed; }
    double get_volume() { return _volume; }

    void update();

    unsigned int get_fmod_version() { return _fmod_version; }

    unsigned int get_current_position();
    unsigned int get_song_length() { return _song_length; }
    inline std::string get_current_song() { return _current_song; }

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

    ExtensionManager &m_extensionManager;
};