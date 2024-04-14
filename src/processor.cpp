#include "../include/processor.hpp"

Mat processor::calculateIntensityGradient(Mat img)
{
    Mat output(img.rows, img.cols, CV_64FC2);
    const Mat G_x(3, 3, CV_16SC1, {1, 0, -1, 2, 0, -2, 1, 0, -1});
    const Mat G_y();
}