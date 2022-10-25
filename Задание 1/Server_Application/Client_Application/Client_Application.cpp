// Client_Application.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<string>
#include<fstream>

#include <stdio.h>
#include <stdlib.h>
#include <share.h>

#include"MyText.h"
//using namespace std;
const string i_file = "client.txt";
const string o_file = "server.txt";
const char* f_serv_name = "serv.txt";
const char* f_client_name = "client.txt";
string ReadLine(FILE* f) {
	string ch = "";
	char* sim = new char[1];
	while (fread(sim, sizeof(char), 1, f) == 1) {
if (sim[0] == '\n')
			break;
		ch += sim[0];
		
	}
	delete[]sim;
	return ch;
}
void WriteLine(FILE* f, string message1) {
	string message = message1 + "\n";
	fwrite(message.c_str(), sizeof(char), message.size(), f);
	fflush(f);
	//_flushall();
	message.clear();
}
const wstring commands[] = { L"init",L"get_",L"ext_",L"add_" };
wstring CreateUserComm(wstring user) {
	wstring us = commands[0] + L"<" + user + L">";
	return us;

}
wstring ExitUserComm(wstring user) {
	return commands[2] + L"<" + user + L">";
}
wstring AddBooK(wstring user, wstring book_name, wstring autor_name, int count) {
	wstring c = to_wstring(count);
	
	return commands[3] + L"<" + user + L">" + L"<" + book_name + L">" + L"<" + autor_name + L">" + L"<"+c+L">";

}
wstring GetBooK(wstring user, wstring book_name, wstring autor_name, int count) {
	wstring c = to_wstring(count);

	return commands[1] + L"<" + user + L">" + L"<" + book_name + L">" + L"<" + autor_name + L">" + L"<" + c + L">";

}
bool Contains(wstring mes, wstring val, int offset) {
	if (mes.size() - offset < val.size())
		return false;
	const wchar_t* m = mes.c_str();
	const wchar_t* v = val.c_str();
	for (int i = 0; i < val.size(); i++)
		if (m[offset + i] != v[i])
			return false;
	return true;
}
wstring GetResult(wstring message, int offset) {
	wstring res = L"";
	wstring comm = L"";
	int p = offset + 1;
	const wchar_t* m = message.c_str();
	while (m[p] != L'>') {
		comm += m[p];
		p++;
	}
	p++;
	if (comm == commands[1]||comm==commands[3]) {
		for (; p < message.size(); p++)
			res += m[p];
	}
	return res;
}
int main()
{

	//setlocale(0, "Rus");
	SetLocale();
	fstream f;
	
	FILE* fil = _fsopen(f_serv_name, "a", _SH_DENYNO);
	FILE* fol = _fsopen(f_client_name, "r", _SH_DENYNO);
	int t1=0, t2=0;
	
	wstring en = L"";
	
	wstring fio=L"";
	while (fio == L"") {
wcout << L"Введите ваше фио" << endl;
getline(wcin, fio);
if (fio == L"")
{
	wcout << L"фио не должно быть пустым" << endl;
}
	}
	WriteLine(fil, ToSTD_STRING(CreateUserComm(fio)));
	wstring comm;
	while (true) {
		
		wcout << L"вы хотите добавить книгу?(ДА/НЕТ)" << endl;
		wcin >> comm;
		if (comm == L"ДА") {
			wstring book_name, autor_name;
			int count;
			wcout << L"Введите название книги" << endl;
			//getline(wcin, book_name);
			wcin >> book_name;
			wcout << L"Введите автора книги" << endl;
			wcin >> autor_name;
			wcout << L"Введите количество добавляемых книг (0;256*256*256)" << endl;
			wcin >> count;
			WriteLine(fil, ToSTD_STRING(AddBooK(fio, book_name, autor_name, count)));
		}
		wcout << L"хотите получить книгу? (ДА / НЕТ)" << endl;
			wcin >> comm;
		if (comm == L"ДА") {
			wstring book_name, autor_name;
			int count;
			wcout << L"Введите название книги" << endl;
			//getline(wcin, book_name);
			wcin >> book_name;
			wcout << L"Введите автора книги" << endl;
			wcin >> autor_name;
			wcout << L"Введите количество получаемых книг (0;256*256*256)" << endl;
			wcin >> count;
			WriteLine(fil, ToSTD_STRING(GetBooK(fio, book_name, autor_name, count)));
		}
		string us_i;
		while (true) {
			if ((us_i = ReadLine(fol)) != "") {
				wstring mes = ToSTD_WSTRING(us_i);
				if (Contains(mes, fio, 0)) {
					wcout << GetResult(mes, fio.size()) << endl;
				}
			}
			else
				break;
		}
		wcout << L"Завершить сеанс?(ДА/НЕТ)" << endl;
		wcin >> comm;
		if (comm == L"ДА") {
			WriteLine(fil, ToSTD_STRING(ExitUserComm(fio)));
			break;
		}
		/*	string w = "", w1 = "";
			
			if (en != L"end") {

				w1 = "";

				while ((w1 = ReadLine(fil)) != "") {
					en = ToSTD_WSTRING(w1);
					wcout << en << endl;
				}
				
				}

			}
			else
				break;
		*/
	}
	//f.close();
	return 0;
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
