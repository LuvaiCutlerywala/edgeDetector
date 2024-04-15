#include "../include/processor.hpp"
#include "../include/img_utils.hpp"

#include <cmath>

Mat generate_x_sobel_kernel()
{
    const short g_x[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};

    Mat G_x(3, 3, CV_16SC1);
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            G_x.at<short>(i, j) = g_x[i][j];
        }
    }

    return G_x;
}

Mat generate_y_sobel_kernel()
{
    const short g_y[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

    Mat G_y(3, 3, CV_16SC1);
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            G_y.at<short>(i, j) = g_y[i][j];
        }
    }

    return G_y;
}


Mat processor::calculateIntensityGradient(Mat img)
{
    Mat output(img.rows - 2, img.cols - 2, CV_64FC2);
    Mat x_kernel = generate_x_sobel_kernel();
    Mat y_kernel = generate_y_sobel_kernel();
    
    for(int i = 1; i < img.rows - 1; ++i)
    {
        for(int j = 1; j < img.cols - 1; ++j)
        {
            
        }
    }

    return output;   
}