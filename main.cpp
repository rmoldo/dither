#include <iostream>
#include <opencv2/opencv.hpp>
#include "dither.h"

using namespace cv;

int main (int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "You must provide the name of the input image\n";
    return 1;
  }

  Dither d {argv[1]};
  d.dither();
  d.saveImage("output.jpeg");

  return 0;
}
