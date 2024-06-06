#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <unordered_set>
#include <boost/filesystem.hpp>
#include <fstream>


class FileAnalyzer {

private:
	boost::filesystem::path first_directory;

	boost::filesystem::path second_directory;

public:
	FileAnalyzer() = delete;

	FileAnalyzer(std::string first_path, std::string second_path);

	void print_vector_of_duplicates();

	std::vector<std::vector<std::string>> get_duplicates(std::vector<std::string>& filenames);

	std::vector<std::string> get_all_filenames();

	bool are_files_equal(std::string first_path_to_file, std::string second_path_to_file);

};