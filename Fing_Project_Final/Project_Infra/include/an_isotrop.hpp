#ifndef AN_ISOTROP_HPP
#define AN_ISOTROP_HPP

#include <vector>
#include <opencv2/opencv.hpp>
#include "image.hpp"
using namespace std;
using namespace cv;

//#######################################################################
//ISOTROPIC TRANSFORMATIONS
//#######################################################################

/**
 * @brief compute a gaussian for each coefficient of the matrix
 * we normalise each coeff by dividinfg it by its maximal distance to the center 
 * we calculated before
 * 
 * p is a coefficient to choose the shape of the gaussian
 * 
 * @param x 
 * @param y 
 * @param p 
 * @param ci 
 * @param cj 
 * @param matrix 
 * @return float 
 */
float coef1(int x, int y, int p, int ci, int cj, Mat matrix);

/**
 * @brief compute a gaussian with a plateau
 * for each coefficient of the matrix
 * 
 * https://www.researchgate.net/figure/Thinner-acrylic-plates-cause-more-total-internal-reflection-points-and-thus-a-wider-and_fig3_221308446
 * https://stats.stackexchange.com/questions/203629/is-there-a-plateau-shaped-distribution
 * 
 * p is a coeff to choose the shape of the gaussian
 * 
 * @param x 
 * @param y 
 * @param p 
 * @param ci 
 * @param cj 
 * @param matrix 
 * @return float 
 */
float coef2(int x, int y, int p, int ci, int cj, Mat matrix);

/**
 * @brief We apply one of the functions to each coeff of an image
 * 
 * @param p 
 * @param input 
 * @return img
 */
img isotrop_transf(int p, img input);

//#######################################################################
//ANISOTROPIC TRANSFORMATIONS
//#######################################################################

/**
 * @brief compute the anisotropic gaussian transform for one pixel (i,j)
 * depending on its position wrt a given ellipse
 * 
 * @param i
 * @param j the coordinates of the pixel
 * @param a 
 * @param b the lenght of the axis of the ellipse
 * @param center the center of pressure of the finger (and the ellipse) 
 *  
 * @return the new value of the pixel obtained after these continuous anisotrop transform 
 */
float c_i_j(int i, int j, int a, int b, vector<int> center, Mat matrix);

/**
 * @brief perform the anisotrop gaussian transform on the whole finger given a direction alpha
 * @param alpha the angle between the x-axis and the direction of the transform
 * @param input the input image
 * @return the new transformed image 
 */
img anisotrop_transf(float alpha, img input);





#endif