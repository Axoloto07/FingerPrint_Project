#ifndef MORPHOLOGICAL_HPP
#define MORPHOLOGICAL_HPP

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <opencv2/opencv.hpp>
#include "structuring_element.hpp"


using namespace cv;
using namespace std;

//#######################################################################
//BINARIZATION OF IMAGES
//#######################################################################

/**
 * @brief compute the occurence of each pixel intensity in a given input image
 * store the results in a vector of lenght 256 (nb of levels of gray)
 * 
 * @param input the input image
 * @return a vector containing, for each level of gray, the nb of pixels having this intensity 
 */
vector<float> proba_distr(Mat &input);

/**
 * @brief the pixels of the image are separated in two classes given an intensity threshold 'level'
 * this function computes the between-class variance
 * 
 * @param level the intensity threshold : pixels with higher intensity are stored in the second class
 * while others are stored in the first class
 * @param frequency the probability occurence of each pixel intensity in the image
 * @return the between-class variance
 */
float between_class_variance(int level, vector<float> &frequency);

/**
 * @brief compute the optimal intensity threshold to separate pixels
 * in 2 classes according to their intensity
 * the method is inspired by Otsu's method
 * the goal is to maximize the between-class variance over all the pixel intensities seen as threshold
 * 
 * @param frequency the probability occurence of each pixel intensity in the image
 * @return the optimal intensity threshold 
 */
float find_threshold(vector<float> &frequency);

/**
 * @brief compute the binarized version of an input image
 * pixels are transformed either in white or in black depending on their original intensity
 * if their intensity is higher than the threshold theyr are turned black
 * at the end, the background of the picture is white
 * 
 * @param input the input image
 * @param threshold the intensity threshold
 * @return the binarized image 
 */
Mat binarization(Mat &input, int threshold);

/**
 * @brief compute the negative version of an image
 * this function is used for binary erosion/dilation filterings
 * 
 * @param input the input image
 */
void convert_negative(Mat &input);


//#######################################################################
//EROSION & DILATION FILTERINGS
//#######################################################################

/**
 * @brief compute the erosion coefficient for center pixel of a binary image
 * here we suppose that image and struct element have the same sizes (they totally overlap)
 * if the black pixels of the kernel are totally included in the black pixels of the image
 * then the pixel of the image takes value 1 (stay black)
 * 
 * @param elt_struct the structuring element
 * @param input the binary input image
 * @return the new value of the pixel 
 */
float erosion_coeff(Mat &elt_struct, Mat &input);

/**
 * @brief compute the dilation coefficient for the center pixel of a binary image
 * here we suppose that image and struct element have the same sizes (they totally overlap)
 * if at least one black pixel of the kernel overlap one black pixel of the image
 * then the pixel of the image takes value 1 (stay black)
 * 
 * @param elt_struct the structuring element
 * @param input the binary input image
 * @return the new value of the pixel  
 */
float dilatation_coeff(Mat &elt_struct, Mat &input);

/**
 * @brief compute the dilation coefficient for the center pixel of a grayscale image
 * here we suppose that image and struct element have the same sizes (they totally overlap)
 * the new value of the pixel of the image is equal to the minimal intensity among 
 * the black pixels of the image overlapped by the black pixels of the kernel
 * 
 * @param elt_struct the structuring element
 * @param input the binary input image
 * @return the new value of the pixel 
 */
float erosion_coeff_grayscale(Mat &elt_struct, Mat &input);

/**
 * @brief compute the dilation coefficient for the center pixel of a grayscale image
 * here we suppose that image and struct element have the same sizes (they totally overlap)
 * the new value of the pixel of the image is equal to the maximal intensity among 
 * the black pixels of the image overlapped by the black pixels of the kernel
 * 
 * @param elt_struct the structuring element
 * @param input the binary input image
 * @return the new value of the pixel 
 */
float dilatation_coeff_grayscale(Mat &elt_struct, Mat &input);

/**
 * @brief compute the eroded/dilated version of a binary or grayscale
 * input image given a structuring element
 * the user can choose the type of filtering (binary/grayscale and erosion/dilation)
 * by entering the proper third argument
 * 
 * @param elt_struct the structuring element
 * @param input the input image (grayscale or binary)
 * @param filter_type the filtering type : either erosion or dilation and either grayscale of=r binary
 * @return the dilated/eroded image 
 */
Mat erosion_dilatation(Mat &elt_struct, Mat &bin, string filter_type);


//#######################################################################
//NON UNIFORM FILTERINGS
//#######################################################################


/**
 * @brief compute the dilated version of a grayscale input image given a structuring element
 * the filtering is not uniform (the kernel changes depending on the position of the pixel)
 * several elliptic zones are determined, where the kernel to apply changes
 * 
 * @param elt_struct_i the nb of rows of each structuring element
 * @param elt_struct_j the nb of columns of each structuring element
 * @param a the radius lenghts of 2 elliptic zones
 * @param b 
 * @param radius the radius of the last circular zone
 * @param center the center of high pressure, also center of some zones
 * @param bin the input image
 * @param bin_gray the option binary or grayscale image
 * @return the non uniformly dilated grayscale image 
 */
Mat dilation_nunif(int elt_struct_i, int elt_struct_j, float a, float b, float radius, vector<int> &center, Mat &bin, string bin_gray);

/**
 * @brief 
 * 
 * @param elt_struct_i 
 * @param elt_struct_j 
 * @param bin 
 * @param a 
 * @param b 
 * @return Mat 
 */
Mat erosion_nunif(int elt_struct_i, int elt_struct_j, Mat &bin, float a, float b, vector<int> center, float radius);

Mat erosion_nunif_bin(int elt_struct_i, int elt_struct_j, Mat &bin, float a, float b, vector<int> center, float radius);

//#######################################################################
//TOOLS
//#######################################################################

/**
 * @brief overloading of operator << to print out the content of a vector of float
 * 
 * @param o the ostream operator
 * @param v the vector to display
 * @return the ostream operator
 */
ostream & operator<<(ostream &o, const vector<float> &v);

#endif