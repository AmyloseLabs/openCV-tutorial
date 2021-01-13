#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

enum hsvRange {
    minHue = 45,
    maxHue = 75,
    minSat = 0,
    maxSat = 255,
    minVal = 0,
    maxVal = 255
};

const std::string strErrMsg_imgFileLoadFailed = "[Error] Image file loading failed!";
const std::string strMsg_noDetection = "Cannot find circle from image!";
const std::string strWindowTitle_source = "Source Image";
const std::string strWindowTitle_binaryImage = "Binary Image";
const std::string strWindowTitle_edgeImage = "Edge Detect Result";

int main() {
    std::vector<cv::Vec3f> circlesData;
    cv::Mat imgMat_source;
    cv::Mat imgMat_colorModelConversion;
    cv::Mat imgMat_binaryImage;
    cv::Mat imgMat_edgeImage;
    cv::namedWindow(strWindowTitle_source, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(strWindowTitle_binaryImage, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(strWindowTitle_edgeImage, cv::WINDOW_AUTOSIZE);

    imgMat_source = cv::imread("sample.jpg", cv::IMREAD_COLOR);
    if ( imgMat_source.empty() ) {
        std::cout << strErrMsg_imgFileLoadFailed << std::endl;
        return -1;
    } else {
        // init sub matrix from loaded image data size
        imgMat_colorModelConversion.create(cv::Size(imgMat_source.cols, imgMat_source.rows), CV_8UC3);
        imgMat_binaryImage.create(cv::Size(imgMat_source.cols, imgMat_source.rows), CV_8UC1);
        imgMat_edgeImage.create(cv::Size(imgMat_source.cols, imgMat_source.rows), CV_8UC1);

        // color model conversion
        cv::cvtColor(imgMat_source, imgMat_colorModelConversion, CV_BGR2HSV);

        // simplify to binary image from hsvType image
        cv::inRange(imgMat_colorModelConversion,
                    cv::Scalar(hsvRange::minHue, hsvRange::minSat, hsvRange::minVal),
                    cv::Scalar(hsvRange::maxHue, hsvRange::maxSat, hsvRange::maxVal),
                    imgMat_binaryImage);

        // filter
        cv::erode(imgMat_binaryImage,
                  imgMat_binaryImage,
                  cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(1,1)));
		cv::dilate(imgMat_binaryImage,
                   imgMat_binaryImage,
                   cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(1,1)));
		cv::dilate(imgMat_binaryImage,
                   imgMat_binaryImage,
                   cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(1,1)));
		cv::erode(imgMat_binaryImage,
                  imgMat_binaryImage,
                  cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(1,1)));
		cv::GaussianBlur(imgMat_binaryImage, imgMat_binaryImage, cv::Size(5, 5), 2, 2);
		cv::threshold(imgMat_binaryImage, imgMat_binaryImage, 127, 255, CV_THRESH_BINARY);

		// Edge Detection
		cv::Canny(imgMat_binaryImage, imgMat_edgeImage, 400, 800);

		// fit circle from edge detected image
		cv::HoughCircles(imgMat_edgeImage,
                         circlesData,
                         CV_HOUGH_GRADIENT,
                         2,
                         imgMat_edgeImage.rows/4,
                         100,
                         80,
                         75,
                         0
                         );
        if ( circlesData.size() != 0 ) {
            for ( int iter = 0; iter < circlesData.size(); iter++ ) {
                cv::circle(imgMat_source,
                           cv::Point((int)circlesData[iter][0], (int)circlesData[iter][1]),
                           (int)circlesData[iter][2],
                           cv::Scalar(0, 0, 255),
                           2);
            }
        } else {
            cv::putText(imgMat_source,
                        strMsg_noDetection,
                        cv::Point(15, 15),
                        1,
                        1.5,
                        cv::Scalar(0, 0, 255),
                        1);
        }
        cv::imshow(strWindowTitle_source, imgMat_source);
        cv::imshow(strWindowTitle_binaryImage, imgMat_binaryImage);
        cv::imshow(strWindowTitle_edgeImage, imgMat_edgeImage);
        cv::waitKey();
    }
    return 0;
}
