#include "ascii_generator.hpp"
#include "color_utils.hpp"
#include "ascii_image.hpp"
#include <iostream>
#include <cmath>

AsciiGenerator::AsciiGenerator(){
    
}
    

void AsciiGenerator::set_desired_dimensions(int width, int height) {
    default_width_ = width;
    default_height_ = height;
}


AsciiImage AsciiGenerator::generate_ascii_from_file(const std::string& image_path, int width, int height) {
    // Load image using OpenCV
    cv::Mat img = cv::imread(image_path);
    if (img.empty()) {
        std::cerr << "Error: Could not load image " << image_path << std::endl;
    }
    int w = img.size().width;
    int h = img.size().height;

    // Determine target dimensions: prefer explicit params, then defaults, then original image size.
    if (width != -1) {
        w = width;
    } 
    else {
        if (default_width_ != -1) {
            w = default_width_;
        }
    }   
    if (height != -1) {
        h = height;
    } 
    else {
        if (default_height_ != -1) {
            h = default_height_;
        }
    }

    // Resize image
    cv::Mat resized_img;
    cv::resize(img, resized_img, cv::Size(w, h), 0, 0, cv::INTER_LANCZOS4);
    // Convert to RGB color space
    cv::Mat3b rgb_img;
    cv::cvtColor(resized_img, rgb_img, cv::COLOR_BGR2RGB);
    
    AsciiImage ascii_mat = AsciiImage(rgb_img);
    // ascii_mat.print();
    return(ascii_mat);
}
