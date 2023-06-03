#pragma once
#include <queue>
#include <string>
#include <vector>

struct Scanner {
	std::queue<std::string> tokens;
	void scan(std::string f_name);
	std::string pop(int n);
};

std::vector<std::string> scan_line(std::string line);
