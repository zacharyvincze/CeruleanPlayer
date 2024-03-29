# Cerulean Player
CLI music player using FMOD and ncurses. This is more of a personal tool, but feel free to use it. :)

![Cerulean Player Screenshot](screenshots/screenshot1.png)

## Installation

### Install the FMOD Core API Dependency
To compile from source, the FMOD Core API (Responsible for audio playback) will have to be installed on your system.
- The FMOD Core API can be downloaded [here](https://www.fmod.com/download#fmodstudiosuite)

- Extract and copy the files located in the `api/core` directories to their respective folders `lib` and `include`.

### Build using CMake

```shell
mkdir build && cd build && cmake .. && sudo make install
```

## Usage
```shell
cerulean-player <directory/song/playlist>
```

- `Space/P`: Pauses the song
- `Right arrow`: Switches to next song
- `Left arrow`: Switches to previous song
- `R`
- `S`: Lowers song speed
- `W`: Increases song speed
- `A`: Seeks backwards
- `D`: Seeks forwards
- `,`: Quickly seeks backwards
- `.`: Quickly seeks forwards
- `Q`: Quits the player
- `-`: Lowers volume
- `=`: Increases volume

## Command Line Options
- Shuffle playlist: `-s or --shuffle`
