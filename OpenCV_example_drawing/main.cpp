#include <iostream>
#include <opencv2/opencv.hpp>

enum imgMatrixSize {
    width = 640,
    height = 480
};

int main() {
    cv::Mat imgMat_canvas;
    bool saveResult = false;
    cv::namedWindow("Canvas", cv::WINDOW_AUTOSIZE);

    imgMat_canvas.create(imgMatrixSize::height, imgMatrixSize::width, CV_8UC3);
    imgMat_canvas = cv::Scalar(255, 255, 255);

    if ( imgMat_canvas.empty() ) {
        std::cout << "[Error] Image Matrix Init Failed..!" << std::endl;
    }

    // canvas range st

    cv::line(
             imgMat_canvas,         // Image Array
             cv::Point(25, 25),     // Start Point
             cv::Point(320, 400),   // End Point
             cv::Scalar(255, 0, 0),
             3
             );

    // canvas range en

    cv::imshow("Canvas", imgMat_canvas);
    saveResult = cv::imwrite("canvas.jpg", imgMat_canvas);
    if ( saveResult ) {
        std::cout << "Canvas image saved successfully." << std::endl;
    } else  {
        std::cout << "[Error]image writing failed.." << std::endl;
    }
    cv::waitKey();
    return 0;
}
