// HTTP_CHAT.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<WinSock2.h>
#include<sstream>
#include<WS2tcpip.h>
#include<string>
#include<fstream>
#include"UriCoder.h"
#include <string> 
#include <locale> 
#include <codecvt>
#include<vector>
#include <io.h>
#include <fcntl.h>
using namespace std;
using namespace std;
#pragma comment(lib,"Ws2_32.lib")
#pragma warning(suppress : 4996)
u_short MY_PORT = 666;
#define CHAT_PORT 667
#define PRINTNUSERS if(nclients)\
std::cout<<"user online"<<nclients<<endl;\
else std::cout<<"No user online\n";
DWORD WINAPI ConToClient(LPVOID client_socket);
DWORD WINAPI ChatThread(LPVOID id);
int nclients = 0;
SOCKET connections[100];
// string html_content = "";
int main()
{
    setlocale(0, "Rus");
    char buff[1024];
  std::  cout << "TCP ECHO-SERVER \n";
    if (WSAStartup(0x0202, (WSAData*)&buff[0])) {
      std::  cout << "Error WSAStartup \n" << WSAGetLastError();
        return -1;
    }
    SOCKET mysocket;
    if ((mysocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      std::  cout << "Error socket\n" << WSAGetLastError();
        WSACleanup();
        return -1;
    }
    sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(MY_PORT);
    local_addr.sin_addr.s_addr = 0;
    local_addr.sin_addr.s_addr = inet_addr("192.168.1.126");
    if (bind(mysocket, (sockaddr*)&local_addr, sizeof(local_addr))) {
      std::  cout << "Error bind\n" << WSAGetLastError();
        WSACleanup();
        return -2;
    }
    if (listen(mysocket, 0x100)) {
      std::  cout << "Error listen\n" << WSAGetLastError();
        closesocket(mysocket);
        WSACleanup();
        return -3;
    }
   //std:: wcout << L"Waiting connections on port:" << MY_PORT << "\n";
    SOCKET client_socket;
    sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);
 sockaddr_in sers;
    int ssize = sizeof(sers);
    sers.sin_addr.s_addr = inet_addr("192.168.1.126");
    sers.sin_port = htons(CHAT_PORT);
    sers.sin_family = AF_INET;
    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&sers, sizeof(sers));
    listen(sListen, 100);
    while ((client_socket = accept(mysocket, (sockaddr*)&client_addr, &client_addr_size))) {
        
        //connections[nclients++] = client_socket;
        HOSTENT* hst;
        hst = gethostbyaddr((char*)&client_addr.sin_addr.s_addr, 4, AF_INET);
     // std::  cout << "+new connect!\n";
        if (hst);//std::cout << hst->h_name;
        else std::cout << "";
      // std:: cout <<          inet_ntoa(client_addr.sin_addr);
       // PRINTNUSERS
           std:: cout << endl;
        DWORD thID;
        CreateThread(NULL, NULL, ConToClient, &client_socket, NULL, &thID);
    }
   
    SOCKET newConnection;
    for (int i = 0; i < 100; i++) {
        newConnection = accept(sListen, (SOCKADDR*)&sers, &ssize);
        if (newConnection != 0) {
            //std::cout << "new connection";
            connections[i] = newConnection;
            CreateThread(NULL, NULL, ChatThread, &i, NULL, NULL);
        }
    }
    return 0;
}
string obr(string s) {
    int i = s.size() - 1;
    while ( s[i] != '\n') {
        i--;
    }
    i += 1;
    string n = "";
    for (; i < s.size(); i++)
        n += s[i];
    return n;
}
void SetLocale() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);
}

DWORD WINAPI ConToClient(LPVOID client_socket) {
    SOCKET my_sock;
    int len;
    my_sock = ((SOCKET*)client_socket)[0];
    char buff[1024];
    const char apf = '"';
    std::stringstream response, response_body;
    //response_body << html_content;
    /*response_body << " <!DOCTYPE html>\r\n";
    response_body << "<title>" << "Многопоточный сервер"
        << "</title>"
        << "<html>"
        << "<head></head>"
        << "<body>"
        << "<div>"
        << "<button>Эта кнопка ничего не делает , не нажимайте ее.</button>"
        << "</div>"
        << "<h1>Hellow student</h1>" << "\n"
        << "</html><body>\n";*/
    std::ifstream ii("HTMLPage.html");
    while (!ii.eof()) {
        string v;
        getline(ii, v);
         response_body << v;
       // html_content += v;

    }

   
    response << "HTTP/1.1 200 OK\r\n" <<
        "Document folows Date:" << "11:11:11" <<
        "Content-Type: text/html;\r\n" <<
        "charset=utf-8" <<
        "Server:localh\r\n"
        << "Content-Length:" << response_body.str().length() << "\r\n\r\n" << response_body.str();
    //char sHELLO[] = "<html><body>Hellow, Student</body> < / html>\r\n";
    //send(my_sock, sHELLO, sizeof(sHELLO), 0);

    int i = send(my_sock, response.str().c_str(), response.str().length(), 0);
    //std::cout << "#" << i;
    if (i == SOCKET_ERROR) {

    }
   
    while (SOCKET_ERROR != (len = recv(my_sock, (char*)&buff[0], 1024, 0))) {
        if (len > 0) {
            buff[len] = '\0';
            
            string v = "";
            for (int i = 0; i < len; i++)
                v += buff[i];
            cout << "received:" << v << endl;
            string g = obr(v);
            cout << g << endl;
            send(my_sock, g.c_str(), g.length(), 0);
            /*string vl = obr(v);
            const char* val = vl.c_str();
            int len = ((int)(val[0]) * 256) + ((int)val[1]);
            cout << len;*/

            /*if (len == 0) {
                break;
            }*/
        }
       // break;
    }
 
    nclients--;
    cout << "-disconnect\n";
    PRINTNUSERS
        closesocket(my_sock);
    return 0;
}
DWORD WINAPI ChatThread(LPVOID id) {
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
