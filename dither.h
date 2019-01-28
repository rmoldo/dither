#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class Dither {
 public:
  Dither (const std::string& sourceImage);

  void dither(); // does the dithering

  void saveImage(const std::string& outputImage);
  void change ();

 private:
  cv::Mat image;
};
