#include <string>
#include <filesystem>
#include <map>

#ifndef SAMPLER
#define SAMPLER

typedef
enum SAMPLES {
    //LETTERS
    A                   = 0,
    B                   = 1,
    C                   = 2,
    D                   = 3,
    E                   = 4,
    F                   = 5,
    G                   = 6,
    H                   = 7,
    I                   = 8,
    J                   = 9,
    K                   = 10,
    L                   = 11,
    M                   = 12,
    N                   = 13,
    O                   = 14,
    P                   = 15,
    Q                   = 16,
    R                   = 17,
    S                   = 18,
    T                   = 19,
    U                   = 20,
    V                   = 21,
    W                   = 22,
    X                   = 23,
    Y                   = 24,
    Z                   = 25,

    //TYPE
    TYPE                = 100,
    INSTRUMENT          = 100,
    SPEECH_INSTRUMENT   = 200,
    PHONETIC            = 300,
    ALPHABET            = 400,

    //OTHER
    KEY                 = 1000,
    LETTER              = 2000,
    START_WITH          = 3000,
    ERR                 = 4000,

    //END
    END                 = -1,
}   SAMPLES;

typedef
enum MODE {
    SEQUENCE,
    RANDOM
}   MODE;

class Sampler
{
private:
    static std::map<SAMPLES, std::string> dir;
    static const std::filesystem::path curpath;
    std::string path;
    int fileCount;
    int increment = 0;
    int mode;

    const int getFileCount();

public:
    Sampler(const std::string p);

    Sampler(const std::string p, MODE m);

    Sampler(int s);

    Sampler(int s, MODE m);


    void setPath(const std::string& p);

    const std::string& getPath();

    void setMode(const MODE& m);

    const std::string getSample();
};
#endif
