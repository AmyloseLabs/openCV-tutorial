#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat frame; // Create Object
    cv::namedWindow("Camera View", cv::WINDOW_AUTOSIZE); // Create Object (GUI Window)
    /*
        Camera Ch 0 <- primary camera in computer
            (ex : laptop: primary camera is built-in cam)
    */
    cv::VideoCapture camera(0); // Create Object (camera)

    if ( !camera.isOpened() ) { // camera state?
        std::cout << "[Error] cannot open Camera device" << std::endl; // Print error message to monitor
        return -1; // End
    }

    for (;;) {
        camera.read(frame); // capture image from camera
        if ( frame.empty() ) { // capture state?
            std::cout << "[Error] Cannot capture image from camera" << std::endl; // Print error message to monitor
            break;
        }
        cv::imshow("Camera View", frame); // image show
        if ( cv::waitKey(25) >= 0 ) break; // wait escape loop key
    }
    return 0; // End
}
