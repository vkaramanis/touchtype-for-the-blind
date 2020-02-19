#include <SFML/Audio.hpp>
#include <string>
#include <vector>
//#include <Windows.h>
#include "Keys.h"

#ifndef AUDIOHANDLER
#define AUDIOHANDLER

class AudioHandler {
private:
    std::vector<std::string> pl;
    sf::SoundBuffer buffer;
    sf::Sound sound;

public:
    AudioHandler();

    void play();

    void play(const bool& enable);

    void play(const std::string& path);

    void play(const std::vector<std::string>& path);

    void play(const std::vector<std::string>& path, const bool& enable);

    void playAsync(const std::string& path);

    template <typename T>
    void setPlaylist(T t) {
        pl.push_back(t);
    }

    template <typename T1, typename... T>
    void setPlaylist(T1 t1, T... t) {
        pl.push_back(t1);
        setPlaylist(t...);
    }

    void delPlaylist();
};
#endif
