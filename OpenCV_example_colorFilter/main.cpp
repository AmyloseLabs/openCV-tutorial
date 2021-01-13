#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat imgMat_original, imgMat_model_gray, imgMat_mask_lower, imgMat_mask_upper;
    cv::Mat imgMat_maskResult;
    cv::namedWindow("Original(BGR)", cv::WINDOW_AUTOSIZE); // Create Object
    cv::namedWindow("GrayScale Model", cv::WINDOW_AUTOSIZE); // Create Object
    cv::namedWindow("Mask Lower", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Mask Upper", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Mask Result", cv::WINDOW_AUTOSIZE);

    imgMat_original = cv::imread("example.jpg", cv::IMREAD_COLOR); // Image Load
    if ( imgMat_original.empty() ) { // Image State?
        // Print error message to monitor
        std::cout << "[Error] cannot open image file" << std::endl;
        return -1; // End
    }

    // Converse color model
    cv::cvtColor(imgMat_original, imgMat_model_gray, CV_BGR2GRAY); // BGR->GRAY
    // Filter color range in grayscale
    cv::inRange(imgMat_model_gray, cv::Scalar(0), cv::Scalar(32), imgMat_mask_lower);
    cv::inRange(imgMat_model_gray, cv::Scalar(223), cv::Scalar(255), imgMat_mask_upper);

    imgMat_maskResult = imgMat_mask_lower | imgMat_mask_upper;

    cv::imshow("Original(BGR)", imgMat_original); // Image Show
    cv::imshow("GrayScale Model", imgMat_model_gray); // Image Show
    cv::imshow("Mask Lower", imgMat_mask_lower);
    cv::imshow("Mask Upper", imgMat_mask_upper);
    cv::imshow("Mask Result", imgMat_maskResult);

    cv::waitKey(0); //Wait
}
