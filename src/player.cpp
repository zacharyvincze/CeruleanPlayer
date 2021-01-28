#include "player.h"

#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>

Player::Player(const std::string filepath) {
    // Initialize FMOD
    FMOD::System_Create(&_system);
    _system->getVersion(&_fmod_version);
    FMOD_Debug_Initialize(FMOD_DEBUG_LEVEL_NONE, FMOD_DEBUG_MODE_TTY, nullptr,
                          nullptr);
    _system->init(32, FMOD_INIT_NORMAL, 0);

    _current_song_num = -1;

    // Check if playlist or not, handle appropriately
    if (boost::filesystem::extension(filepath) == ".playlist") {
        std::ifstream infile(filepath.c_str());
        std::string line;
        while (std::getline(infile, line)) {
            _song_list.push_back(line);
        }
        infile.close();
    } else if (boost::filesystem::is_directory(filepath)) {
        for (boost::filesystem::directory_iterator itr(filepath);
             itr != boost::filesystem::directory_iterator(); itr++) {
            _song_list.push_back(itr->path().c_str());
        }
    } else {
        _song_list.push_back(filepath);
    }

    nextSong();
}

Player::~Player() { _sound->release(); }

void Player::load(const std::string filepath) {
    if (_sound != nullptr) {
        _sound->release();
    }
    _system->createStream(filepath.c_str(), FMOD_DEFAULT, 0, &_sound);
    _current_song = boost::filesystem::path(filepath).filename().c_str();
    _sound->getLength(&_song_length, FMOD_TIMEUNIT_MS);
}

void Player::play() {
    _sound->setMode(FMOD_LOOP_OFF);
    _system->playSound(_sound, 0, false, &_channel);
    _channel->setPitch(_pitch);
}

void Player::pause() {
    _paused = !_paused;
    _channel->setPaused(_paused);
}

void Player::movePosition(int delta) {
    _channel->setPosition(getCurrentPosition() + delta, FMOD_TIMEUNIT_MS);
}

void Player::setPosition(unsigned int millis) {
    _channel->setPosition(millis, FMOD_TIMEUNIT_MS);
}

bool Player::isPlaying() {
    bool is_finished;
    _channel->isPlaying(&is_finished);
    return is_finished;
}

void Player::nextSong() {
    _current_song_num++;
    if (_current_song_num > _song_list.size() - 1) {
        _current_song_num = 0;
    }
    load(_song_list[_current_song_num]);
    play();
}

void Player::prevSong() {
    _current_song_num--;
    if (_current_song_num < 0) {
        _current_song_num = _song_list.size() - 1;
    }
    load(_song_list[_current_song_num]);
    play();
}

unsigned int Player::getCurrentPosition() {
    _channel->getPosition(&_current_ms, FMOD_TIMEUNIT_MS);
    return _current_ms;
}

void Player::adjustPitch(int pitch_increment) {
    _pitch_increment += pitch_increment;
    _pitch = (1.0f + (0.05f * _pitch_increment));
    _channel->setPitch(_pitch);
}

void Player::update() {
    if (!isPlaying()) {
        nextSong();
    }
}