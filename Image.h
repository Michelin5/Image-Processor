#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#pragma pack(push, 1)
struct RGB {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

struct Image {
    size_t height;
    size_t width;
    std::vector<std::vector<RGB>> image;
};

#pragma pack(pop)