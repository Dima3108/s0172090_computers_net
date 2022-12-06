// HTTP_CLIENT.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include "winsock2.h"
#define MAX_PACKET_SIZE 4096*10


#pragma comment (lib,"Ws2_32.lib")
std::string request(std::string adres) {
	return "/Index GET HTTP/1.0\r\nHost:" + adres + " \r\n\r\n";
 }
int main()
{
	WSADATA ws;
	SOCKET s;
	sockaddr_in adr;
	hostent* hn;
	char buff[MAX_PACKET_SIZE];
	if (WSAStartup(0x0101, &ws) != 0) {
		return -1;
	}
	if (INVALID_SOCKET == (s = socket(AF_INET, SOCK_STREAM, 0))) {
		return -2;
	}
	std::string site_name;
	std::cin >> site_name;
	if (NULL == (hn = gethostbyname(site_name.c_str()))) {
		return -3;
	}
	adr.sin_family = AF_INET;
	((unsigned long*)&adr.sin_addr)[0] = ((unsigned long**)hn->h_addr_list)[0][0];
	adr.sin_port = htons(80);
	if (SOCKET_ERROR == connect(s, (sockaddr*)&adr, sizeof(adr))) {
		return -4;
	}
	std::string req = request(site_name);
	if (SOCKET_ERROR == send(s, req.c_str(), req.size(), 0)) {
		return -5;
	}
	int len = 0;
	do {
		if (SOCKET_ERROR == (len = recv(s, (char*)buff, MAX_PACKET_SIZE, 0))) {
			return -6;
		}
		buff[len] = 0;
	std::	cout << buff;

	} while (len != 0);
	if (SOCKET_ERROR == closesocket(s)) {
		return -7;
	}
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
