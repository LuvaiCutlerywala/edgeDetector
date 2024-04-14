#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

#include "../include/denoiser.hpp"

using namespace cv;

int main()
{
    Mat img = imread("../media/512-sample-image.tiff");
    Mat output(img.rows - 2, img.cols - 2, CV_8UC3);
    imshow("Sample Image", img);
    waitKey(0);
    denoiser::denoise(img, output);
    imshow("Denoised Image", output);
    waitKey(0);
}