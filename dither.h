#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class Dither {
 public:
  Dither (const std::string& sourceImage);

  void dither(); // does the dithering effect

  void saveImage(const std::string& outputImage);

 private:
  cv::Mat image;
};
