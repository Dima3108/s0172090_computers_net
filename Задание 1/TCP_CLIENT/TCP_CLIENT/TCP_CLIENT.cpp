// TCP_CLIENT.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<WinSock.h>
#include<Windows.h>
#include<string>
#pragma comment(lib,"Ws2_32.lib")
using namespace std;
#define SRV_HOST "localhost"
#define SRV_PORT 1234
#define CLNT_PORT 1235
#define BUF_SIZE 64
#pragma warning(suppress : 4996)
int main()
{
	char buff[1024];
	if (WSAStartup(0x0202, (WSADATA*)&buff[0])) {
		cout << "Error WSAStartup\n" << WSAGetLastError();
		return -1;
	}
	SOCKET s;
	int from_len;
	char buf[BUF_SIZE] = { 0 };
	hostent* hp;
	sockaddr_in clnt_sin, srv_sin;
	s = socket(AF_INET, SOCK_STREAM, 0);
	clnt_sin.sin_family = AF_INET;
	clnt_sin.sin_addr.s_addr = 0;
	clnt_sin.sin_port = htons(CLNT_PORT);
	bind(s, (sockaddr*)&clnt_sin, sizeof(clnt_sin));
	hp = gethostbyname(SRV_HOST);
	srv_sin.sin_port = htons(SRV_PORT);
	srv_sin.sin_family = AF_INET;
	((unsigned long*)&srv_sin.sin_addr)[0] = ((unsigned long**)hp->h_addr_list)[0][0];
	connect(s, (sockaddr*)&srv_sin, sizeof(srv_sin));
	string mst;
	do {
		from_len = recv(s, (char*)&buf, BUF_SIZE, 0);
		buf[from_len] = 0;
		cout << buf << endl;
		getline(cin, mst);
		int msg_size = mst.size();
		send(s, (char*)&mst[0], msg_size,0);
	} while (mst!="Bye");
	cout << "exit" << endl;
	closesocket(s);
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
