#ifndef ASCII_VIDEO_H
#define ASCII_VIDEO_H

#include <vector>
#include <memory>
#include "ASCIIImage.h"

namespace ASCIIDisplay {

// Represents an ASCII video as a sequence of frames
class ASCIIVideo {
public:
    // Constructor
    ASCIIVideo();
    
    // Add a frame to the video
    void addFrame(std::shared_ptr<ASCIIImage> frame);
    
    // Load frames from RGB data sequence
    // Each frame is width * height * 3 bytes (RGB)
    void loadFromRGBSequence(const std::vector<std::vector<unsigned char>>& frames, 
                             int width, int height);
    
    // Load frames from grayscale data sequence
    void loadFromGrayscaleSequence(const std::vector<std::vector<unsigned char>>& frames,
                                   int width, int height);
    
    // Get frame by index
    std::shared_ptr<ASCIIImage> getFrame(size_t index);
    
    // Get current frame
    std::shared_ptr<ASCIIImage> getCurrentFrame();
    
    // Advance to next frame (wraps around)
    void nextFrame();
    
    // Set current frame index
    void setFrame(size_t index);
    
    // Get frame count
    size_t getFrameCount() const { return frames_.size(); }
    
    // Get current frame index
    size_t getCurrentFrameIndex() const { return currentFrame_; }
    
    // Set frame rate (for timing reference)
    void setFrameRate(double fps) { frameRate_ = fps; }
    double getFrameRate() const { return frameRate_; }
    
    // Clear all frames
    void clear();
    
    // Render current frame to panel
    void renderToPanel(class Panel& panel, int row = 0, int col = 0);

private:
    std::vector<std::shared_ptr<ASCIIImage>> frames_;
    size_t currentFrame_;
    double frameRate_;  // Frames per second (for reference)
};

} // namespace ASCIIDisplay

#endif // ASCII_VIDEO_H
