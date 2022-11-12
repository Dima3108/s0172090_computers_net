// server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
//#define CLNT_PORT 1235
#define BUF_SIZE 64
using namespace std;
//const string QUEST = "Who are you?\n";
//#define C 1.0
#define EXIT -2222
struct Model {
    //double I, U, R, FI;
    double U;
    int ID;
};
const double C[] = { 1.0,2.3,0.34,5.82,1,2.31 };
const double FI[] = { 1/1000.0,3.5/1000.0,0.6,1.23/1000.0,3.45/1000.0,1/1000.0 };
const double R[] = { 2,3,0.33,0.33,47,86 };
const double VoltageDrop[] = { 13,34,23,27,17,78 };//Процент падениянапрния
double ValtageOnAnchor(double U, int ID) {//напряжение на якоре
    double on_pr =abs( U) / 100.0;
    return abs(abs(U) - (on_pr*VoltageDrop[ID]));
}
int SCHECK_MODEL(Model model) {
    if (model.ID == EXIT)
        return -3;
   /* if (model.FI <= 0)
        return -1;*/
    if (model.ID < 0||model.ID>5)
        return -2;
    return 0;
}
double SCOR_DV(double U, int ID) {
    double I = ValtageOnAnchor(U, ID) / R[ID];
    return ((abs(U) - (I * R[ID])) / (C[ID] * FI[ID]))*60;
}
string CreateResult(Model m) {
    
    switch (SCHECK_MODEL(m)) {
    case -1:
        return "error in FI";

    case -2:
        return "error in ID";
    case -3:
        return "Bye";
    default:
        return std::to_string(SCOR_DV( m.U, m.ID));
    }
}
/*
* U — подводимое к обмотке якоря напряжение,

  I — ток обмотки якоря,

 R — сопротивление цепи якоря,

 C — конструктивная постоянная,

Phi  — поток, создаваемый обмоткой возбуждения.
*/

int main()
{

    char buff[1024];
    if (WSAStartup(0x0202, (WSADATA*)&buff[0])) {
        cout << WSAGetLastError();
        return -1;
    }
    SOCKET s,s_new;
    int from_len;
   // char buf[BUF_SIZE] = { 0 };
    //char buf[sizeof(Model)] = { 0 };
    Model buf;
    sockaddr_in sin, from_sin;
    s = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(SRV_PORT);
    bind(s, (sockaddr*)&sin, sizeof(sin));
    string msg, msg1;
    listen(s, 10);
    cout << "server run\n";
    while (1) {
        from_len = sizeof(from_sin);
        s_new = accept(s, (sockaddr*)&from_sin, &from_len);
        cout << "new connected client!" << endl;
        //msg = QUEST;
        while (1) {
           // send(s_new, (char*)&msg[0], msg.size(), 0);
           // from_len = recv(s_new, (char*)buf, BUF_SIZE, 0);
            from_len = recv(s_new, (char*)&buf, sizeof(Model), 0);
            string res = CreateResult(buf);
            int size = res.size();
            send(s_new, (char*)&size, sizeof(int), 0);
            send(s_new, (char*)res.c_str(), size, 0);
            if (res == "Bye")
                break;
          /*  buf[from_len] = 0;
            msg1 = (string)buf;
            cout << msg1 << endl;
            if (msg1 == "Bye")
                break;
            getline(cin, msg);*/
        }
        cout << "client is lost";
        closesocket(s_new);
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
