#include "Filters.h"

void FilterCrop::Apply(Image &x) const {
    if (h_ > x.height || w_ > x.width) {
        return;
    }
    x.height = h_;
    x.width = w_;
    x.image.resize(h_);
    for (int i = 0; i < h_; ++i) {
        x.image[i].resize(w_);
    }
}

void FilterNeg::Apply(Image &x) const {
    for (int i = 0; i < x.height; ++i) {
        for (int j = 0; j < x.width; ++j) {
            x.image[i][j].blue = 255 - x.image[i][j].blue;
            x.image[i][j].green = 255 - x.image[i][j].green;
            x.image[i][j].red = 255 - x.image[i][j].red;
        }
    }
}

void FilterGrayscale::Apply(Image &x) const {
    for (int i = 0; i < x.height; ++i) {
        for (int j = 0; j < x.width; ++j) {
            const auto b = x.image[i][j].blue;
            const auto g = x.image[i][j].green;
            const auto r = x.image[i][j].red;
            const auto formula = 0.114 * b + 0.587 * g + 0.299 * r;
            x.image[i][j].blue = formula;
            x.image[i][j].green = formula;
            x.image[i][j].red = formula;
        }
    }
}

void FilterSharp::Apply(Image &x) const {
    Image current_image = x;
    for (int i = 1; i < x.height - 1; ++i) {
        for (int j = 1; j < x.width - 1; ++j) {
            x.image[i][j].blue = std::min(255, std::max(0, -1 * current_image.image[i][j -
                                                                                       1].blue -
                                                           1 * current_image.image[i -
                                                                                   1][j].blue +
                                                           5 *
                                                           current_image.image[i][j].blue -
                                                           1 * current_image.image[i +
                                                                                   1][j].blue -
                                                           1 * current_image.image[i][j +
                                                                                      1].blue));
            x.image[i][j].green = std::min(255, std::max(0, -1 * current_image.image[i][j -
                                                                                        1].green -
                                                            1 * current_image.image[i -
                                                                                    1][j].green +
                                                            5 *
                                                            current_image.image[i][j].green -
                                                            1 * current_image.image[i +
                                                                                    1][j].green -
                                                            1 * current_image.image[i][j +
                                                                                       1].green));
            x.image[i][j].red = std::min(255, std::max(0, -1 * current_image.image[i][j -
                                                                                      1].red -
                                                          1 * current_image.image[i -
                                                                                  1][j].red +
                                                          5 *
                                                          current_image.image[i][j].red -
                                                          1 * current_image.image[i +
                                                                                  1][j].red -
                                                          1 * current_image.image[i][j +
                                                                                     1].red));
        }
    }
}

void FilterEdge::Apply(Image &x) const {
    Image current_image = x;
    for (int i = 1; i < x.height - 1; ++i) {
        for (int j = 1; j < x.width - 1; ++j) {
            x.image[i][j].blue = std::min(255, std::max(0, -1 * current_image.image[i][j -
                                                                                       1].blue -
                                                           1 * current_image.image[i -
                                                                                   1][j].blue +
                                                           4 *
                                                           current_image.image[i][j].blue -
                                                           1 * current_image.image[i +
                                                                                   1][j].blue -
                                                           1 * current_image.image[i][j +
                                                                                      1].blue));
            x.image[i][j].green = std::min(255, std::max(0, -1 * current_image.image[i][j -
                                                                                        1].green -
                                                            1 * current_image.image[i -
                                                                                    1][j].green +
                                                            4 *
                                                            current_image.image[i][j].green -
                                                            1 * current_image.image[i +
                                                                                    1][j].green -
                                                            1 * current_image.image[i][j +
                                                                                       1].green));
            x.image[i][j].red = std::min(255, std::max(0, -1 * current_image.image[i][j -
                                                                                      1].red -
                                                          1 * current_image.image[i -
                                                                                  1][j].red +
                                                          4 *
                                                          current_image.image[i][j].red -
                                                          1 * current_image.image[i +
                                                                                  1][j].red -
                                                          1 * current_image.image[i][j +
                                                                                     1].red));
        }
    }
    for (int i = 1; i < x.height - 1; ++i) {
        for (int j = 1; j < x.width - 1; ++j) {
            if (x.image[i][j].blue > threshold_) {
                x.image[i][j].blue = 255;
                x.image[i][j].green = 255;
                x.image[i][j].red = 255;
            } else {
                x.image[i][j].blue = 0;
                x.image[i][j].green = 0;
                x.image[i][j].red = 0;
            }
        }
    }
}