#pragma once

#include "Image.h"
#include "Parser.h"

uint32_t touint(std::string str) {
    uint32_t value = 0;

    for (int i = 0; i < str.size(); i++) {

        if (str[i] != '-') {
            value *= 10;
            value += static_cast<uint32_t>((str[i]) - '0');
        }
    }


    if (str.size() > 0 && str[0] == '-') {
        return -value;
    } else {
        return value;
    }
}

class Filter {
public:
    virtual void Apply(Image &image) const = 0;
};

class FilterCrop : public Filter {
    uint32_t h_;
    uint32_t w_;

public:
    void Apply(Image &x) const;

    FilterCrop(uint32_t h, uint32_t w) {
        h_ = h;
        w_ = w;
    }
};

class FilterNeg : public Filter {
public:
    void Apply(Image &x) const override;
};

class FilterGrayscale : public Filter {
public:
    void Apply(Image &x) const override;
};

class FilterSharp : public Filter {
public:
    void Apply(Image &x) const override;
};

class FilterEdge : public Filter {
    uint32_t threshold_;
public:
    void Apply(Image &x) const;

    FilterEdge(uint32_t threshold) {
        threshold_ = threshold;
    }
};
