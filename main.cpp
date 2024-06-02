#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <sys/ioctl.h>
#include <unistd.h>

int main() {
  // const std::string pxlMap = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()"
  //                            "1{}[]?-_+~<>i!lI;:,\"^`'. ";
  // const std::string pxlMap = "@%#*+=-:. "; //" .:-=+*#%@";
  const std::string pxlMap = "$EFL1v!;,. "; //" .:-=+*#%@";
  std::cout << pxlMap.length() << std::endl;
  const int pxlMapLen = pxlMap.length();
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  std::cout << w.ws_col << " " << w.ws_row << std::endl;
  cv::Mat img = cv::imread("../img/dogs2.jpg");
  std::cout << img.dims << " " << img.cols << " " << img.rows << std::endl;
  cv::resize(img, img, cv::Size(w.ws_col, w.ws_row), cv::INTER_LINEAR);
  std::cout << img.at<uchar>(0, 0) << " " << img.cols << " " << img.rows
            << std::endl;
  // cv::imwrite("dogs2.jpg", img);
  cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
  std::cout << std::endl;
  int min = 255;
  int max = 0;

  for (int i = 0; i < w.ws_row; i++) {
    for (int j = 0; j < w.ws_col; j++) {
      if (int(float(img.at<uchar>(i, j))) < min)
        min = int(float(img.at<uchar>(i, j)));
      if (int(float(img.at<uchar>(i, j))) > max)
        max = int(float(img.at<uchar>(i, j)));
    }
  }
  int iscale = max - min;
  for (int i = 0; i < w.ws_row; i++) {
    for (int j = 0; j < w.ws_col; j++) {
      // std::cout << int(float(img.at<uchar>(i, j)) / 255 * 70) << " " <<
      // img.cols
      //           << " " << img.rows << std::endl;
      if (int(float(img.at<uchar>(i, j))) < min)
        min = int(float(img.at<uchar>(i, j)));
      if (int(float(img.at<uchar>(i, j))) > max)
        max = int(float(img.at<uchar>(i, j)));
      std::cout << pxlMap[pxlMapLen - int(float(img.at<uchar>(i, j) - min) /
                                          iscale * pxlMapLen)];
    }
    std::cout << std::endl;
  }
  // std::cout << min << " " << max << std::endl;
  cv::imshow("Hello", img); // Show our image inside the created window.

  cv::waitKey(0); // Wait for any keystroke in the window

  cv::destroyAllWindows(); // destroy the created window
  return 0;
}
