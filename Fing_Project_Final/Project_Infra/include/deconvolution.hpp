#ifndef DECONVOLUTION_HPP
#define DECONVOLUTION_HPP

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "solvers.h"
#include "stdafx.h"


using namespace cv;
using namespace std;
using namespace alglib;


//#######################################################################
//CONVOLUTION - MATRIX METHOD
//#######################################################################

/**
 * @brief create a circulant matrix from a vector containing coefficients
 * this matrix has the same dimensions as the input image
 * the coefficients are stored in column in the matrix and moved one row down at each column
 * the coef at the top left of the circulant matrix corresponds to the middle coef of the vector
 * @param kernel_ligne the input kernel (vector) containing coefficients
 * @param input the input image
 * @return the circulant matrix
 */
Mat circulate_coeff(Mat &kernel_ligne, Mat &input);

/**
 * @brief create a vector of circulant matrices
 * each matrix is built from one row of the kernel
 * 
 * @param kernel the filter
 * @param input the input image (to get its dimensions)
 * 
 * @return a vector containing circulant matrices (one for each kernel row)
 */
vector<Mat> list_circulante(Mat &kernel, Mat &input);


/**
 * @brief create a doubly block circulant matrix from a vector of circulant matrices
 * each column/row of this matrix contains smaller matrices from vector v
 * the block-dimensions of this circulant matrix is equal to those of the input matrix
 * the block at the top left corner corresponds to the circulant matrix stored at the middle position
 * in the vector
 * @param v a vector of circulant matrices built from the kernel rows
 * @param input the input image 
 * @return the doubly block circulant matrix, which is the matrix
 * of the convolution between the kernel and the input image 
 */
Mat circulate_matrix(vector<Mat> &v, Mat &input);


/**
 * @brief compute the convolution between a vectorized input image and a kernel
 * 
 * @param K the convolution matrix
 * @param input_vector the input vectorized image
 * @return the matrix of the blurred image 
 */
Mat blurr(Mat &K, Mat &input_vector);


//#######################################################################
//DECONVOLUTION - LEAST SQUARES METHOD
//#######################################################################

/**
 * @brief solve a linear system Kx = y with the least squares method given a damping/regularization coefficient
 * this coefficient is used to have a well posed system
 * 
 * @param doubly_block the convolution matrix K
 * @param lmbda the damping coefficient
 * @param output the right member of the equation y (corrupted acquisition)
 * @return the result x (clean acquisition)
 */
Mat least_squares_result(Mat &doubly_block, float lmbda, Mat &output);


//#######################################################################
//TOOLS
//#######################################################################


/**
 * @brief overloading to extract and copy a submatrix from a source matrix to a destination matrix
 * 
 * @param i_begin row of the top left corner of the submatrix
 * @param i_dist nb of rows of the submatrix
 * @param j_begin column of the top left corner of the submatrix
 * @param j_dist nb of columns of the submatrix
 * @param src input where the submatrix is extracted
 * @param dest matrix where the submatrix must be copied
 */
void modif_block(int i_begin, int i_dist, int j_begin, int j_dist, Mat &src, Mat &dest);

/**
 * @brief put away i_suppr_top rows at the top of the matrix m1, i_suppr_bott at the bottom
 * and j_suppr/2 columns on the left and right
 * This method is used when convolving the clean acquisition with a blurr kernel
 * @param m1 the input matrix to be modified
 * @param i_suppr_top the nb of rows to erase at the top
 * @param i_suppr_bott the nb of rows to erase at the bottom
 * @param j_suppr the nb of columns to erase
 * @return the modified matrix
 */
Mat cut(Mat &m1, int i_suppr_top, int i_suppr_bott, int j_suppr);

//#######################################################################
//CONVERSION MATRIX / VECTOR
//#######################################################################

/**
 * @brief vectorise an image at format Mat
 * the matrix is stored row after row in the vector
 * 
 * @param picture the input image/matrix
 * @return the vector containing the matrix
 */
Mat vectorise(Mat &picture);

/**
 * @brief transform an input vector into a matrix
 * the coeff of the vector are stored row after row in the matrix
 * 
 * @param input_vector the input vector
 * @param output_i the nb of rows of the matrix
 * @param output_j the nb of columns of the matrix
 * @return the output matrix
 */
Mat matricise(Mat &input_vector, int output_i, int output_j);


/**
 * @brief convert a dense matrix into a sparse matrix
 * 
 * @param m1 the input dense matrix
 * @return the sparse matrix 
 */
sparsematrix matrix_to_sparse(Mat &m1);

/**
 * @brief transform a matrix into a 1D array
 * 
 * @param m1 the input matrix
 * @return the real 1D array 
 */
real_1d_array matrix_to_vector_dense(Mat &m1);

/**
 * @brief transform a 1D array into a matrix
 * the matrix is filled row after row
 * 
 * @param x the input 1D array
 * @param input the output size
 * @return the filled matrix
 */
Mat tab_to_matrix(real_1d_array &x, Mat &input);


//#######################################################################
//PRINT
//#######################################################################

/**
 * @brief print the content of a sparse matrix
 * 
 * @param m1 the input sparse matrix 
 */
void print_sparse(sparsematrix &m1);


/**
 * @brief print the content of a vector of matrices
 * overloading of operator <<
 * @param o the ostream operator
 * @param v the vector to print out
 * @return the ostream string 
 */
ostream & operator<<(ostream &o, const vector<Mat> &v);

/**
 * @brief overloading of the operator << to print the content of a 1D array
 * 
 * @param o the ostream operator
 * @param result the array to print out
 * @return the ostream string 
 */
ostream& operator<<(ostream &o, const real_1d_array &result);



#endif