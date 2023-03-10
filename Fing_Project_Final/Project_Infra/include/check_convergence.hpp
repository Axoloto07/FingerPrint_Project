#ifndef CONVERGENCE_HPP
#define CONVERGENCE _HPP

#include <string>
#include "image.hpp"

//using namespace std;


//#######################################################################
//COMPARISON PIXEL PER PIXEL
//#######################################################################

/**
 * @brief compute the proportion of matching pixels between two images given a confidence threshold
 * 
 * @param filename1 first image
 * @param filename2 second image
 * @param threshold confidence threshold
 * @return proportion of "closed" pixels between both images 
 */
float convergence(std::string filename1, std::string filename2, float threshold);


//#######################################################################
//MEAN SQUARED ERROR
//#######################################################################

/**
 * @brief compute the mean squared error between two images
 * 
 * @param filename1 the first image
 * @param filename2 the second image
 * @return the mean squared error 
 */
float mean_squared_error(std::string filename1, std::string filename2);


//#######################################################################
//HISTOGRAM OF GRAY LEVELS
//#######################################################################

/**
 * @brief plot the gray level histogram of two input images
 * 
 * @param filename1 the input image
 * @param filename2 the input image
 * @param directory_output the directory to store the output
 */
void histogram(std::string filename1, std::string filename2, std::string directory_output);


#endif 