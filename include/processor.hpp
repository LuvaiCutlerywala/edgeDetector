#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <opencv2/opencv.hpp>

using namespace cv;

class processor
{
    public:
        static Mat calculateIntensityGradient(Mat img);
};
#endif
