// UDP_server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include<WinSock2.h>
#include<Windows.h>
#include<string>
#include<math.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
using namespace std;
#define PORT 999
#define sHELLO "Hello ,student!\n"
#define PI 3.14
#define ALPHA 1
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
/*
* Электродвижущая сила e генератора переменного тока определяется по формуле:

 e=w2Bl(alpha\2)*omega*sin((2pi*t)\T)
 */
double get_phi(double t,double T) {
	return (2 * PI * t) / T;
}
double get_ads(double number_of_turns, double magnetic_induction, double the_length_of_each_of_the_active_sides_of_the_contour_in_meters,
  double angular_velocity_of_sinusoidal_electromotive_force,double phi) {
	return number_of_turns * magnetic_induction*ALPHA * the_length_of_each_of_the_active_sides_of_the_contour_in_meters * angular_velocity_of_sinusoidal_electromotive_force*sin(phi);
}
string get_ads(Model m) {
	if (m.T == 0)
		return "ошибка деления на ноль";
	double r = get_ads(m.w, m.B, m.l, m.omega, get_phi(m.t, m.T));
	string v = "вольт";
	if (r > 1000.0) {
		r /= 1000.0;
		v = "киловольт";
		
	}
	return "Электродвижущая сила :" + std::to_string(r) + v;
}
int main()
{
	setlocale(0, "Rus");
	char buff[1024];
	if (WSAStartup(0x202, (WSADATA*)&buff)) {
		cout << "WSAStartup error:" << WSAGetLastError() << "\n";
		return -1;
	}
	SOCKET Lsock;
	Lsock = socket(AF_INET, SOCK_DGRAM, 0);
	if (Lsock == INVALID_SOCKET) {
		cout << "soket() error:" << WSAGetLastError();
		WSACleanup();
		return -2;
	}
	sockaddr_in Laddr;
	Laddr.sin_family = AF_INET;
	Laddr.sin_addr.s_addr = INADDR_ANY;
	Laddr.sin_port = htons(PORT);
	if (bind(Lsock, (sockaddr*)&Laddr, sizeof(Laddr))) {
		cout << "BIND ERROR:" << WSAGetLastError();
		closesocket(Lsock);
		WSACleanup();
		return -3;
	}
	Model mod;
	while (true) {
		sockaddr_in Caddr;
		int Caddr_size = sizeof(Caddr);
		int bsize = recvfrom(Lsock,(char*)&mod,sizeof(Model),0,
			
			(sockaddr*)&Caddr, &Caddr_size);
		if (bsize == SOCKET_ERROR) {
			cout << "recvfrom() error:" << WSAGetLastError();
		}
	
		hostent* hst;
		hst = gethostbyaddr((char*)&Caddr.sin_addr, 4, AF_INET);
		cout << "NEW DATAGRAM!\n" << ((hst) ? hst->h_name : "Unknown host") << "\n"
			<< inet_ntoa(Caddr.sin_addr) << "\n" <<
			ntohs(Caddr.sin_port) << '\n';
		
		string v = get_ads(mod);
		int l = v.size();
		sendto(Lsock, (char*)&l, sizeof(int), 0, (sockaddr*)&Caddr, sizeof(Caddr));
		sendto(Lsock, v.c_str(), v.size(), 0, (sockaddr*)&Caddr, sizeof(Caddr));
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
