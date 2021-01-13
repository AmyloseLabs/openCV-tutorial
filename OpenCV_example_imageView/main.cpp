#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat img; // Create Object
    cv::namedWindow("Image Window", cv::WINDOW_AUTOSIZE); // Create Object

    img = cv::imread("no_no_zapan.jpg", cv::IMREAD_COLOR); // Image Load
    if ( img.empty() ) { // Image State?
        // Print error message to monitor
        std::cout << "[Error] cannot open image file" << std::endl;
        return -1; // End
    }
    cv::imshow("Image Window", img); // Image Show
    cv::waitKey(0); //Wait
}
