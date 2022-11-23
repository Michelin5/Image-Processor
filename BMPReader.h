#pragma once

#include "Image.h"
#include "Parser.h"


#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t file_type{0x4042};
    uint32_t file_size{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offset_data{0};
};

struct BMPInfoHeader {
    uint32_t size{0};
    int32_t width{0};
    int32_t height{0};
    uint16_t planes{1};
    uint16_t bit_count{0};
    uint32_t compression{0};
    uint32_t size_image{0};
    int32_t x_pixels_per_meter{0};
    int32_t y_pixels_per_meter{0};
    uint32_t colors_used{
            0};
    uint32_t colors_important{0};
};

#pragma pack(pop)

struct BMP {
    BMPFileHeader file_header;
    BMPInfoHeader bmp_info_header;
    std::vector<uint8_t> data;
    Image image_rgb;

    BMP(const char *fname) {
        read(fname);
    }

    void read(const char *fname);

    void write(const char *fname, uint32_t h, uint32_t w);

private:
    uint32_t row_stride{0};

    void write_headers(std::ofstream &of);

    void write_headers_and_data(std::ofstream &of);

    uint32_t make_stride_aligned(uint32_t align_stride);

};
