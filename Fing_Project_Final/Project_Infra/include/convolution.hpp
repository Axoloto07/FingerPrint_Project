#ifndef CONVOLUTION_HPP
#define CONVOLUTION_HPP

#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include "kernel.hpp"

 
using namespace cv;
//using namespace std;


//#######################################################################
//CHECK CONVOLUTION
//#######################################################################

/**
 * @brief Check the discrete convolution with an opencv function
 * 
 * @param m1 input matrice 
 * @param kernel filter
 * @param border choice of pixel extension at the boundary of the image
 * if border = 'r', pixels at the boundary will be replicated
 * if border = 'z', the image will be zero padded
 * @return output filtered matrix 
 */
Mat conv_using_filter(Mat &m1, Mat &kernel, char border);

/**
 * @brief Perform the discrete 2d convolution thanks to the FFT
 * 
 * @param m1 input matrice
 * @param kernel filter
 * @return output filtered matrix 
 */
Mat conv_using_fft(Mat &m1, Mat &kernel);

//#######################################################################
//HOME MADE CONVOLUTION
//#######################################################################

/**
 * @brief compute the convolution between the matrix m1 and m2
 * the result is with the same dimensions as the ones of m1
 * 
 * @param m1 input matrix
 * @param m2 filter
 * @param border choice of pixel extension at the boundary of the image
 * if border = 'r', pixels at the boundary will be replicated
 * if border = 'z', the image will be zero padded
 * @return output filtered matrix
 */
Mat discrete_conv(Mat &m1, Mat &m2, char border);

/**
 * @brief compute one coefficient of the discrete convolution
 * assume that m1 and kernel have the same dimensions
 * kernel is already flipped
 * @param m1 input matrix
 * @param kernel filter
 * @return value of the coefficient of the output matrix 
 */
float convol_coeff(Mat &m1, Mat &kernel);

/**
 * @brief compute a kernel for each pixel of the image depending on the position
 * of this pixel in the image
 * (pixels located inside an ellipse will be applied an identity kernel)
 * compute then the convolution of the input image with this changing kernel
 * @param m1 input image/matrix
 * @param kernel_i nb of rows of the kernel
 * @param kernel_j nb of columns of the kernel
 * @param center center of high pressure of the finger
 * @param a radius length of the ellipse
 * @param b 
 * @param position position where the filter will be applied
 * if position = 'b' the effect will be mostly on the bottom of the image
 * if position = 't'the effect will be mostly on the top of the image
 * @param normalized if normalized = 'n', the energy of the kernel applies at the top is preserved,
 * otherwise it slighty increases
 * @return output filtered matrix 
 */
Mat conv_x_y(Mat &m1, int kernel_i, int kernel_j, std::vector<int> center, float a, float b, char position, char normalize);


/**
 * @brief compute a kernel for each pixel of the image depending on the position
 * of this pixel in the image
 * the total energy of the kernel decreases as long as the distance
 * of the pixel from the center increases
 * compute the convolution of the input image with this changing kernel
 * 
 * @param m1 input image/matrix
 * @param kernel_i nb of rows of the kernel
 * @param kernel_j nb of columns of the kernel
 * @param center center of high pressure of the finger
 * @return output filtered matrix  
 */
Mat convol_energy(Mat &m1, int kernel_i, int kernel_j, std::vector<int> center);


//#######################################################################
//PADDINGS
//#######################################################################

/**
 * @brief pad a given image acording to the size of a given kernel
 *  with null values and put the input image at the center of the new padded one
 * @param m1 the input image to be padded
 * @param kernel_i the nb of rows of the kernel
 * @param kernel_j the nb of columns of the kernel
 * @return the padded image
 */
Mat padd_center(Mat &m1, int kernel_i, int kernel_j);


//#######################################################################
//KERNEL FLIPS
//#######################################################################

/**
 * @brief flip the kernel on x-axis and y-axis
 * 
 * @param kernel filter of odd size
 */
void flip_kernel(Mat &kernel);

/**
 * @brief Resize the kernel to the same size as m1 and perform a circular symmetry on its coefficients
 * the center of the kernel is placed at the position (0,0) in this new matrix
 * 
 * @param m1 input matrix
 * @param kernel filter
 * @return filter resized to m1's size 
 */
Mat kernel_swap_fft(Mat &m1, Mat &kernel);

#endif