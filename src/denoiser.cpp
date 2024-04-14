#include "../include/denoiser.hpp"

#include <cmath>
#include <cassert>
#include <iostream>

double gaussian_kernel(int x, int y)
{
    const int sigma = 1.2;
    return (exp(-1 * (pow(x, 2) + pow(y, 2)) / (2 * pow(sigma, 2))) / (2 * pow(sigma, 2) * PI));
}

Mat generate_filter()
{
    Mat filter(3, 3, CV_64FC3);
    for(int i = 0; i < filter.rows; ++i)
    {
        for(int j = 0; j < filter.cols; ++j)
        {
            filter.at<double>(i, j) = gaussian_kernel(i - 1, j - 1);
        }
    }

    return filter;
}

void denoiser::denoise(Mat img, Mat output)
{
    Mat filter = generate_filter();

    //Filter sum to used in normalisation for brightness correction.
    double filter_sum = 0;
    for(int i = 0; i < filter.rows; ++i)
    {
        for(int j = 0; j < filter.cols; ++j)
        {
            filter_sum += filter.at<double>(i, j);
        }
    }

    for(int i = 1; i < img.rows - 1; ++i)
    {
        for(int j = 1; j < img.cols - 1; ++j)
        {
            output.at<Vec3b>(i - 1, j - 1) = normalise(convolve_matrices(extract_sample_matrix(img, i, j), filter), filter_sum);
        }
    }
}

Mat denoiser::extract_sample_matrix(Mat img, int x, int y)
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

Vec3b denoiser::convolve_matrices(Mat sample, Mat filter)
{
    assert((sample.rows == filter.rows) && (sample.cols == filter.cols));
    
    Vec3b total = 0;
    for(int i = 0; i < sample.rows; ++i)
    {
        for(int j = 0; j < sample.cols; ++j)
        {
            total += sample.at<Vec3b>(i, j) * filter.at<double>(i, j);
        }
    }

    return total;
}

Vec3b denoiser::normalise(Vec3b img, double normalisation_factor)
{
    Vec3b out(0, 0, 0);
    for(int i = 0; i < 3; ++i)
    {
        out[i] = img[i] / normalisation_factor;
    }

    return out;
}
