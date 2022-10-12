// Server_Streng_CPP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<string>
#include<string.h>


#include<fstream>
#include<locale>
#include"MyText.h"
const char* f_serv_name = "serv.txt";
const char* f_client_name = "client.txt";
//using namespace std;
//const wchar_t* alphavit = L"abcdifghtrqwzxp";
//const char* alphavit_char = "abcdifghtrqwzxp";
//typedef unsigned char byte;
//#define T_Length 16
/*wstring EncodeText(wstring t) {
    const wchar_t* v = t.c_str();
    wstring out_;
    out_ += L"";
    for (int n = 0; n < t.length(); n++) {
        byte f = v[n]/256;
        out_ += alphavit_wchar[f / T_Length];
        out_ += alphavit_wchar[f % T_Length];
        f = v[n] % 256;
        out_ += alphavit_wchar[f / T_Length];
        out_ += alphavit_wchar[f % T_Length];
    }
   
    return out_;
}*/
/*byte GetByte(wchar_t x, wchar_t y) {
    int f = 0;
    for (int i = 0; i < T_Length; i++) {
        if (alphavit[i] == x) {
            f = T_Length * i;
            break;
        }
    }
    for (int i = 0; i < T_Length; i++) {
        if (alphavit[i] == y) {
            f += i;
            break;
        }
    }
    return (byte)f;
}*/
/*wstring DecodeText(wstring t) {
    const wchar_t* v = t.c_str();
    wstring out_ = L"";
    
    //out_ += (wchar_t)"";
    for (int i = 0; i < t.length(); i += 4) {
        byte b1= GetByte(v[i], v[i + 1]);
        byte b2 = GetByte(v[i + 2], v[i + 3]);
        wchar_t sim= (256 * b1) + b2;
        out_ += sim;
    }
    return out_;

}*/
#pragma region String_
/*string EncodeText(string t) {
    const char* v = t.c_str();
    string out_;
    out_ += "";
    for (int n = 0; n < t.length(); n++) {
        byte f = v[n]; //;/ 256;
        out_ += alphavit_char[f / T_Length];
        out_ += alphavit_char[f % T_Length];
        
    }
    
    return out_;
}*/
/*byte GetByte(char x, char y) {
    int f = 0;
    for (int i = 0; i < T_Length; i++) {
        if (alphavit[i] == x) {
            f = T_Length * i;
            break;
        }
    }
    for (int i = 0; i < T_Length; i++) {
        if (alphavit[i] == y) {
            f += i;
            break;
        }
    }
    return (byte)f;
}*/
/*string DecodeText(string t) {
    const char* v = t.c_str();
    string out_ = "";

   
    for (int i = 0; i < t.length(); i += 2) {
        
        out_ += GetByte(v[i], v[i + 1]);

    }
    return out_;

}*/
#pragma endregion

int main(){
   /* _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);*/
    SetLocale();
    fstream f(f_serv_name,ios_base::out, _SH_DENYNO);
   // f.open(f_serv_name, ios_base::out, _SH_DENYNO);
    while (f.is_open() == false) {

    }
    wstring mes;
    while (true) {
        
        getline(wcin, mes);
        if (mes == L"")
            break;
        f << ToSTD_STRING(mes) << endl;
        f.flush();
        f.sync();
    }
    /*wstring f;
    getline(wcin, f);
    wcout << f << endl;
    string enc = ToSTD_STRING(f);
    wstring d = ToSTD_WSTRING(enc);
    wcout << d << endl;*/

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
