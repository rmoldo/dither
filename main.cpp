#include <iostream>
#include <opencv2/opencv.hpp>
#include "dither.h"

using namespace cv;

int main (int argc, char** argv) {
  Dither d {argv[1]};
  d.change();
  d.saveImage("muiepsd.jpeg");

  return 0;
}
