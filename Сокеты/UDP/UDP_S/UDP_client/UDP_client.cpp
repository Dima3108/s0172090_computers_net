// UDP_client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<string>
#include<Windows.h>
#include<iostream>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
using namespace std;
#define PORT 999
#define SERVERADDR "127.0.0.1"
struct Model {
	double w, B, l, omega, T, t;
};
/*
* w — количество витков;

B — магнитная индукция магнитного поля в вольт-секундах на квадратный метр (Тл, Тесла);

l — длина каждой из активных сторон контура в метрах;

omega  — угловая скорость синусоидальной электродвижущей силы, в данном случае равная угловой скорости вращения магнита в контуре;

omegat — фаза синусоидальной электродвижущей силы.
*/
int main()
{
	setlocale(0, "Rus");
	char buff[10 * 1014];
	cout << "Use quit to exit \n";
	if (WSAStartup(0x202, (WSADATA*)&buff)) {
		cout << "WSAStartup error:" << WSAGetLastError() << "\n";
		return -1;
	}
	SOCKET my_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (my_sock == INVALID_SOCKET) {
		cout << "SOCKET() error:" << WSAGetLastError() << endl;
		WSACleanup();
		return -2;
	}
	sockaddr_in Daddr;
	Daddr.sin_family = AF_INET;
	Daddr.sin_port = htons(PORT);
	hostent* hst;
	if (inet_addr(SERVERADDR))
		Daddr.sin_addr.s_addr = inet_addr(SERVERADDR);
	else
		if (hst = gethostbyname(SERVERADDR))
			Daddr.sin_addr.s_addr = ((unsigned long**)hst->h_addr_list)[0][0];
		else
		{
			cout << "Unknown host:" << WSAGetLastError() << "\n";
			closesocket(my_sock);
			WSACleanup();
			return -3;
		}
	Model m;
	const string d = "(допускает нецелое значение , нецелая часть отделяется точкой)";
	while (true) {
		/*cout << "S<=C:";
		string SS;
		getline(cin, SS);
		if (SS == "quit")
			break;*/
		//sendto(my_sock, (char*)&SS[0], SS.size(), 0, (sockaddr*)&Daddr, sizeof(Daddr));
		cout << "введите количество витков (отрицальное значение для завершения работы)" << endl;
		cin >> m.w;
		if (m.w < 0)
			break;
		cout << "введите магнитную индукцию магнитного поля Тесла"<<d<<endl;
		cin >> m.B;
		cout << "введите длину каждой из активных сторон контура в метрах"<<d << endl;
		cin >> m.l;
		cout << "введите угловая скорость синусоидальной электродвижущей силы" << d << endl;
		cin >> m.omega;
		cout << "t и T используются в следующей формуле ((2pi*t)\T) вводите их исходя из формулы" << endl;
		cout << "введите t"<<endl;
		cin >> m.t;
		cout << "введите T" << endl;
		cin >> m.T;
		sendto(my_sock, (char*)&m, sizeof(Model), 0, (sockaddr*)&Daddr, sizeof(Daddr));
		sockaddr_in SRaddr;
		int SRaddr_size = sizeof(SRaddr);
		int l = 0;
		int n = recvfrom(my_sock, (char*)&l, sizeof(int),0,
			//buff, sizeof(buff), 0, 
			(sockaddr*)&SRaddr, &SRaddr_size);

		if (n == SOCKET_ERROR) {
			cout << "recvfrom() error:" << WSAGetLastError() << "\n";
			closesocket(my_sock);
			WSACleanup();
			return -4;
		}
		else {
			//cout << l << endl;
			char* b = new char[l];
			n = recvfrom(my_sock, b, l, 0, (sockaddr*)&SRaddr, &SRaddr_size);
			if (n == SOCKET_ERROR) {
				cout << "recvfrom() error:" << WSAGetLastError() << "\n";
				closesocket(my_sock);
				WSACleanup();
				delete[]b;
				return -5;
			}
			for (int i = 0; i < l; i++)
				cout << b[i];
			cout << endl;
			delete[]b;
		}
		//buff[n] = '\0';
		//cout << "S=>C:" << buff << "\n";
	}
	closesocket(my_sock);
	WSACleanup();
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
