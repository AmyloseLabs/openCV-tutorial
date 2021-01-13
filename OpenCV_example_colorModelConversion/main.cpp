#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat imgMat_original, imgMat_model_gray, imgMat_model_rgb, imgMat_model_hsv; // Create Object
    cv::namedWindow("Original(BGR)", cv::WINDOW_AUTOSIZE); // Create Object
    cv::namedWindow("GrayScale Model Conversion", cv::WINDOW_AUTOSIZE); // Create Object
    cv::namedWindow("RGB Model Conversion", cv::WINDOW_AUTOSIZE); // Create Object
    cv::namedWindow("HSV Model Conversion", cv::WINDOW_AUTOSIZE); // Create Object

    imgMat_original = cv::imread("example.jpg", cv::IMREAD_COLOR); // Image Load
    if ( imgMat_original.empty() ) { // Image State?
        // Print error message to monitor
        std::cout << "[Error] cannot open image file" << std::endl;
        return -1; // End
    }

    // Converse color model
    cv::cvtColor(imgMat_original, imgMat_model_gray, CV_BGR2GRAY); // BGR->GRAY
    cv::cvtColor(imgMat_original, imgMat_model_rgb, CV_BGR2RGB); // BGR->RGB
    cv::cvtColor(imgMat_original, imgMat_model_hsv, CV_BGR2HSV); // BGR->HSV

    cv::imshow("Original(BGR)", imgMat_original); // Image Show
    cv::imshow("GrayScale Model Conversion", imgMat_model_gray); // Image Show
    cv::imshow("RGB Model Conversion", imgMat_model_rgb); // Image Show
    cv::imshow("HSV Model Conversion", imgMat_model_hsv); // Image Show

    cv::waitKey(0); //Wait
}
