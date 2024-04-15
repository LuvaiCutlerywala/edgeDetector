#ifndef IMG_UTILS_H
#define IMG_UTILS_H

#include <opencv2/opencv.hpp>

#include <cassert>

using namespace cv;

namespace img_utils
{
    Mat extract_sample_matrix(Mat img, int x, int y)
    {
        Mat sample(3, 3, CV_8UC3);
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                sample.at<Vec3b>(i, j) = img.at<Vec3b>(x - 1 + i, y - 1 + j);
            }
        }

        return sample;
    }

    template<typename type_s, typename type_k>
    type_s convolve_matrices(Mat sample, Mat kernel)
    {
        assert((sample.rows == kernel.rows) && (sample.cols == kernel.cols));
    
        type_s total = 0;
        for(int i = 0; i < sample.rows; ++i)
        {
            for(int j = 0; j < sample.cols; ++j)
            {
                total += sample.at<type_s>(i, j) * kernel.at<type_k>(i, j);
            }
        }

        return total;
    }
}


#endif