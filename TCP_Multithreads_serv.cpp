// TCP_Multithreads_serv.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include<WinSock2.h>
#include<string>
#pragma comment(lib,"Ws2_32.lib")
#pragma warning(disable:4996)
using namespace std;
u_short MY_PORT = 666;
#define PRINTNUSERS if(nclients)\
cout<<"user online "<<nclients<<endl;\
else cout <<"No user online\n";

DWORD WINAPI ConToClient(LPVOID client_socket);
int nclients = 0;

int main()
{
    char buff[1024];
    if (WSAStartup(0x0202, (WSADATA*)&buff[0])) {
        cout << "Error wsa startrup" << endl;
        return -1;
    }
SOCKET mysocket;
if ((mysocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    cout << "Error socket\n" << WSAGetLastError();
    WSACleanup();
    return -2;
}
sockaddr_in local_addr;
local_addr.sin_family = AF_INET;
local_addr.sin_port = htons(MY_PORT);
local_addr.sin_addr.s_addr = 0;
if (bind(mysocket, (sockaddr*)&local_addr, sizeof(local_addr))) {
    cout << "Error bind\n" << GetLastError();
    closesocket(mysocket);
    WSACleanup();
    return -3;
}
if (listen(mysocket, 0x100)) {
    cout << "Error listen\n" << WSAGetLastError();
    closesocket(mysocket);
    WSACleanup();
    return -4;
}
cout << "Waiting connections\n";
SOCKET client_socket;
sockaddr_in client_addr;
int client_addr_size = sizeof(client_addr);
while ((client_socket = accept(mysocket, (sockaddr*)&client_addr, &client_addr_size))) {
    nclients++;
    HOSTENT* hst;
    hst = gethostbyaddr((char*)&client_addr.sin_addr.s_addr, 4, AF_INET);
    cout << "+newq connect!\n";
    if (hst)cout << hst->h_name;
    else cout << "";
    cout << inet_ntoa(client_addr.sin_addr);
    PRINTNUSERS
        cout << endl;
    DWORD thID;
    CreateThread(NULL, NULL, ConToClient, &client_socket, NULL, &thID);
}
    std::cout << "Hello World!\n";
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
