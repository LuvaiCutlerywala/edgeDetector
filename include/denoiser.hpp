#ifndef DENOISER_H
#define DENOISER_H

#include <opencv2/opencv.hpp>
#include <cstdint>

using namespace cv;

#define PI 3.141592654

class denoiser
{
    public:
        static void denoise(Mat img, Mat output);
    private:
        static Mat extract_sample_matrix(Mat img, int x, int y);
        static Vec3b convolve_matrices(Mat sample, Mat filter);
        static Vec3b normalise(Vec3b pixel, double normalisation_factor);
        static Mat add_buffer_zone(Mat img);
};

#endif