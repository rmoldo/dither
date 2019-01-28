#include "dither.h"
#include <assert.h>

Dither::Dither (const std::string& sourceImage) {
  image = cv::imread(sourceImage, 1);

  assert(image.data);
}

void Dither::saveImage (const std::string &outputImage) {
  cv::imwrite(outputImage, image);
}

void Dither::change () {
  for (int y = 0; y < image.rows; ++y)
    for (int x = 0; x < image.cols; ++x) {
      cv::Vec3b color = image.at<cv::Vec3b>(cv::Point(x,y));
      color[0] = 0;
      color[1] = 255;
      color[2] = 0;
      image.at<cv::Vec3b>(cv::Point(x,y)) = color;
    }
}
