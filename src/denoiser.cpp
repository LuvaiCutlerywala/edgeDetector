#include "../include/denoiser.hpp"
#include "../include/img_utils.hpp"

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

    Mat buffered_img = add_buffer_zone(img);

    for(int i = 1; i < buffered_img.rows - 1; ++i)
    {
        for(int j = 1; j < buffered_img.cols - 1; ++j)
        {
            output.at<Vec3b>(i - 1, j - 1) = normalise(
                img_utils::convolve_matrices<Vec3b, double>(
                    img_utils::extract_sample_matrix(buffered_img, i, j),
                    filter),
                filter_sum
            );
        }
    }
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

Mat denoiser::add_buffer_zone(Mat img)
{
    Mat buffered_img(img.rows + 2, img.cols + 2, CV_8UC3);
    
    int l = 0;
    for(int i = 1; i < buffered_img.rows - 1; ++i)
    {
        for(int j = 0; j < buffered_img.cols; ++j)
        {
            if(j == 1)
            {
                l = 0;
            } else if(j == img.rows)
            {
                l = img.rows - 1;
            }

            buffered_img.at<Vec3b>(i, j) = img.at<Vec3b>(i - 1, l);
            l++;
        }
    }

    for(int j = 0; j < buffered_img.cols; ++j)
    {
        buffered_img.at<Vec3b>(0, j) = buffered_img.at<Vec3b>(1, j);
    }

    for(int j = 0; j < buffered_img.cols; ++j)
    {
        buffered_img.at<Vec3b>(buffered_img.rows - 1, j) = buffered_img.at<Vec3b>(buffered_img.rows - 2, j);
    }

    return buffered_img;
}
