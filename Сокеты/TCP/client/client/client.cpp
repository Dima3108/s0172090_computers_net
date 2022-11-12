// client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include<string>
#include<Windows.h>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

#define SRV_HOST "localhost"
#define SRV_PORT 1234
#define CLNT_PORT 1235
#define BUF_SIZE 64
using namespace std;
/*struct Model {
    double I, U, R, FI;

};*/
struct Model {
    //double I, U, R, FI;
    double U;
    int ID;
};
int main()
{
    setlocale(0, "Rus");
    char buff[1024];
    if (WSAStartup(0x0202, (WSADATA*)&buff[0])) {
      std::  cout << WSAGetLastError();
        return -1;
    }
    SOCKET s;
    int from_len;
    char buf[BUF_SIZE] = { 0 };
    hostent* hp;
    sockaddr_in clnt_sin,srv_sin;
    s = socket(AF_INET, SOCK_STREAM, 0);
    clnt_sin.sin_family = AF_INET;
    clnt_sin.sin_addr.s_addr == 0;
    clnt_sin.sin_port = htons(CLNT_PORT);
    bind(s, (sockaddr*)&clnt_sin, sizeof(clnt_sin));
    hp = gethostbyname(SRV_HOST);
    srv_sin.sin_port = htons(SRV_PORT);
    srv_sin.sin_family = AF_INET;
    ((unsigned long*)&srv_sin.sin_addr)[0] = ((unsigned long**)hp->h_addr_list)[0][0];
    connect(s, (sockaddr*)&srv_sin, sizeof(srv_sin));
    string mst;
    Model mod;
   std:: cout << "Программа вычисляет количество оборотов в минуту для электродвигателя постоянного тока.\n"<<
        "Поток, создаваемый обмоткой возбуждения и  сопротивление цепи якоря беруться в качестве константных велмчин и хранятся на сервере.\n "<<
        "Возможна погрешность результата , выдоваемого программой ." << endl;
    while (true)
    {

    
   
       std:: cout << "Хотите завершить работу\n(Y(Да)/N(Нет))";
        string v;
        cin >> v;
        if (v == "N") {
           std:: cout << "Введите напряжение подводимое к обмотке якоря \n";
            cin >> mod.U;
            std::cout << "Введите позицию двигателя [0;5]  \n";
            cin >> mod.ID;
           /* cin >> mod.I;
            cout << "Введите сопротивление обмотки якоря \n";
            cin >> mod.R;
            cout << "Введите поток, создаваемый обмоткой возбуждения FI\n";
            cin >> mod.FI;*/
        }
        else {
            mod.ID = -2222;
        }
        send(s, (char*)&mod, sizeof(Model), 0);
        int size=0;
        recv(s, (char*)&size, sizeof(int), 0);
        
     
        char* res = new char[size];
        recv(s, res, size, 0);
        string s = "";
        for (int i = 0; i < size; i++)
            s+= res[i];
     std::   cout << "Скорость двигателя :";
     std::   cout <<s;
     std::   cout << "обр/мин\n";
        delete[]res;
        if (s == "Bye")
            break;

    } 
  
 std::   cout << "exit" << endl;
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
