# Cerulean Player
CLI music player using FMOD and ncurses
## Usage
    cerulean-player <directory/song/playlist>

- `Space`: Pauses the song
- `Right arrow`: Switches to next song
- `Left arrow`: Switches to previous song
- `,`: Seeks backwards
- `.`: Seeks forwards
- `S`: Lowers the speed
- `W`: Increases song speed

## Installation
    mkdir build && cd build && cmake .. && make