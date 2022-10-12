#include"MyText.h"
const wchar_t* alphavit_wchar = L"abcdifghtrqwzxp";
const char* alphavit_char = "abcdifghtrqwzxp";
void SetLocale() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);
}
string ToSTD_STRING(wstring t) {
    const wchar_t* v = t.c_str();
    string out_ = "";

    for (int n = 0; n < t.length(); n++) {
        byte f = v[n] / 256;
        out_ += alphavit_char[f / T_Length];
        out_ += alphavit_char[f % T_Length];
        f = v[n] % 256;
        out_ += alphavit_char[f / T_Length];
        out_ += alphavit_char[f % T_Length];
    }
    //out_ += L"\n";
    return out_;
}
byte GetByte(wchar_t x, wchar_t y) {
    int f = 0;
    for (int i = 0; i < T_Length; i++) {
        if (alphavit_wchar[i] == x) {
            f = T_Length * i;
            break;
        }
    }
    for (int i = 0; i < T_Length; i++) {
        if (alphavit_wchar[i] == y) {
            f += i;
            break;
        }
    }
    return (byte)f;
}
byte GetByte(char x, char y) {
    int f = 0;
    for (int i = 0; i < T_Length; i++) {
        if (alphavit_wchar[i] == x) {
            f = T_Length * i;
            break;
        }
    }
    for (int i = 0; i < T_Length; i++) {
        if (alphavit_wchar[i] == y) {
            f += i;
            break;
        }
    }
    return (byte)f;
}
wstring ToSTD_WSTRING(string t) {
    const char* v = t.c_str();
    wstring out_ = L"";

    //out_ += (wchar_t)"";
    for (int i = 0; i < t.length(); i += 4) {
        byte b1 = GetByte(v[i], v[i + 1]);
        byte b2 = GetByte(v[i + 2], v[i + 3]);
        wchar_t sim = (256 * b1) + b2;
        out_ += sim;
    }
    return out_;
}