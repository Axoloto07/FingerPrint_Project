#ifndef _OPTIMIZATION_HPP_
#define _OPTIMIZATION_HPP_

#include "class_image.hpp"


//---------------- loss functions ----------------

/**
 * @brief loss function quadratic
 * 
 * @param img
 * @param img
 * @param tx translation along x
 * @param ty translation along y
 * @param theta rotation angle
 * @return float 
 */
double loss_function(img i1, img i2, float tx=0, float ty=0, float theta=0);


float find_min_x(img i1, img i2, float b1 = -200, float b2 = 200, float min = INFINITY, float pmin = 0);


/**
 * @brief calculate the loss function optimized, 
 * it is defined as a covariance between 2 images
 * 
 * @param image 
 * @param tx  translation along x
 * @param ty  translation along y
 * @param theta  rotation angle
 * @return float 
 */
float loss_function_opt(img i1, img i2, float tx=0, float ty=0, float theta=0);


/**
 * @brief comppute a aditional loss function thanks 
 * to the absolute value of the difference
 * 
 * @param image 
 * @param tx  translation along x
 * @param ty  translation along y
 * @return float 
 */
float loss_function_diff(img i1, img i2, float tx=0, float ty=0);

/**
 * @brief loss function derivated according to px
 * 
 * @param img 
 * @param img
 * @param tx translation along x
 * @param ty translation along y
 * @param theta rotation angle
 * @param h step for the variation rate
 * @return float 
 */
double loss_function_pderivative_x(img i1, img i2, double tx=0, double ty=0, double theta=0, double h=1);

/**
 * @brief loss function derivated according to py
 * 
 * @param img 
 * @param img
 * @param tx translation along x
 * @param ty translation along y
 * @param theta rotation angle
 * @param h step for the variation rate
 * @return float 
 */
double loss_function_pderivative_y(img i1, img i2, double tx=0, double ty=0, double theta=0, double h=1);


//---------------- draw loss functions ----------------



/**
 * @brief draw the loss function with respect to the translation
 * according one axis
 * 
 * if a = 0 (default), we draw the loss function with respect to the loss_function
 * if a = 1, we draw the loss function with respect to the loss_function_opt
 * 
 * @param img
 * @param img
 * @param b1 begin of the interval
 * @param b2 end of the interval
 * @param a if a = 0 (default), we draw the loss function with respect to the loss_function if a = 1, we draw the loss function with respect to the loss_function_opt
 */
void draw_loss_function_x(img i1, img i2, double b1=-100, double b2=100, int a=0);

/**
 * @brief draw the loss function with respect to the translation
 * according one axis (derivative)
 * 
 * @param img
 * @param img
 * @param b1 begin of the interval
 * @param b2 end of the interval
 */
void draw_loss_function_pderivative_x(img i1, img i2, double b1=-100, double b2=100, double h=1);

/**
 * @brief draw the loss function with respect to the translation
 * according the two axis
 * 
 * if a = 0 (default), we draw the loss function with respect to the loss_function
 * if a = 1, we draw the loss function with respect to the loss_function_opt
 * 
 * @param image 
 * @param a if a = 0 (default), we draw the loss function with respect to the loss_function if a = 1, we draw the loss function with respect to the loss_function_opt
 * @return void
 */
void draw_loss_function_xy(img i1, img i2, int a = 0);


/**
 * @brief draw the loss function with respect to the translation
 * and the rotation
 * 
 * @param image 
 * @param a if a = 0 (default), we draw the loss function with respect to the loss_function if a = 1, we draw the loss function with respect to the loss_function_opt
 * @return void
 */
void display_loss_function_xytheta(img i1, img i2, int a = 0);

/**
 * @brief recursive function to make a non differentiable coordinate descent
 * it is used in draw_convergence
 * @param image 
 * @param pi i-coordinate of the pixel of the beginning of the algorithm
 * @param pj j-coordinate of the pixel of the beginning of the algorithm
 * @param al step of the descent at the beginning
 * @param list_al list of the step of the descent
 * @param p_res the result of the algorithm
 * @param cpt counter that is used to stop the recursion
 */
void coord_descent(img i1, img i2, float pi, float pj, float al, std::vector<float>* list_al, float* p_res, int cpt = 0);

/**
 * @brief recursive function to make a non differentiable coordinate descent
 * it is used in result_conv
 * 
 * @param image 
 * @param pi i-coordinate of the pixel of the beginning of the algorithm
 * @param pj j-coordinate of the pixel of the beginning of the algorithm
 * @param al step of the descent at the beginning
 * @param p_res the result of the algorithm
 * @param cpt counter that is used to stop the recursion
 */
void coord_descent_2(img i1, img i2, float pi, float pj, float al, float *p_res, int cpt = 0);

/**
 * @brief draw the parameter alpha in function of cpt
 * dsiplay the result
 * ie the convergence of the algorithm
 * 
 * 
 * @param image 
 * @param al  step of the descent
 */
void draw_convergence(img i1, img i2, float al=0.1);

/**
 * @brief display several result of the algorithm 
 * for random initial values
 * 
 * @param image 
 * @param al  step of the descent at the beginning
 */
void result_conv(img i1, img i2, float al = 0.1);



// ---------------- gradient descent algorithm ----------------

/**
 * @brief gradient descent algorithm function, used for draw convergence of the algorithm
 * 
 * @param image 
 * @param pi initial value for translation along y
 * @param pj initial value for translation along x
 * @param al step of the descent const
 * @param list_eps list of the value of derivative of the descent
 * @param p_res pointer to the result of the algorithm
 * @param eps value for the stop condition
 */
void grad_descent(img i1, img i2, double pi, double pj, double al, std::vector<double>* list_eps, double *p_res, double eps = 10);


/**
 * @brief gradient descent algorithm function, used for display results of the algorithm
 * 
 * @param image 
 * @param pi initial value for translation along y
 * @param pj initial value for translation along x
 * @param al step of the descent const
 * @param p_res pointer to the result of the algorithm
 * @param eps value for the stop condition
 */
void grad_descent_2_x(img i1, img i2, double pi, double pj, double al, double *p_res);

/**
 * @brief gradient descent algorithm function, used for display results of the algorithm
 * 
 * @param image 
 * @param pi initial value for translation along y
 * @param pj initial value for translation along x
 * @param al step of the descent const
 * @param p_res pointer to the result of the algorithm
 * @param eps value for the stop condition
 */
void grad_descent_2_y(img i1, img i2, double pi, double pj, double al, double *p_res);



/**
 * @brief gradient descent algorithm function, used for display results  of the algorithm
 * 
 * @param i1 
 * @param i2 
 * @param pi initial value for translation along y
 * @param pj initial value for translation along x
 * @param al step of the descent const
 * @param p_res value of the result of the algorithm
 */
void grad_descent_2(img i1, img i2, double pi, double pj, double al, double *p_res);

/**
 * @brief draw the convergence of the algorithm
 * 
 * @param image 
 * @param al step of the descent
 */
void draw_convergence_grad(img i1, img i2, double al = 1e-5);


/**
 * @brief compute the gradient of the loss function for several initial values
 * 
 * @param image 
 * @param al 
 */
void result_conv_grad(img i1, img i2, double al = 1e-5);



#endif