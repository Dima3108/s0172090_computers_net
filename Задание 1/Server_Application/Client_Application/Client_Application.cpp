// Client_Application.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<string>
#include<fstream>
#include"MyText.h"
//using namespace std;
const string i_file = "client.txt";
const string o_file = "server.txt";
const char* f_serv_name = "serv.txt";
const char* f_client_name = "client.txt";
int main()
{

	//setlocale(0, "Rus");
	SetLocale();
	fstream f;
	//f.open(f_serv_name, ios_base::in, _SH_DENYNO);
	
	int t1=0, t2=0;
	while (true) {
		f.open(f_serv_name, ios_base::in, _SH_DENYNO);
		while (f.is_open()==false)
	{

	}
		//f.sync();
		//t2 = f.tellg();
		//if (t1 != t2) {


			string w,w1="";
			//t2 = f.tellg();
			//if (t1 != t2) {
			if (f.tellg() > t1) {
				f.seekg(t1);
				w1 = "";

				//while (!f.eof()) {
				getline(f, w);
				if (w != "") {
					wcout << "read" << endl;
					w1 = w;
					t1 += w.length();
					w = "";
				}
				//f.flush();
				//}
				if (w1 != "") {
					wcout << ToSTD_WSTRING(w) << endl;
					//f.flush();
				}
				//t1 = t2;
			//}
			//while (!f.eof()) {
				/*getline(f, w);
				if (w != "") {
					wcout << ToSTD_WSTRING(w) << endl;

				}
				f.flush();*/
				//}
				//f.flush();
				//t1 = t2;
			//}
			}
		f.close();
	}
	
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
