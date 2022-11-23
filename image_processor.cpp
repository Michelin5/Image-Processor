#include "BMPReader.cpp"
#include "Parser.cpp"
#include "ImageProcessing.cpp"

int main(int argc, char **argv) {
    ParsedInput parsed_args = Parser::Parse(argc, argv);

    BMP bmp_object("examples/example.bmp");

    ImageProcessor image_processor(parsed_args.filter_options);

    image_processor.ApplyFilters(bmp_object.image_rgb);

    bmp_object.write("output.bmp", bmp_object.image_rgb.height, bmp_object.image_rgb.width);

    return 0;
}
