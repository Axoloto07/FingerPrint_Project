#ifndef STRUCTURING_ELEMENT_HPP
#define STRUCTURING_ELEMENT_HPP

#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//#######################################################################
//LIBRARY OF STRUCTURING ELEMENTS
//#######################################################################


/**
 * @brief create a structuring element with a central cross, or a single row or a single column
 * depending on the choice of the user
 * 
 * @param size_i the nb of rows of the kernel
 * @param size_j the nb of columns of the kernel
 * @param type the form of the principal motif (cross, row or column)
 * 
 * @return the structuring element 
 */
Mat elt_struct_cross_col_row (int size_i, int size_j, string type);

/**
 * @brief create a squared structuring element
 * 
 * @param size_i the nb of rows of the kernel
 * @param size_j the nb of columns of the kernel
 * @return the structuring element 
 */
Mat elt_struct_square (int size_i, int size_j);

/**
 * @brief create a disc-formed structuring element
 * dimensions should be odd and equal one to another to have a circle (otherwise it is an ellipse)
 * 
 * @param size_i the nb of rows of the kernel
 * @param size_j the nb of columns of the kernel
 * @return the structuring element  
 */
Mat elt_struct_disc (int size_i, int size_j);

/**
 * @brief create an identity structuring element
 * 
 * @param size_i the nb of rows of the kernel
 * @param size_j the nb of columns of the kernel
 * @return the structuring element   
 */
Mat elt_struct_id(int size_i, int size_j);

/**
 * @brief create a diamond-formed structuring element
 * dimensions should be equal to have a well formed diamond
 * 
 * @param size_i the nb of rows of the kernel
 * @param size_j the nb of columns of the kernel
 * @return the structuring element 
 */
Mat elt_struct_diamond (int size_i, int size_j);


/**
 * @brief create a structuring element with a diagonal of ones
 * the user can choose to have a diagonal coming from the top left corner to the bottom right corner
 * (option 'diag') or conversely from the top right corner to the bottom left corner (option 'diag_inv')
 * 
 * @param size_i the nb of rows of the kernel
 * @param size_j the nb of columns of the kernel
 * @param position the sense of the diagonal
 * @return the structuring element  
 */
Mat elt_struct_diag(int size_i, int size_j, string position);

/**
 * @brief 
 * 
 * @param size_i 
 * @param size_j 
 * @return Mat 
 */
Mat elt_struct_hole(int size_i, int size_j);



#endif