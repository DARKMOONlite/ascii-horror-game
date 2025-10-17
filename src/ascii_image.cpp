#include <ascii_image.hpp>

AsciiImage::AsciiImage(cv::Mat3b img_matrix, float horizontal_scale_factor){
    cv::Mat mat(img_matrix.size().height, img_matrix.size().width, CV_8UC4);
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            // Read from the input image
            cv::Vec3b pixel = img_matrix.at<cv::Vec3b>(i, j);
            
            // Calculate brightness using the input image pixel values
            int brightness = (0.2126 * pixel[2]) + (0.7152 * pixel[1]) + (0.0722 * pixel[0]); // BGR format
            char ascii_char = ColorUtils::get_ascii_char(brightness);
            
            // Store RGB values and ASCII character in our matrix
            cv::Vec4b& v = mat.at<cv::Vec4b>(i, j);
            v[0] = pixel[0]; // R
            v[1] = pixel[1]; // G  
            v[2] = pixel[2]; // B
            v[3] = static_cast<unsigned char>(ascii_char);
        }
    }
    cv::resize(mat,data.mat_,cv::Size(),horizontal_scale_factor,1); // this also stores the matrix in mat_
}
AsciiImage::AsciiImage(AsciiImageData data){
    this->data = data;
}

cv::Mat AsciiImage::get_matrix(){
    return(data.mat_);
}

void AsciiImage::print(){
    std::cout << *this;
}

void AsciiImage::set_greyscale(bool grey){
    data.greyscale = grey;
}

AsciiImage AsciiImage::crop(int x, int y, int size_x, int size_y){
    AsciiImage result = AsciiImage(data);
    result.data.mat_ = data.mat_(cv::Rect(x, y, size_x, size_y)).clone();
    return result;
}
AsciiImage AsciiImage::scale(float x,float y){
    AsciiImage result = AsciiImage(data);
    cv::resize(data.mat_,result.data.mat_,cv::Size(),x,y);
    return(result);
}