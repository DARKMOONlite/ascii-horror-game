#ifndef ASCII_IMAGE_HPP
#define ASCII_IMAGE_HPP
#include <opencv2/opencv.hpp>
#include <color_utils.hpp>
#include <iostream>

class AsciiImage{

public:

AsciiImage(cv::Mat3b img_matrix, float horizontal_scale_factor=3);
AsciiImage(cv::Mat4b ascii_img);
cv::Mat get_matrix();
void print();

AsciiImage crop(int x, int y, int size_x, int size_y);
AsciiImage scale(float x_scale, float y_scale);
// AsciiImage Filter(int r, int g, int b)




friend std::ostream& operator<< (std::ostream& os, const AsciiImage& mat){
    for (int i = 0; i < mat.mat_.rows; ++i) {
        for (int j = 0; j < mat.mat_.cols; ++j) {
            const cv::Vec4b& v = mat.mat_.at<cv::Vec4b>(i, j);
            std::string color_code = ColorUtils::rgb_to_ansi(v[0], v[1], v[2]);
            std::string reset_code = ColorUtils::reset_color();
            os << color_code << static_cast<char>(v[3]) << reset_code;
        }
        os << std::endl;
    }
    return(os);
}
private:
cv::Mat4b mat_;

};

#endif