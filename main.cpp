#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <sys/ioctl.h>
#include <unistd.h>

cv::Mat resizeImg(cv::Mat img) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  // std::cout << img.dims << " " << img.cols << " " << img.rows << std::endl;
  cv::resize(img, img, cv::Size(w.ws_col, w.ws_row), cv::INTER_LINEAR);
  // std::cout << img.at<uchar>(0, 0) << " " << img.cols << " " << img.rows
  //           << std::endl;
  // cv::imwrite("dogs2.jpg", img);
  cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
  return img;
}

void printImg(cv::Mat img) {

  // const std::string pxlMap = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()"
  //                            "1{}[]?-_+~<>i!lI;:,\"^`'. ";
  // const std::string pxlMap = "@%#*+=-:. "; //" .:-=+*#%@";
  const std::string pxlMap = "@$W8EF1vt/!;,. "; //" .:-=+*#%@";
  // std::cout << pxlMap.length() << std::endl;
  const int pxlMapLen = pxlMap.length();
  int min = 0; // 255;
  // std::cout << "\033[2J";
  std::cout << "\033[1;1H";
  int max = 255; // 0;
  int iscale = max - min;
  for (int i = 0; i < img.rows - 1; i++) {
    for (int j = 0; j < img.cols; j++) {
      if (int(float(img.at<uchar>(i, j))) < min)
        min = int(float(img.at<uchar>(i, j)));
      if (int(float(img.at<uchar>(i, j))) > max)
        max = int(float(img.at<uchar>(i, j)));
      std::cout << pxlMap[pxlMapLen - int(float(img.at<uchar>(i, j) - min) /
                                          iscale * pxlMapLen)];
    }
    std::cout << std::endl;
  }
}

void image() {
  cv::Mat origImg = cv::imread("../img/dogs2.jpg");
  std::cout << std::endl;
  cv::Mat img = resizeImg(origImg);
  printImg(img);

  cv::cvtColor(origImg, origImg, cv::COLOR_BGR2GRAY);
  cv::imshow("Original", origImg);
  cv::waitKey(0); // Wait for any keystroke in the window
}

void webcam() {
  cv::VideoCapture cap(0);

  // Check if camera opened successfully
  if (!cap.isOpened()) {
    std::cout << "Error opening video stream or file" << std::endl;
    exit(-1);
  }

  while (1) {

    cv::Mat frame;
    cap >> frame;
    if (frame.empty())
      break;

    cv::Mat img = resizeImg(frame);
    printImg(img);

    imshow("Frame", frame);

    // Press  ESC on keyboard to exit
    char c = (char)cv::waitKey(25);
    if (c == 27)
      break;
  }

  // Release the video capture object
  cap.release();
}

int main() {
  // std::cout << "Using OpenCV version " << CV_VERSION << "\n" << std::endl;
  // std::cout << cv::getBuildInformation();

  // image();
  webcam();

  cv::destroyAllWindows();
  return 0;
}
