#include "player.h"

#include <algorithm>
#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <random>

#include "extensions/extension_manager.h"

Player::Player(PlayerOptions options, ExtensionManager &extensionManager) : m_extensionManager(extensionManager)
{
    // Initialize FMOD
    FMOD::System_Create(&_system);
    _system->getVersion(&_fmod_version);
    FMOD_Debug_Initialize(FMOD_DEBUG_LEVEL_NONE, FMOD_DEBUG_MODE_TTY, nullptr, nullptr);
    _system->init(32, FMOD_INIT_NORMAL, 0);
    _sound = nullptr;

    _current_song_num = -1;
    std::string filepath = options.filepath;

    // Check if playlist or not, handle appropriately
    if (boost::filesystem::extension(filepath) == ".playlist")
    {
        std::ifstream infile(filepath.c_str());
        std::string line;
        while (std::getline(infile, line))
        {
            _song_list.push_back(line);
        }
        infile.close();
    }
    else if (boost::filesystem::is_directory(filepath))
    {
        for (boost::filesystem::directory_iterator itr(filepath); itr != boost::filesystem::directory_iterator(); itr++)
        {
            _song_list.push_back(itr->path().c_str());
        }
    }
    else
    {
        _song_list.push_back(filepath);
    }

    // Shuffle the song list if the option is chosen
    if (options.shuffle)
    {
        std::random_device rd;
        std::default_random_engine rng(rd());
        std::shuffle(_song_list.begin(), _song_list.end(), rng);
    }
}

Player::~Player()
{
    _sound->release();
}

void Player::load(const std::string filepath)
{
    if (_sound != nullptr)
    {
        _sound->release();
    }
    _system->createStream(filepath.c_str(), FMOD_DEFAULT, 0, &_sound);
    _current_song = boost::filesystem::path(filepath).filename().c_str();
    _sound->getLength(&_song_length, FMOD_TIMEUNIT_MS);
}

void Player::play()
{
    _sound->setMode(FMOD_LOOP_OFF);
    _system->playSound(_sound, 0, false, &_channel);
    _channel->setPitch(_speed);
    _channel->setVolume(_volume);
}

void Player::pause()
{
    _paused = !_paused;
    _channel->setPaused(_paused);
}

void Player::move_position(int delta)
{
    _channel->setPosition(get_current_position() + delta, FMOD_TIMEUNIT_MS);
}

void Player::set_position(unsigned int millis)
{
    _channel->setPosition(millis, FMOD_TIMEUNIT_MS);
}

bool Player::is_playing()
{
    bool is_finished;
    _channel->isPlaying(&is_finished);
    return is_finished;
}

void Player::next_song()
{
    _current_song_num++;
    if (_current_song_num > _song_list.size() - 1)
    {
        _current_song_num = 0;
    }
    load(_song_list[_current_song_num]);
    play();
    m_extensionManager.on_song_change(_song_list[_current_song_num]);
}

void Player::prev_song()
{
    _current_song_num--;
    if (_current_song_num < 0)
    {
        _current_song_num = _song_list.size() - 1;
    }
    load(_song_list[_current_song_num]);
    play();
    m_extensionManager.on_song_change(_song_list[_current_song_num]);
}

unsigned int Player::get_current_position()
{
    _channel->getPosition(&_current_ms, FMOD_TIMEUNIT_MS);
    return _current_ms;
}

void Player::adjust_speed(int speed_increment)
{
    _speed_increment += speed_increment;
    _speed = (1.0f + (0.05f * _speed_increment));
    _channel->setPitch(_speed);
}

void Player::adjust_volume(int volume_increment)
{
    _volume_increment += volume_increment;
    _volume = 1.0f + (0.025f * _volume_increment);
    _channel->setVolume(_volume);
}

void Player::update()
{
    if (!is_playing())
    {
        next_song();
    }
    m_extensionManager.on_player_update(*this);
}