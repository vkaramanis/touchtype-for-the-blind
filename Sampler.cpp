#include "Sampler.h"

std::map<SAMPLES, std::string> Sampler::dir{
{A, "a/"},
{B, "b/"},
{C, "c/"},
{D, "d/"},
{E, "e/"},
{F, "f/"},
{G, "g/"},
{H, "h/"},
{I, "i/"},
{J, "j/"},
{K, "k/"},
{L, "l/"},
{M, "m/"},
{N, "n/"},
{O, "o/"},
{P, "p/"},
{Q, "q/"},
{R, "r/"},
{S, "s/"},
{T, "t/"},
{U, "u/"},
{V, "v/"},
{W, "w/"},
{X, "x/"},
{Y, "y/"},
{Z, "z/"},

{INSTRUMENT,        "/samples/instrument/"},
{SPEECH_INSTRUMENT, "/samples/speech/instrument/"},
{PHONETIC,          "/samples/speech/letter/phonetic/"},
{ALPHABET,          "/samples/speech/letter/alphabet/"},

{KEY,               "/samples/speech/other/key/"},
{LETTER,            "/samples/speech/other/letter/"},
{START_WITH,        "/samples/speech/other/start_with/"},
{ERR,               "/samples/sound/error/"},

};

const std::filesystem::path Sampler::curpath = std::filesystem::current_path();

Sampler::Sampler(const std::string p) : path(curpath.string() + p), mode(SEQUENCE)  { fileCount = getFileCount(); };

Sampler::Sampler(const std::string p, MODE m) : path(curpath.string() + p), mode(m) { fileCount = getFileCount(); };

Sampler::Sampler(int s) : mode(SEQUENCE) {
    path = curpath.string();
    while (s >= 0) {
        if (s >= 1000) {
            //OTHERS
            path += dir[static_cast<SAMPLES>(s)];
            s = END;
        }
        else if (s >= 100) {
            //TYPE
            int letter = s % TYPE;
            path += dir[static_cast<SAMPLES>(s - letter)];
            s = letter;
        }
        else if (s >= 0) {
            //LETTER
            path += dir[static_cast<SAMPLES>(s)];
            s = END;
        }
    }
    fileCount = getFileCount();
};

Sampler::Sampler(int s, MODE m): mode(m) {
    path = curpath.string();
    while (s >= 0) {
        if (s >= 1000) {
            //OTHERS
            path += dir[static_cast<SAMPLES>(s)];
            s = END;
        }
        else if (s >= 100) {
            //TYPE
            int letter = s % TYPE;
            path += dir[static_cast<SAMPLES>(s - letter)];
            s = letter;
        }
        else if (s >= 0) {
            //LETTER
            path += dir[static_cast<SAMPLES>(s)];
            s = END;
        }
    }
    fileCount = getFileCount();
};


void Sampler::setPath(const std::string& p) { path = p; }

const std::string& Sampler::getPath() { return path; }

void Sampler::setMode(const MODE& m) { mode = m; }

const std::string Sampler::getSample() {
    if (fileCount > 1) {
        if (mode == 0) return path + std::to_string(increment++ % fileCount) + ".wav";
        else return path + std::to_string(rand() % fileCount) + ".wav";
    }
    else {
        if (mode == 0) return path + std::to_string(0) + ".wav";
        else return path + std::to_string(0) + ".wav";
    }
}

const int Sampler::getFileCount() {
    auto it = std::filesystem::directory_iterator(path);
    int temp(0);
    for (auto& p : it) if (p.is_regular_file()) ++temp;
    return temp-1;
};