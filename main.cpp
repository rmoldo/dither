#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main (int argc, char** argv) {
  if (argc != 2) {
    printf("usage: DisplayImage.out <Image_Path>\n");
    return -1;
  }

  Mat image;
  image = imread(argv[1], 1);

  if (!image.data) {
    printf("No image data \n");
    return -1;
  }

  Mat finimage;
  if (image.type() != CV_GRAY2RGB)
    cvtColor(image, finimage, CV_RGB2GRAY);

  imwrite("outputphoto.png", finimage);

  return 0;
}
