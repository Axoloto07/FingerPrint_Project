#ifndef CONVERGENCE_HPP
#define CONVERGENCE _HPP

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "class_image.hpp"

using namespace std;

/**
 * @brief compute the proportion of matching pixels between two images given a confidence threshold
 * 
 * @param filename1 first image
 * @param filename2 second image
 * @param threshold confidence threshold
 * @return proportion of "closed" pixels between both images 
 */
float convergence(string filename1, string filename2, float threshold);

/**
 * @brief compute the mean squared error between two images
 * 
 * @param filename1 the first image
 * @param filename2 the second image
 * @return the mean squared error 
 */
float mean_squared_error(string filename1, string filename2);

#endif 