#include "metadata_extension.h"

#include <taglib/fileref.h>
#include <taglib/taglib.h>

#include "window.h"

void MetadataExtension::on_song_change(const std::string songPath) {
    TagLib::FileRef f(songPath.c_str());
    TagLib::String songName = f.tag()->title();
    TagLib::String songArtist = f.tag()->artist();

    // Set the song name to the path if there are no id3 tags
    if (songName.isEmpty()) {
        m_songName = songPath;
    } else {
        m_songName = songName.to8Bit();
    }

    if (!songArtist.isEmpty()) {
        m_songName += " - " + songArtist.to8Bit();
    }
}

void MetadataExtension::on_window_draw(Window& window) { window.set_song_title(m_songName); }
