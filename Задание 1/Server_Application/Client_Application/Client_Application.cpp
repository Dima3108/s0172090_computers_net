// Client_Application.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<string>
#include<fstream>
using namespace std;
const string i_file = "client.txt";
const string o_file = "server.txt";
int main()
{
	setlocale(0, "Rus");
	ofstream ser_file(o_file);
	while (!ser_file.is_open())
	{

	}
	ifstream client_file(i_file);
	while (!client_file.is_open()) {

	}
	string command = "";string o_data="";
	command += "4";
	ser_file << command << endl;
	ser_file.flush();
	while (client_file.eof()) {

	}
	while (!client_file.eof()) {
while (getline(client_file,o_data)) {
		cout << o_data;
	}
	}
	
	cout << endl;
	while (true)
	{
		if (getline(cin, command)) {
ser_file << command << endl;
		ser_file.flush();
		while (client_file.eof()) {

		}
		while (!client_file.eof()) {
while (getline(client_file, o_data)) {
			cout << o_data;
		}
		}
		}
		
		
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
