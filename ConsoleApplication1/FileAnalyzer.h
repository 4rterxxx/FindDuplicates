#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <unordered_set>
#include <boost/filesystem.hpp>
#include <fstream>
#include <exception>

class FileAnalyzer {
public:
	FileAnalyzer() = delete;

	FileAnalyzer(std::string path_1, std::string path_2);

	void exec();

private:
	void compare_files();

	void find_duplicates_in_dir(boost::filesystem::path path_to_file, boost::filesystem::path path_to_dir);

	bool compare_bin_files(std::string first_file_s, std::string second_file_s);

	void print_duplicates();

private:
	std::string first_path;

	std::string second_path;

	std::unordered_set<std::string> checked_files;

	std::map<std::string, std::vector<std::string>> duplicates;

};