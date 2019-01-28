#include "dither.h"
#include <assert.h>
#include <cmath>

Dither::Dither (const std::string& sourceImage) {
  image = cv::imread(sourceImage, 1);

  assert(image.data);
}

void Dither::saveImage (const std::string &outputImage) {
  cv::imwrite(outputImage, image);
}

// quantize the pixel RGB values by a factor
void quantize (cv::Vec3b& color, int factor) {
  color[0] = std::round(factor * color[0] / 255.0) * (255 / factor);
  color[1] = std::round(factor * color[1] / 255.0) * (255 / factor);
  color[2] = std::round(factor * color[2] / 255.0) * (255 / factor);
}

cv::Vec3b computeError (const cv::Vec3b& _originalColor, const cv::Vec3b& _newColor) {
  cv::Vec3b error;

  error[0] = _originalColor[0] - _newColor[0];
  error[1] = _originalColor[1] - _newColor[1];
  error[2] = _originalColor[2] - _newColor[2];

  return error;
}

void Dither::dither() {
  for (int y = 0; y < image.rows; ++y)
    for (int x = 0; x < image.cols; ++x) {
      cv::Vec3b color = image.at<cv::Vec3b>(cv::Point(x,y));

      quantize(color,6);

      image.at<cv::Vec3b>(cv::Point(x,y)) = color;
    }
}
