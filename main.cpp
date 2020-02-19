#include <iostream>
#include <sapi53.h>
#include "Keys.h"
#include "SQLite_Client.h"
#include "Sampler.h"
#include "AudioHandler.h"

typedef 
enum CASE {
    INSTRUMENT_MODE,
    FASTTYPE_MODE,
    WORD_MODE,
}CASE;

std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

void app() {
    //init
    //Default Mode
    CASE mode = INSTRUMENT_MODE;
    //Import To Library
    bool libImport(false);
    //Spacebar_Enable
    bool enable(false);
    //Word for TTS
    std::string word = "";
    //Load word library
    SQLite_Client words("./sqlite-31.db");
    //Audio
    AudioHandler ah;
    //TTS
    ISpVoice* tts = NULL;
    if (FAILED(::CoInitialize(NULL)))
        std::cout << "tts failed\n";

    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&tts);
    //Keys
    Keys ctrl(K_CTRL);
    Keys spacebar(K_SPACEBAR);
    Keys back(K_BACKSPACE);
    Keys k3(K_3);
    Keys k2(K_2);
    Keys k1(K_1);

    std::vector<Keys> k;
    for (int i(0); i <= 25; ++i) {
        Keys temp(static_cast<KEYCODE>(K_A + i));
        k.push_back(temp);
    }
    //Samples
    Sampler Start_With(START_WITH, RANDOM);
    
    std::vector<Sampler> inst;
    std::vector<Sampler> speech_inst;
    std::vector<Sampler> alphabet;
    std::vector<Sampler> phonetics;

    for (int i(0); i <= 25; ++i) {
        Sampler ti(INSTRUMENT + (A + i));
        Sampler tsi(SPEECH_INSTRUMENT + (A + i), RANDOM);
        Sampler ta(ALPHABET + (A + i), RANDOM);
        Sampler tp(PHONETIC + (A + i), RANDOM);

        inst.push_back(ti);
        speech_inst.push_back(tsi);
        alphabet.push_back(ta);
        phonetics.push_back(tp);
    }

    std::cout << "TouchType for Blind\nCTRL+h for help\n";
    while (true) {
        //Main Menu
        if (ctrl.state() >= PRESSED&& k1.state() == PRESSED) {
            std::cout << "Instrument Mode\n";
            mode = INSTRUMENT_MODE;
        }
        else if (ctrl.state() >= PRESSED&& k2.state() == PRESSED) {
            std::cout << "FastType Mode\n";
            mode = FASTTYPE_MODE;
        }
        else if (ctrl.state() >= PRESSED&& k3.state() == PRESSED) {
            std::cout << "Word Mode\n";
            mode = WORD_MODE;
        }
        else if (ctrl.state() >= PRESSED&& k[16].state() == PRESSED) {
            std::cout << "Quiting\n";
            break;
        }
        else if (ctrl.state() >= PRESSED&& k[7].state() == PRESSED) {
            std::cout << "CTRL+1 - Instrument Mode \nCTRL+2 - FastType Mode\nCTRL+3 - Word Mode\nCRL+Q - Quit\n";
        }
        //Keys Loop
        for (int i(0); i <= 25; ++i)
        {
            if (k[i].state() == PRESSED && ctrl.state() == NON_PRESSED) {
                switch (mode)
                {
                case INSTRUMENT_MODE: {
                    ah.setPlaylist(inst[i].getSample(), speech_inst[i].getSample(), Start_With.getSample(), phonetics[i].getSample(), alphabet[i].getSample());
                    break;
                case FASTTYPE_MODE:
                    ah.play(phonetics[i].getSample());
                    break; 
                }
                case WORD_MODE: {
                    std::string st = "";
                    st = static_cast<char>(i + 97);
                    std::wstring temp = s2ws(st);
                    tts->Speak(temp.c_str(), SPF_PURGEBEFORESPEAK | SPF_ASYNC, NULL);
                    word += st;
                    break;
                }
                default:
                    break;
                }
            }

        }

        switch (mode)
        {
        case INSTRUMENT_MODE: {
            if (ctrl.state() >= PRESSED&& spacebar.state() == PRESSED) {
                if (!enable) {
                    enable = true;
                    std::cout << "Enabling Space\n";
                }
                else {
                    enable = false;
                    std::cout << "Disabling Space\n";
                }
            }
            if (!enable) { ah.play(); }
            else { ah.play(1); }
            ah.delPlaylist();
            break;
        }
        case FASTTYPE_MODE:
            break;
        case WORD_MODE: {
            if (ctrl.state() >= PRESSED&& k[8].state() == PRESSED) {
                if (!libImport) {
                    libImport = true;
                    std::cout << "Enabling Word Import\n";
                }
                else {
                    libImport = false;
                    std::cout << "Disabling Word Import\n";
                }
            }

            if (spacebar.state() == PRESSED) {
                std::string temp = "SELECT LEMMA FROM WORDS WHERE LEMMA = \"" + word + "\";";

                if (words.getValue(temp.c_str())) {
                    std::wstring stemp = s2ws(word);
                    LPCWSTR result = stemp.c_str();
                    hr = tts->Speak(result, 0, NULL);
                }
                else {
                    if (libImport) {
                        std::cout << word << " not found\nInsert it to DB? ctrl+(y/n)\n";

                        while (1) {
                            if (ctrl.state() > PRESSED& k[24].state() == PRESSED) {
                                std::string stemp = "INSERT INTO WORDS(LEMMA) VALUES(\"" + word + "\")";
                                words.setStatement(stemp.c_str());
                                std::cout << "placed\n";
                                break;
                            }
                            else if (ctrl.state() > PRESSED& k[13].state() == PRESSED) {
                                std::cout << "Back\n";
                                break;
                            }
                        }
                    }
                    else { std::cout << word << " not found\n"; }
                }
                word = "";
            }
            break;
        }
        }
    }
    tts->Release();
    tts = NULL;
    ::CoUninitialize();
}

int main(int argc, char* argv[]) {
    app();
    return 0;
}
