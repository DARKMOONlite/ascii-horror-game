#include<memory>


class Image {
    private:
    std::unique_ptr<uint8_t> data;
    int width, height, num_channels;
};