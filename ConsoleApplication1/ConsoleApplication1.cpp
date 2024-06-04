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

    std::cout << "Далее в каждой строке будут представлены дубликаты файлов" << std::endl;
    FileAnalyzer f{ path_1,path_2 };
    f.exec();

    return 0;
}
