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
    std::vector<std::vector<cv::Point>> contours;
    cv::Mat ellipseLine;
    cv::RotatedRect ellipse;
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
		cv::medianBlur(imgMat_binaryImage, imgMat_binaryImage, 5);
		cv::threshold(imgMat_binaryImage, imgMat_binaryImage, 127, 255, CV_THRESH_BINARY);

		// Edge Detection
		cv::Canny(imgMat_binaryImage, imgMat_edgeImage, 800, 900);

		// Find Contours from Edge Image
		contours.clear();
		cv::findContours(imgMat_edgeImage, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

		// Fit Ellipse from Contours
		if ( contours.size() > 0 ) {
            for ( int iter = 0; iter < contours.size(); iter++ ) {
                if ( contours.at(iter).size() < 6 ) {
                    continue;
                }
                cv::Mat(contours.at(iter)).convertTo(ellipseLine, CV_32F);
                ellipse = cv::fitEllipse(ellipseLine);
                cv::ellipse(imgMat_source, ellipse, cv::Scalar(0, 0, 255), 2);
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
