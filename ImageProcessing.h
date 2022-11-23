#pragma once

#include "Filters.cpp"

class ImageProcessor {
    std::vector<Filter *> filters;

public:
    ImageProcessor(std::vector<FilterOptions> &filter_options);

    void ApplyFilters(Image &image);
};
