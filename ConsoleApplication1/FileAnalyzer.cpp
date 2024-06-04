#include "FileAnalyzer.h"


FileAnalyzer::FileAnalyzer(std::string path_1, std::string path_2) {
	this->first_path = path_1;
	this->second_path = path_2;
}

void FileAnalyzer::exec() {
    try {
        compare_files();
        print_duplicates();
    }
    catch (std::exception e) {
        std::cout << "Путь к папкам введен неверно!";
    }
}

bool FileAnalyzer::compare_bin_files(std::string first_file_s, std::string second_file_s) {
    char first_symb, second_symb;
    bool result = true;

    std::ifstream first_file;
    first_file.open(first_file_s, std::ios::binary);

    std::ifstream second_file;
    second_file.open(second_file_s, std::ios::binary);

    while (first_file.get(first_symb) && second_file.get(second_symb)) {
        if (first_symb != second_symb) {
            result = false;
            break;
        }
    }
    
    if (first_file.get(first_symb)) result = false;
    if (second_file.get(second_symb)) result = false;
    
    first_file.close();
    second_file.close();
    
    return result;
}

void FileAnalyzer::print_duplicates(){
    if (duplicates.empty()) {
        std::cout << "Дубликаты отсутствуют!";
        return;
    }
    std::cout << "Список дубликатов:" << std::endl;
    for (auto& val : duplicates) {
        std::cout << std::endl << val.first << " -> ";
        for (auto& dup : val.second) {
            std::cout << dup << "  ";
        }
        std::cout << std::endl;
    }
}

void FileAnalyzer::find_duplicates_in_dir(boost::filesystem::path path_to_file, boost::filesystem::path path_to_dir) {

    boost::filesystem::directory_iterator end_iter;

    std::string file_param = "";
    std::string dir_param = "";

    if (path_to_file.parent_path().string() == this->first_path) {
        file_param = "1";
    }
    else {
        file_param = "2";
    }

    if (path_to_dir.string() == this->first_path) {
        dir_param = "1";
    }
    else {
        dir_param = "2";
    }

    if (duplicates.find(file_param + "/" + path_to_file.filename().string()) == duplicates.end()) duplicates[file_param + "/" + path_to_file.filename().string()] = {};
    
    checked_files.emplace(path_to_file.filename().string() + file_param);

    for (boost::filesystem::directory_iterator dir_iter(path_to_dir); dir_iter != end_iter; ++dir_iter) {

        if (checked_files.find(dir_iter->path().filename().string() + dir_param) != checked_files.end()) {
            continue;
        }

        boost::filesystem::path path_2(dir_iter->path());

        bool is_equal = compare_bin_files(path_to_file.string(), path_2.string());

        if (is_equal) {
            checked_files.emplace(path_2.filename().string() + dir_param);
            duplicates[file_param + "/" + path_to_file.filename().string()].push_back(dir_param + "/" + path_2.filename().string());
        }
    }

    if (duplicates[file_param + "/" + path_to_file.filename().string()].size() == 0)  duplicates.erase(file_param + "/" + path_to_file.filename().string());
}

void FileAnalyzer::compare_files() {

    boost::filesystem::path first_dir(first_path);
    boost::filesystem::path second_dir(second_path);
    boost::filesystem::directory_iterator end_iter;
    
    // Перебираем файлы из первой директории

    for (boost::filesystem::directory_iterator dir_iter(first_dir); dir_iter != end_iter; ++dir_iter) {
        if (checked_files.find(dir_iter->path().filename().string() + "1") != checked_files.end()) {
            continue;
        }
        boost::filesystem::path path_1(dir_iter->path());

        find_duplicates_in_dir(path_1, first_dir);
        find_duplicates_in_dir(path_1, second_dir);
        
    }

    // Перебирааем файлы из второй директории

    for (boost::filesystem::directory_iterator dir_iter(second_dir); dir_iter != end_iter; ++dir_iter) {
        if (checked_files.find(dir_iter->path().filename().string() + "2") != checked_files.end()) {
            continue;
        }
        boost::filesystem::path path_1(dir_iter->path());

        find_duplicates_in_dir(path_1, second_dir);

    }
}


