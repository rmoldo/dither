#include "dither.h"
#include <assert.h>
#include <cmath>

Dither::Dither(const std::string& sourceImage)
{
        image = cv::imread(sourceImage, 1);

        assert(image.data);
}

void Dither::saveImage(const std::string &outputImage)
{
        cv::imwrite(outputImage, image);
}

/* Quantize the pixel RGB values by a factor */
void quantize(cv::Vec3b& color, int factor)
{
        color[0] = std::round(factor * (color[0] / 255.0f)) * (255 / factor);
        color[1] = std::round(factor * (color[1] / 255.0f)) * (255 / factor);
        color[2] = std::round(factor * (color[2] / 255.0f)) * (255 / factor);
}

cv::Vec3b computeError(const cv::Vec3b &originalColor, const cv::Vec3b &newColor)
{
        return originalColor - newColor;
}

void setPixel(cv::Mat &img, const cv::Vec3b &error, int x, int y, int ammount) {
        cv::Vec3b color = img.at<cv::Vec3b>(cv::Point(x, y));

        color[0] = color[0] + error[0] * ammount / 16.0f;
        color[1] = color[1] + error[1] * ammount / 16.0f;
        color[2] = color[2] + error[2] * ammount / 16.0f;

        img.at<cv::Vec3b>(cv::Point(x, y)) = color;
}

/*
  Dither the image using Floyd-Steinberg algorithm
  For more information: https://en.wikipedia.org/wiki/Floyd%E2%80%93Steinberg_dithering
*/
void Dither::dither()
{
        for (int y = 0; y < image.rows - 1; ++y)
                for (int x = 1; x < image.cols - 1; ++x) {
                        cv::Vec3b newcolor = image.at<cv::Vec3b>(cv::Point(x, y));
                        cv::Vec3b original = newcolor;

                        quantize(newcolor, 1);
                        cv::Vec3b error = computeError(original, newcolor);

                        setPixel(image, error, x + 1, y    , 7);
                        setPixel(image, error, x - 1, y + 1, 3);
                        setPixel(image, error, x    , y + 1, 5);
                        setPixel(image, error, x + 1, y + 1, 1);

                        image.at<cv::Vec3b>(cv::Point(x, y)) = newcolor;
                }
}
