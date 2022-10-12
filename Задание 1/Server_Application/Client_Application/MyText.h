#pragma once
#pragma once
#include<string.h>
#include <io.h>
#include <fcntl.h>
#include<iostream>
using namespace std;

typedef unsigned char byte;
#define T_Length 16
void SetLocale();
string ToSTD_STRING(wstring t);
byte GetByte(wchar_t x, wchar_t y);
byte GetByte(char x, char y);
wstring ToSTD_WSTRING(string t);