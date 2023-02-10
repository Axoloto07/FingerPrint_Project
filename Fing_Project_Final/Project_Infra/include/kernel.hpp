#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
//using namespace std;

//#######################################################################
//LIBRARY OF CONVOLUTION KERNELS
//#######################################################################

/**
 * @brief create a gaussian kernel depending on given standard deviations
 * 
 * @param sigma_i standard deviation in direction i
 * @param sigma_j standard deviation in direction j
 * @param size_i nb of rows of the kernel
 * @param size_j nb of columns of the kernel
 * @return the gaussian kernel with standard deviation sqrt(sigma_i*sigma_j)
 */
Mat kernel_gaussian(float sigma_i, float sigma_j, int size_i, int size_j);


/**
 * @brief create a box blur kernel : all the coefficients are equal
 * 
 * @param size_i nb of rows of the kernel
 * @param size_j nb of columns of the kernel
 * @return the box blur kernel
 */
Mat kernel_blurred(int size_i, int size_j);


/**
 * @brief create a kernel to sharpen the image
 * 
 * @param size_i nb of rows of the kernel
 * @param size_j nb of columns of the kernel
 * @param value value of the central cross in the kernel, big value = sharpen strongly
 * @return the kernel
 */
Mat kernel_sharpen (int size_i, int size_j, float value);

/**
 * @brief create a kernel that lighten or darken the image
 * 
 * @param size_i nb of rows of the kernel
 * @param size_j nb of columns of the kernel
 * @param value value at the center of the kernel : value = 1 : identity, value > 1 : lighten, value < 1 : darken
 * @return the kernel
 */
Mat kernel_id_light_dark(int size_i, int size_j, float value);

/**
 * @brief create a kernel with one column of non null coefficients in order to pull the image
 * towards the top. The kernel depends on the position of the pixel in the input image
 * @param size_i nb of rows of the kernel
 * @param size_j nb of columns of the kernel
 * @param n coordinates of the pixel in the input image
 * @param m
 * @param center the center of the highest pressure of the finger 
 * @return the non uniform pull kernel 
 */
Mat kernel_pull(int size_i, int size_j, int n, int m, std::vector<int> center);


//#######################################################################
//NON UNIFORM CONVOLUTION
//#######################################################################

/**
 * @brief create a kernel for each pixel depending on its position in the input image
 * this kernel tends to the identity kernel for pixels located inside a given ellipse
 * this kernel performs a motion blur on the image
 * 
 * @param size_i nb of rows of the kernel
 * @param size_j nb of columns of the kernel
 * @param center center of high pressure of the finger
 * @param a radius of the ellipse
 * @param b 
 * @param n position of the pixel (rows)
 * @param m position of the pixel (columns)
 * @param normalize if normlized = 'n', the energy of the kernel is preserved, otherwise
 * it slightly increases
 * @return the kernel 
 */
Mat kernel_nunif(int size_i, int size_j, std::vector<int> center, float a, float b, int n, int m, char normalize);

/**
 * @brief create a kernel for each pixel depending on its position in the input image.
 * this kernel tends to the identity kernel for pixels located inside a given circle
 * centered at the middle of the image.
 * this kernel performs an uniform blur on the bottom of the image
 * 
 * @param size_i nb of rows of the kernel
 * @param size_j nb of columns of the kernel
 * @param r radius of the circle
 * @param m1_rows nb of rows of the input image
 * @param m1_cols nb of columns of the input image
 * @param n position of the pixel (rows)
 * @param m position of the pixel (columns)
 * @return the non uniform kernel
 */
Mat kernel_bottom(int size_i, int size_j, float r, int m1_rows, int m1_cols, int n , int m);

/**
 * @brief create a kernel with decreasing energy depending on the position of the pixel in the input image
 * 
 * @param center center of high pressure of the finger
 * @param n position of the pixel (rows)
 * @param m position of the pixel (columns)
 * @param size_i nb of rows of the kernel
 * @param size_j nb of columns of the kernel
 * @param m1_rows nb of rows of the input matrix
 * @param m1_cols nb of columns of the input matrix
 * @return the kernel 
 */
Mat kernel_energy(std::vector<int> center, int n, int m, int size_i, int size_j, int m1_rows, int m1_cols);


//#######################################################################
//TOOLS
//#######################################################################


/**
 * @brief compute the negative version of the input image
 * 
 * @param m1 the input image
 */
void negative_img(Mat &m1);

/**
 * @brief normalize the coefficients of a given kernel such that its energy is preserved
 * 
 * @param m1 the kernel
 * @param sum the value used to normalize the coefficients
 */
void normalize_mat(Mat &m1, float sum);


#endif