#include "FileAnalyzer.h"


FileAnalyzer::FileAnalyzer(std::string first_path, std::string second_path) : first_directory{ first_path }, second_directory{ second_path }{}

void FileAnalyzer::print_vector_of_duplicates() {
    std::vector<std::string> filenames = this->get_all_filenames();
    std::vector<std::vector<std::string>> duplicates = this->get_duplicates(filenames);
    if (duplicates.size() == 0) {
        std::cout << "Дубликатов не найдено!";
    }
    else {
        std::cout << "\nСписок дубликатов:\n" << std::endl;
        for (auto& equal_files : duplicates) {
            std::cout << equal_files.size() << " ->" << std::endl << std::endl;
            for (auto& file : equal_files) {
                std::cout << file << std::endl;
            }
            std::cout << std::endl;
        }
    }

}

std::vector<std::string> FileAnalyzer::get_all_filenames() {

    boost::filesystem::directory_iterator end_iter;
    std::vector<std::string> filenames;

    for (boost::filesystem::directory_iterator dir_iter(this->first_directory); dir_iter != end_iter; ++dir_iter) {
        filenames.push_back(dir_iter->path().string());
    }
    for (boost::filesystem::directory_iterator dir_iter(this->second_directory); dir_iter != end_iter; ++dir_iter) {
        filenames.push_back(dir_iter->path().string());
    }
    return filenames;
}

std::vector<std::vector<std::string>> FileAnalyzer::get_duplicates(std::vector<std::string>& filenames) {

    std::vector<bool> is_file_checked(filenames.size(), false);
    std::vector<std::vector<std::string>> duplicates;

    for (int i = 0; i < filenames.size(); ++i) {
        if (is_file_checked[i]) {
            continue;
        }

        std::vector <std::string> equal_files;
        for (int j = i + 1; j < filenames.size(); ++j) {
            if (!is_file_checked[j] && are_files_equal(filenames[i], filenames[j])) {
                equal_files.push_back(filenames[j]);
                is_file_checked[j] = true;
            }
        }
        if (!equal_files.empty()) {
            equal_files.push_back(filenames[i]);
            duplicates.emplace_back(equal_files);
        }
        is_file_checked[i] = true;
    }

    return duplicates;
}

bool FileAnalyzer::are_files_equal(std::string first_path_to_file, std::string second_path_to_file) {
    std::ifstream first_file;
    first_file.open(first_path_to_file, std::ios::binary);

    std::ifstream second_file;
    second_file.open(second_path_to_file, std::ios::binary);

    boost::filesystem::path first_file_in_path_format{ first_path_to_file }, second_file_in_path_format{ second_path_to_file };
    if (boost::filesystem::file_size(first_file_in_path_format) != boost::filesystem::file_size(second_file_in_path_format)) {
        first_file.close();
        second_file.close();
        return false;
    }
    char first_symb, second_symb;
    bool result = true;

    while (first_file.get(first_symb) && second_file.get(second_symb)) {
        if (first_symb != second_symb) {
            result = false;
            break;
        }
    }
    
    first_file.close();
    second_file.close();
    
    return result;
}





