#ifndef DITHER_H
#define DITHER_H

#include <opencv2/opencv.hpp>
#include <string>

class Dither {
public:
        Dither(const std::string &sourceImage);

        void dither();
        void saveImage(const std::string &outputImage);

private:
        cv::Mat image;
};

#endif
