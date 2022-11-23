#include "ImageProcessing.h"

ImageProcessor::ImageProcessor(std::vector<FilterOptions> &filter_options) {
    for (auto &x: filter_options) {
        std::cout << x.filter_name << std::endl;
        if (x.filter_name == "-neg") {
            filters.push_back(new FilterNeg());
        } else if (x.filter_name == "-gs") {
            filters.push_back(new FilterGrayscale());
        } else if (x.filter_name == "-sharp") {
            filters.push_back(new FilterSharp());
        } else if (x.filter_name == "-crop") {
            filters.push_back(new FilterCrop(touint(x.params[0]), touint(x.params[1])));
        } else if (x.filter_name == "-edge") {
            filters.push_back(new FilterEdge(touint(x.params[0])));
        }
    }
}

void ImageProcessor::ApplyFilters(Image &image) {
    for (const auto &filter: filters) {
        filter->Apply(image);
    }
}