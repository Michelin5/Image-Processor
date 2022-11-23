#include "Parser.h"

ParsedInput Parser::Parse(int argc, char **argv) {
    ParsedInput returned;
    if (argc == 1) {
        std::cout << "no parameters" << std::endl;
        return returned;
    }
    int i = 1;

    std::string current_filter;
    std::vector<std::string> current_params;

    while (i < argc) {
        std::string s = argv[i];
        if (i == 1) {
            returned.input_file = s;
        } else if (i == 2) {
            returned.output_file = s;
        } else if (s[0] == '-') {
            FilterOptions new_filter;
            new_filter.filter_name = current_filter;
            new_filter.params = current_params;
            if (!current_filter.empty()) {
                returned.filter_options.push_back(new_filter);
            }
            current_params = {};
            current_filter = s;
            if (i == argc - 1) {
                FilterOptions new_filter;
                new_filter.filter_name = current_filter;
                new_filter.params = current_params;
                returned.filter_options.push_back(new_filter);
            }
        } else {
            current_params.push_back(s);
            if (i == argc - 1) {
                FilterOptions new_filter;
                new_filter.filter_name = current_filter;
                new_filter.params = current_params;
                returned.filter_options.push_back(new_filter);
            }
        }
        ++i;
    }

    return returned;
}