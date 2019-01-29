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

void setPixel (cv::Mat& img, const cv::Vec3b& error, int x, int y, int ammount) {
  cv::Vec3b color = img.at<cv::Vec3b>(cv::Point(x, y));

  color[0] = color[0] + error[0] * ammount/16.0;
  color[1] = color[1] + error[1] * ammount/16.0;
  color[2] = color[2] + error[2] * ammount/16.0;

  img.at<cv::Vec3b>(cv::Point(x, y)) = color;
}

// For more information: https://en.wikipedia.org/wiki/Floyd%E2%80%93Steinberg_dithering

void Dither::dither() {
  for (int y = 0; y < image.rows - 1; ++y)
    for (int x = 1; x < image.cols - 1; ++x) {
      cv::Vec3b color = image.at<cv::Vec3b>(cv::Point(x, y));
      cv::Vec3b original = color;

      quantize(color,1);
      cv::Vec3b error = computeError(original, color);

      setPixel(image, error, x + 1, y    , 7);
      setPixel(image, error, x - 1, y + 1, 3);
      setPixel(image, error, x    , y + 1, 5);
      setPixel(image, error, x + 1, y + 1, 1);

      image.at<cv::Vec3b>(cv::Point(x, y)) = color;
    }
}
