#include <iostream>
#include "FileAnalyzer.h"
#include <Windows.h> // Неодходим для считывания папок на русском

int main()
{
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);

    std::string path_1, path_2;
    std::cout << "Введите первую папку для поиска дубликатов > ";
    std::cin >> path_1;

    std::cout << "Введите вторую папку для поиска дубликатов > ";
    std::cin >> path_2;

    FileAnalyzer f{ path_1,path_2 };
    f.print_vector_of_duplicates();

    return 0;
}
