#include "ASCIIVideo.h"

namespace ASCIIDisplay {

ASCIIVideo::ASCIIVideo() : currentFrame_(0), frameRate_(30.0) {
}

void ASCIIVideo::addFrame(std::shared_ptr<ASCIIImage> frame) {
    frames_.push_back(frame);
}

void ASCIIVideo::loadFromRGBSequence(const std::vector<std::vector<unsigned char>>& frames,
                                     int width, int height) {
    clear();
    
    for (const auto& frameData : frames) {
        auto image = std::make_shared<ASCIIImage>();
        image->loadFromRGB(frameData, width, height);
        frames_.push_back(image);
    }
    
    currentFrame_ = 0;
}

void ASCIIVideo::loadFromGrayscaleSequence(const std::vector<std::vector<unsigned char>>& frames,
                                           int width, int height) {
    clear();
    
    for (const auto& frameData : frames) {
        auto image = std::make_shared<ASCIIImage>();
        image->loadFromGrayscale(frameData, width, height);
        frames_.push_back(image);
    }
    
    currentFrame_ = 0;
}

std::shared_ptr<ASCIIImage> ASCIIVideo::getFrame(size_t index) {
    if (index < frames_.size()) {
        return frames_[index];
    }
    return nullptr;
}

std::shared_ptr<ASCIIImage> ASCIIVideo::getCurrentFrame() {
    if (currentFrame_ < frames_.size()) {
        return frames_[currentFrame_];
    }
    return nullptr;
}

void ASCIIVideo::nextFrame() {
    if (!frames_.empty()) {
        currentFrame_ = (currentFrame_ + 1) % frames_.size();
    }
}

void ASCIIVideo::setFrame(size_t index) {
    if (index < frames_.size()) {
        currentFrame_ = index;
    }
}

void ASCIIVideo::clear() {
    frames_.clear();
    currentFrame_ = 0;
}

void ASCIIVideo::renderToPanel(Panel& panel, int row, int col) {
    auto frame = getCurrentFrame();
    if (frame) {
        frame->renderToPanel(panel, row, col);
    }
}

} // namespace ASCIIDisplay
