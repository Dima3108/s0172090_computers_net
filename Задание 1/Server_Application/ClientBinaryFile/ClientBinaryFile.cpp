// ClientBinaryFile.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
struct Model {
    double I;
    int U, T;

};
void WriteModel(FILE* f, Model m) {
    fwrite((void*)&m, sizeof(Model), 1, f);
    fflush(f);
}
void ReadResult(FILE* f) {
    double v;
    if (fread((void*)&v, sizeof(double), 1, f) !=0) {
        if (v >= 0) {
            std::wcout << L"полная мощность:" << v << L"вт" << std::endl;

        }
        else {
            if (v == -2) {
                std::wcout << L"недопустимое значение периуда , перуд должен быть больше 0" << std::endl;
            }
            else if(v==-3) {
                std::wcout << L"недопустимое значение тока , ток должен быть больше 0" << std::endl;
            }
            else if(v==-4) {
                std::wcout << L"недопустимое значение напряжения , напряжение должно быть больше неравно 0" << std::endl;
            }
            else {
                std::wcout << L"возникла непредвиденная ошибка" << std::endl;
            }
        }
    }
}
const char* path_serv = "Server.bin";
const char* path_client = "Client.bin";
const char* phi_inf= "Сдвиг фаз — разность между начальными фазами двух переменных величин, изменяющихся во времени периодически с одинаковой частотой.\nСдвиг фаз является величиной безразмерной и может измеряться в радианах(градусах) или долях периода.\nПри неизменном, в частности нулевом сдвиге фаз говорят о когерентности двух процессов.\nФазой(фазовым углом) называется угол  phi = 2pi * (t / T), где T — период, t — доля периода смещения по фазе при наложении синусоид друг на друга.\nТак что если кривые(переменные величины — синусоиды : колебания, токи) сдвинуты по отношению друг к другу на четверть периода,\nто мы говорим, что они смещены по фазе на pi / 2(90 *), если на восьмую часть(долю) периода — то,\nзначит, на pi / 4 и т.д.";

void SetLocale() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);
}
int main()
{
    SetLocale();
    Model mod;
    //std::cout << "информация о периуде :\n" << phi_inf <<std:: endl;
    FILE* f_read = _fsopen(path_client, "r", _SH_DENYNO);
    FILE* f_write = _fsopen(path_serv, "w+", _SH_DENYNO);
    std::wstring s;
    while (true) {
        std::wcout << L"Вы хотите завершить программу?(Да/Нет)" << std::endl;
        std::wcin >> s;
        if (s == L"Да") {
            mod.T = STOP_V;
            mod.I = 0;
            mod.U = 0;
            WriteModel(f_write, mod);
            break;
        }
        else {
            std::wcout << L"Введите значения напряжения в вольтах в целочисленном виде" << std::endl;
            std::wcin >> mod.U;
            std::wcout << L"Введите значение тока в амперах (допускается нецалая часть , части разделяются точкой)" << std::endl;
            std::wcin >> mod.I;
            std::wcout << L"Введите значение периуда в секундах в целочисленном виде" << std::endl;
            std::wcin >> mod.T;
            WriteModel(f_write, mod);
            ReadResult(f_read);
        }
    }
    fclose(f_read);
    fclose(f_write);
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
