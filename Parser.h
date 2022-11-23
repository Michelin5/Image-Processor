#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <iostream>

struct FilterOptions {
    std::string filter_name;
    std::vector<std::string> params;
};

struct ParsedInput {
    std::string input_file;
    std::string output_file;
    std::vector<FilterOptions> filter_options;
};

class Parser {
public:
    static ParsedInput Parse(int argc, char **argv);
};