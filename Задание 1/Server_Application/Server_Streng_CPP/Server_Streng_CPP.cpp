// Server_Streng_CPP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
#include"MyText.h"
const char* f_serv_name = "serv.txt";
const char* f_client_name = "client.txt";
//using namespace std;
//const wchar_t* alphavit = L"abcdifghtrqwzxp";
//const char* alphavit_char = "abcdifghtrqwzxp";
//typedef unsigned char byte;
//#define T_Length 16
/*wstring EncodeText(wstring t) {
    const wchar_t* v = t.c_str();
    wstring out_;
    out_ += L"";
    for (int n = 0; n < t.length(); n++) {
        byte f = v[n]/256;
        out_ += alphavit_wchar[f / T_Length];
        out_ += alphavit_wchar[f % T_Length];
        f = v[n] % 256;
        out_ += alphavit_wchar[f / T_Length];
        out_ += alphavit_wchar[f % T_Length];
    }
   
    return out_;
}*/
/*byte GetByte(wchar_t x, wchar_t y) {
    int f = 0;
    for (int i = 0; i < T_Length; i++) {
        if (alphavit[i] == x) {
            f = T_Length * i;
            break;
        }
    }
    for (int i = 0; i < T_Length; i++) {
        if (alphavit[i] == y) {
            f += i;
            break;
        }
    }
    return (byte)f;
}*/
/*wstring DecodeText(wstring t) {
    const wchar_t* v = t.c_str();
    wstring out_ = L"";
    
    //out_ += (wchar_t)"";
    for (int i = 0; i < t.length(); i += 4) {
        byte b1= GetByte(v[i], v[i + 1]);
        byte b2 = GetByte(v[i + 2], v[i + 3]);
        wchar_t sim= (256 * b1) + b2;
        out_ += sim;
    }
    return out_;

}*/
#pragma region String_
/*string EncodeText(string t) {
    const char* v = t.c_str();
    string out_;
    out_ += "";
    for (int n = 0; n < t.length(); n++) {
        byte f = v[n]; //;/ 256;
        out_ += alphavit_char[f / T_Length];
        out_ += alphavit_char[f % T_Length];
        
    }
    
    return out_;
}*/
/*byte GetByte(char x, char y) {
    int f = 0;
    for (int i = 0; i < T_Length; i++) {
        if (alphavit[i] == x) {
            f = T_Length * i;
            break;
        }
    }
    for (int i = 0; i < T_Length; i++) {
        if (alphavit[i] == y) {
            f += i;
            break;
        }
    }
    return (byte)f;
}*/
/*string DecodeText(string t) {
    const char* v = t.c_str();
    string out_ = "";

   
    for (int i = 0; i < t.length(); i += 2) {
        
        out_ += GetByte(v[i], v[i + 1]);

    }
    return out_;

}*/
#pragma endregion
void WriteLine(FILE* f, string message1) {
    string message = message1 + "\n";
    fwrite(message.c_str(), sizeof(char), message.size(), f);
    fflush(f);
   // _flushall();
    message.clear();
}
string ReadLine(FILE* f) {
    string ch = "";
    char* sim = new char[1];
    while (fread(sim, sizeof(char), 1, f) == 1) {
        if (sim[0] == '\n')
            break;
        ch += sim[0];

    }
    delete[]sim;
    return ch;
}
const wstring commands[] = { L"init",L"get_",L"ext_",L"add_"};
struct Book
{
    wstring b_name, b_autor;
    int count;
};
int ParseCommand(wstring comm) {
    
    if (comm.size() < 4)
        return -1;
   const wchar_t* chars_ = comm.c_str();
   wstring c=L"";
   for (int i = 0; i < 4; i++)
       c += chars_[i];
   for (int w = 0; w < 4; w++)
       if (c == commands[w])
           return w;
   return -2;
}
void AddUser(vector<wstring>& users, wstring user) {
    //init<US_NAME>
    const wchar_t* us = user.c_str();
    wstring n_u = L"";
    for (int i = 5; i < user.size() - 1; i++) {
        n_u += us[i];
    }
    users.push_back(n_u);
    wcout << L"пользователь " << n_u << L" вошел" << endl;
}
vector<wstring> DeleteUser(vector<wstring>& users, wstring user) {
    const wchar_t* us = user.c_str();
    wstring n_u = L"";
    for (int i = 5; i < user.size() - 1; i++) {
        n_u += us[i];
    }
    vector<wstring>n_users;
    for (int i = 0; i < users.size(); i++
        ) {
        if (users[i] != n_u) {
            
            n_users.push_back(users[i]);
        }
        else {
            wcout << L"пользователь " << n_u << L" вышел" << endl;
        }
    }
    return n_users;
}
void AddBook(vector<Book>& books, wstring info,FILE *f) {
    const wchar_t* inf = info.c_str();
    //commands[3] + L"<" + user + L">" + L"<" + book_name + L">" + L"<" + autor_name + L">" + L"<"+c+L">";
    //add_<
    int pos = 5;
    wstring us = L"";
    while (inf[pos] != L'>') {
        us += inf[pos];
        pos++;
    }
    pos += 2;
    wstring book_n = L"";
    while (inf[pos] != L'>') {
        book_n += inf[pos];
        pos++;
    }
    pos += 2;
    wstring autor_n = L"";
    while (inf[pos] != L'>') {
        autor_n += inf[pos];
        pos++;
    }
    pos += 2;
    wstring count_n = L"";
    while (inf[pos] != L'>') {
        count_n += inf[pos];
        pos++;
    }
    int count_ = stoi(count_n);
    Book book;
    book.b_autor = autor_n;
    book.b_name = book_n;
    book.count = count_;
    wcout << L"Пользователь" << us << L" добавил " << count_n << ((count_ == 1) ? L"книгу:" : L"книг:")<<book.b_name <<L" автора:"<<book.b_autor<< endl;
    WriteLine(f, ToSTD_STRING(us + L"<" + commands[3] + L">"+L"книги получены"));
    if (books.size() == 0) {
        books.push_back(book);
    }
    else {
 bool nal = false;
        for (int i = 0; i < books.size(); i++) 
        {
          if (books[i].b_autor == book.b_autor && books[i].b_name == book.b_name) 
          {
         books[i].count += book.count;
         nal = true;
         break;
          }
        }
        if (!nal) {
            books.push_back(book);
        }
    }
   

}
wstring GetBook(vector<Book>&books, wstring info) {
    const wchar_t* inf = info.c_str();
    //commands[3] + L"<" + user + L">" + L"<" + book_name + L">" + L"<" + autor_name + L">" + L"<"+c+L">";
    //add_<
    int pos = 5;
    wstring us = L"";
    while (inf[pos] != L'>') {
        us += inf[pos];
        pos++;
    }
    pos += 2;
    wstring book_n = L"";
    while (inf[pos] != L'>') {
        book_n += inf[pos];
        pos++;
    }
    pos += 2;
    wstring autor_n = L"";
    while (inf[pos] != L'>') {
        autor_n += inf[pos];
        pos++;
    }
    pos += 2;
    wstring count_n = L"";
    while (inf[pos] != L'>') {
        count_n += inf[pos];
        pos++;
    }
    int count_ = stoi(count_n);
    Book book;
    book.b_autor = autor_n;
    book.b_name = book_n;
    book.count = count_;
    wcout << L"пользователю :" << us << L" отправлена информация о книге :" << book.b_name << L"автора:" << book.b_autor << endl;
    int result_com = -1;
    for (int i = 0; i < books.size(); i++) {
        if (books[i].b_autor == book.b_autor && books[i].b_name == book.b_name) {
            if (books[i].count >= book.count) {
                result_com = 0;
                books[i].count -= book.count;
            }
            else {
                result_com = books[i].count;
                books[i].count = 0;
            }
            break;
        }
    }
    if (result_com == 0) {
        return us+ L"<" + commands[1] + L">" + L"книги:"+book.b_name+L" -отправлены ";
    }
    else {
        if (result_com == -1) {
            return us+L"<"+commands[1]+L">" + L"книги указанные:" + us + L"- отсутствуют";
        }
        else {
            return us+ L"<" + commands[1] + L">" + L"книги:" + book.b_name + L" -отправлены в количестве:"+to_wstring(result_com);
        }
    }
}
int main(){
   /* _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);*/
    SetLocale();
    /*fstream f(f_serv_name, ios_base::out, _SH_DENYNO);
   
    while (f.is_open() == false) {
        
    }*/

    FILE* f_read = _fsopen(f_serv_name, "r", _SH_DENYNO);
    FILE* f_write = _fsopen(f_client_name, "a", _SH_DENYNO);
    vector<wstring>users_;

    wstring mes;
   /* while (true) {
        
        getline(wcin, mes);
        if (mes == L"") {
            f << ToSTD_STRING(L"end") << endl;
            f.sync();
 break;
        }
           
        f << ToSTD_STRING(mes) << endl;
       
        f.sync();
    }*/
    string read_comm;
    wcout << L"сервер запущен" << endl;
    vector<Book>books;
    while (true) {
        while ((read_comm = ReadLine(f_read)) != "") {
            int command_ = ParseCommand(ToSTD_WSTRING(read_comm));
            if (command_ < 0) {
                wcout << "нераспознаная команда" << endl;
            }
            else {
                wstring str = ToSTD_WSTRING(read_comm);
                switch (command_)
                {
                case 0:
                    AddUser(users_, str);
                    break;
                case 1:
                   
                    WriteLine(f_write, ToSTD_STRING(GetBook(books, str)));
                    break;
case 2:
 users_=   DeleteUser(users_, str);
                    break;
case 3:
    AddBook(books, str,f_write);
    break;
                }
                
            }
        }
    }
    fclose(f_read);
    fclose(f_write);
    /*wstring f;
    getline(wcin, f);
    wcout << f << endl;
    string enc = ToSTD_STRING(f);
    wstring d = ToSTD_WSTRING(enc);
    wcout << d << endl;*/

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
