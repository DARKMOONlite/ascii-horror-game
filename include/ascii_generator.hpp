#ifndef ASCII_GENERATOR_HPP
#define ASCII_GENERATOR_HPP

#include <string>
#include <ascii_image.hpp>
#include <opencv2/opencv.hpp>

class AsciiGenerator {
public:
    AsciiGenerator();
    
    AsciiImage generate_ascii_from_file(const std::string& image_path, int width = -1, int height = -1);
    void set_desired_dimensions(int width, int height);

private:
    int contrast_;
    int default_width_ = -1;
    int default_height_ = -1;
    std::string density_;

    
    void initialize_density();
    char get_ascii_char(int brightness) const;


};


#endif