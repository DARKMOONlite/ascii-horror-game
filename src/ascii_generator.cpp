#include "ascii_generator.hpp"
#include "color_utils.hpp"

#include <iostream>
#include <cmath>

AsciiGenerator::AsciiGenerator(int contrast, int default_width) 
    : contrast_(contrast), default_width_(default_width) {
    initialize_density();
}

void AsciiGenerator::initialize_density() {
    std::string full_density = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|"
                              "()1{}[]?-_+~<>i!lI;:,\"^`'.            ";
    
    // Apply contrast adjustment
    int trim_amount = -11 + contrast_;
    if (trim_amount < 0) {
        density_ = full_density.substr(0, full_density.length() + trim_amount);
    } else {
        density_ = full_density;
    }
}

void AsciiGenerator::set_contrast(int contrast) {
    contrast_ = contrast;
    initialize_density();
}

void AsciiGenerator::set_default_width(int width) {
    default_width_ = width;
}

char AsciiGenerator::get_ascii_char(int brightness) const {
    int n = density_.length();
    int k = static_cast<int>(std::floor(brightness / 256.0 * n));
    k = std::min(k, n - 1);  // Ensure k doesn't exceed bounds
    return density_[n - 1 - k];
}

int AsciiGenerator::calculate_ascii_height(int width, int orig_width, int orig_height) const {
    double ratio = static_cast<double>(orig_height) / orig_width;
    // ASCII character glyphs are taller than they are wide
    return static_cast<int>(width * ratio * 0.5);
}

void AsciiGenerator::generate_ascii_art(const std::string& image_path, int width) {
    if (width == -1) {
        width = default_width_;
    }
    
    // Load image
    int x,y,n;
    unsigned char *data = stbi_load(image_path.c_str(),&x,&y,&n,0);

    if (img.empty()) {
        std::cerr << "Error: Could not load image " << image_path << std::endl;
        return;
    }
    
    // Calculate new dimensions
    int orig_width = img.cols;
    int orig_height = img.rows;
    int height = calculate_ascii_height(width, orig_width, orig_height);
    
    // Resize image
    cv::Mat resized_img;
    cv::resize(img, resized_img, cv::Size(width, height), 0, 0, cv::INTER_LANCZOS4);
    
    // Convert to different color spaces
    cv::Mat rgb_img, gray_img;
    cv::cvtColor(resized_img, rgb_img, cv::COLOR_BGR2RGB);
    cv::cvtColor(resized_img, gray_img, cv::COLOR_BGR2GRAY);
    
    // Generate ASCII art
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // Get brightness from grayscale image
            int brightness = gray_img.at<uchar>(i, j);
            
            // Get RGB color from original image
            cv::Vec3b rgb_pixel = rgb_img.at<cv::Vec3b>(i, j);
            int r = rgb_pixel[0];
            int g = rgb_pixel[1];
            int b = rgb_pixel[2];
            
            // Generate colored ASCII character
            char ascii_char = get_ascii_char(brightness);
            std::string color_code = ColorUtils::rgb_to_ansi(r, g, b);
            std::string reset_code = ColorUtils::reset_color();
            
            std::cout << color_code << ascii_char << reset_code;
        }
        std::cout << std::endl;
    }
}
