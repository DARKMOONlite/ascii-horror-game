#ifndef ASCII_IMAGE_HPP
#define ASCII_IMAGE_HPP
#include <opencv2/opencv.hpp>
#include <color_utils.hpp>
#include <iostream>


struct AsciiImageData{
    AsciiImageData(){

    }
    AsciiImageData(cv::Mat4b mat, bool grey){
        mat_ = mat;
        greyscale = grey;
    }
cv::Mat4b mat_;
bool greyscale = false;
};

class AsciiImage{

public:

AsciiImage(cv::Mat3b img_matrix, float horizontal_scale_factor=3);
AsciiImage(AsciiImageData data);
cv::Mat get_matrix();
void print();
void set_greyscale(bool grey);

AsciiImage crop(int x, int y, int size_x, int size_y);
AsciiImage scale(float x_scale, float y_scale);
// AsciiImage Filter(int r, int g, int b)




friend std::ostream& operator<< (std::ostream& os, const AsciiImage& mat){
    for (int i = 0; i < mat.data.mat_.rows; ++i) {
        for (int j = 0; j < mat.data.mat_.cols; ++j) {
            const cv::Vec4b& v = mat.data.mat_.at<cv::Vec4b>(i, j);
            std::string color_code, reset_code;
            if(!mat.data.greyscale){
                color_code = ColorUtils::rgb_to_ansi(v[0], v[1], v[2]);
                reset_code = ColorUtils::reset_color();
            }
            os << color_code << static_cast<char>(v[3]) << reset_code;
            
        }
        os << std::endl;
    }
    return(os);
}
private:
AsciiImageData data;
};

#endif