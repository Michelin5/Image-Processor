#include "BMPReader.h"

void BMP::read(const char *fname) {
    std::ifstream inp{fname, std::ios_base::binary};

    if (!inp) {
        throw std::runtime_error("Unable to open the input image file.");
    }

    inp.read((char *) &file_header, sizeof(file_header));
    if (file_header.file_type != 0x4D42) {
        throw std::runtime_error("Error! Unrecognized file format.");
    }
    inp.read((char *) &bmp_info_header, sizeof(bmp_info_header));

    inp.seekg(file_header.offset_data, inp.beg);

    if (bmp_info_header.bit_count == 24) {
        bmp_info_header.size = sizeof(BMPInfoHeader);
        file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    }

    file_header.file_size = file_header.offset_data;

    if (bmp_info_header.height < 0) {
        throw std::runtime_error(
                "The program can treat only BMP images with the origin in the bottom left corner!");
    }

    data.resize(bmp_info_header.width * bmp_info_header.height * bmp_info_header.bit_count / 8);

    if (bmp_info_header.width % 4 == 0) {
        inp.read((char *) data.data(), data.size());
        file_header.file_size += static_cast<uint32_t>(data.size());
    } else {
        row_stride = bmp_info_header.width * bmp_info_header.bit_count / 8;
        uint32_t new_stride = make_stride_aligned(4);
        std::vector <uint8_t> padding_row(new_stride - row_stride);

        for (int y = 0; y < bmp_info_header.height; ++y) {
            inp.read((char *) (data.data() + row_stride * y), row_stride);
            inp.read((char *) padding_row.data(), padding_row.size());
        }
        file_header.file_size += static_cast<uint32_t>(data.size()) +
                                 bmp_info_header.height * static_cast<uint32_t>(padding_row.size());
    }

    uint32_t channels = bmp_info_header.bit_count / 8;


    for (size_t i = 0; i < bmp_info_header.height; ++i) {
        std::vector <RGB> temp;
        for (size_t j = 0; j < bmp_info_header.width * channels; j += 3) {
            RGB cur_rgb;
            cur_rgb.blue = data[channels * i * bmp_info_header.height + j + 0];
            cur_rgb.green = data[channels * i * bmp_info_header.height + j + 1];
            cur_rgb.red = data[channels * i * bmp_info_header.height + j + 2];
            temp.push_back(cur_rgb);
        }
        image_rgb.image.push_back(temp);
    }
    image_rgb.height = bmp_info_header.height;
    image_rgb.width = bmp_info_header.width;
}

void BMP::write(const char *fname, uint32_t h, uint32_t w) {
    bmp_info_header.height = h;
    bmp_info_header.width = w;
    std::ofstream of{fname, std::ios_base::binary};
    if (of) {
        if (bmp_info_header.bit_count == 32) {
            write_headers_and_data(of);
        } else if (bmp_info_header.bit_count == 24) {
            if (bmp_info_header.width % 4 == 0) {
                write_headers_and_data(of);
            } else {
                uint32_t new_stride = make_stride_aligned(4);
                std::vector <uint8_t> padding_row(new_stride - row_stride);

                write_headers(of);

                for (int y = 0; y < bmp_info_header.height; ++y) {
                    of.write((const char *) (data.data() + row_stride * y), row_stride);
                    of.write((const char *) padding_row.data(), padding_row.size());
                }
            }
        } else {
            throw std::runtime_error("The program can treat only 24 or 32 bits per pixel BMP files");
        }
    } else {
        throw std::runtime_error("Unable to open the output image file.");
    }
}

void BMP::write_headers(std::ofstream &of) {
    of.write((const char *) &file_header, sizeof(file_header));
    of.write((const char *) &bmp_info_header, sizeof(bmp_info_header));
}

void BMP::write_headers_and_data(std::ofstream &of) {
    write_headers(of);
    for (auto &x: image_rgb.image) {
        of.write(reinterpret_cast<char *>(x.data()), x.size() * 3);
    }
}

uint32_t BMP::make_stride_aligned(uint32_t align_stride) {
    uint32_t new_stride = row_stride;
    while (new_stride % align_stride != 0) {
        new_stride++;
    }
    return new_stride;
}