// ServerBinaryFile.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include<string>
#include<string.h>
#include<vector>

#include<fstream>
#include<locale>

#include <stdio.h>
#include <stdlib.h>
#include <share.h>
#include<math.h>

#include <io.h>
#include <fcntl.h>
#define PI 3.14
#define STOP_V -23
/*P_active=U*I*cos(phi)*/
double GetActiveP(double U, double I, double phi) {
    return U * I * cos(phi);
}
/*P_reactive=U*I*sin(phi)*/
double GetReactiveP(double U, double I, double phi) {
    return U * I * sin(phi);
}
/*P_total=sqrt(P_active^2+P_reactive^2)*/
double GetTotalP(double active_p, double reactive_p) {
    return sqrt(pow(active_p, 2.0) + pow(reactive_p, 2.0));
}
/*
Сдвиг фаз — разность между начальными фазами двух переменных величин, изменяющихся во времени периодически с одинаковой частотой.
Сдвиг фаз является величиной безразмерной и может измеряться в радианах (градусах) или долях периода.
При неизменном, в частности нулевом сдвиге фаз говорят о когерентности двух процессов.
Фазой (фазовым углом) называется угол  phi =2pi*(t/T), где T — период, t — доля периода смещения по фазе при наложении синусоид друг на друга.
Так что если кривые (переменные величины — синусоиды: колебания, токи) сдвинуты по отношению друг к другу на четверть периода, 
то мы говорим, что они смещены по фазе на pi/2(90*), если на восьмую часть (долю) периода — то, 
значит, на pi/4 и т. д.*/
double GetPhi(int T) {
    return 2 * PI * (1 / T);
}
struct Model {
    double I;
    int U,T;

};
Model ReadModel(FILE* f,int &result) {
    Model m;
    int r;
    if ((r=fread(((void*)&m), sizeof(Model), 1, f) )!=0)
    {
        result = 0;
    }
    else {
        if(r!=0)
        std::cout << r << std::endl;
        result = -1;
    }
    return m;
}
double GetTotalP(Model m) {
    
    if (m.T <= 0)
        return -2;
    if (m.I <= 0)
        return -3;
    if (m.U == 0)
        return -4;
    double phi = GetPhi(m.T);
    return GetTotalP(GetActiveP(m.U, m.I, phi), GetReactiveP(m.U, m.I, phi));

}
void WriteP(FILE* f, double value) {
    fwrite((void*)&value, sizeof(double), 1,f);
    fflush(f);
}
const char* path_serv = "Server.bin";
const char* path_client = "Client.bin";
void SetLocale() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);
}
int main()
{
    FILE* f_read = _fsopen(path_serv, "r", _SH_DENYNO);
    FILE* f_write = _fsopen(path_client, "w+", _SH_DENYNO);
    Model mod;
    int res;
    std::cout << "server run" << std::endl;
    //std::cout << sizeof(Model) << std::endl;
    while (true) {
        mod = ReadModel(f_read, res);
        if (res == 0) {
            std::cout << "read data" << std::endl;
            if (mod.T == STOP_V)
            {
                std::cout << "server close" << std::endl;
                break;
            }
            else {
                WriteP(f_write, GetTotalP(mod));
                std::cout << "data writed" << std::endl;
            }
        }
    }
    fclose(f_read);
    fclose(f_write);
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
