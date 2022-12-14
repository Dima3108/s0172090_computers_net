#include"UriCoder.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
string urlEncode(string str) {
	string new_str = "";
	char c;
	int ic;
	const char* chars = str.c_str();
	char bufHex[10];
	int len = strlen(chars);
	for (int i = 0; i < len; i++) {
		c = chars[i];
		ic = c;
		if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
			new_str += c;
		else {
			sprintf(bufHex, "%X", c);
			if (ic < 16)
				new_str += "%0";
			else
				new_str += "%";
			new_str += bufHex;
		}
	}
	return new_str;
}
string urlDecode(string str) {
	string ret;
	char ch;
	int i, ii, len = str.length();
	for (i = 0; i < len; i++) {
		if (str[i] != '%') {
			if (str[i] == '+')
				ret += ' ';
			else
				ret += str[i];
		}
		else {
			sscanf(str.substr(i + 1, 2).c_str(), "%x", &ii);
			ch = static_cast<char>(ii);
			ret += ch;
			i = i + 2;
		}
	}
	return ret;
}