// #include <opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include "deconvolution.hpp"
#include "convolution.hpp"
#include "class_image.hpp"
#include "kernel.hpp"
#include "check_convergence.hpp"
#include "solvers.h"
#include "alglib/stdafx.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace alglib;
using namespace cv;
#include <iostream>
using namespace std;

void test_deconvolution(){

//#######################################################################
//GET THE INPUTS
//#######################################################################  


    img fingerprint("images/clean_blur_ex.png");
    img tmp = fingerprint.cast_to_float();
    Mat input_dense = tmp.get_matrix();

    //input_dense = cut(input_dense,4,4);
    //input_dense = (Mat_<float>(2,3,CV_32F)<<1,2,3,4,5,6);


//#######################################################################
//CONSTRUCTION OF THE KERNEL
//#######################################################################


    Mat kernel= Mat::zeros(5,5,CV_32F);
    for (int i=0; i<kernel.rows; i++){
        kernel.at<float>(i,kernel.rows-1-i) = 1.0/7;
    }
    kernel.at<float>(3,2) = 1.0/7;
    kernel.at<float>(4,2) = 1.0/7;

    flip_kernel(kernel);
    //Mat kernel= (Mat_<float>(3,3,CV_32F)<<1,2,3,4,5,6,7,8,9);


//#######################################################################
//CREATION OF THE MATRIX OF CONVOLUTION
//#######################################################################

    // // Mat padded_kernel = padd_bottom_left(kernel, input_dense);


    vector<Mat> v = list_circulante(kernel, input_dense);
    Mat doubly_block = circulate_matrix(v, input_dense);
    cout<<doubly_block.rows<<" "<<doubly_block.cols<<endl;


//#######################################################################
//TEST OF THE CONVOLUTION MATRIX
//#######################################################################

    if(0){
        Mat result = blurr(doubly_block, input_dense, kernel);
        // cout<<result.rows<<" "<<result.cols<<endl;

        //Mat result_1 = cut(result, 3,1,4);

        //histo chag de couleur
        // //cout<<result;
        // for (int i=0; i<result_1.rows; i++){
        //     for (int j=0; j<result_1.cols; j++){
        //         result_1.at<float>(i, j) *= 1.15;
        //     }
        // }

        img picture = img(result);
        picture.save("corrupted.png");
        //mean_squared_error("corrupted.png","corrupted_blur_ex.png");
        //float threshold = 0.05;
        //convergence("images/corrupted_blur_ex.png", "corrupted.png", threshold);
        //convergence("corrupted_flip.png", "corrupted_verif.png", threshold);
    
    }

    //----------------check with convolution algorithm--------------------

    if(0){
        Mat kernel_1= Mat::zeros(5,5,CV_32F);
        for (int i=0; i<kernel_1.rows; i++){
            kernel_1.at<float>(i,kernel_1.rows-1-i) = 1.0/7;
        }
        kernel_1.at<float>(3,2) = 1.0/7;
        kernel_1.at<float>(4,2) = 1.0/7;
        Mat result_2 = conv_using_filter(input_dense, kernel_1, 'z');
        //save the result in a new image
        img verif = img(result_2);
        verif.save("corrupted_verif.png");
        convergence("corrupted_verif.png", "corrupted.png", 0.05);
        mean_squared_error("corrupted_verif.png", "corrupted.png");
    }
    

//#######################################################################
//LEAST SQUARES DECONVOLUTION
//#######################################################################

    if(0){
        //-------------get the output-------------------
        img fingerprint("images/corrupted_blur_ex.png");
        img tmp = fingerprint.cast_to_float();
        Mat output = tmp.get_matrix();
        Mat padded = Mat::zeros(output.rows+4,output.cols+4,output.type());
        //replicate the border to reach the size of tclean_finger
        //copyMakeBorder(output,padded,3,1,2,2, BORDER_REPLICATE);
        //zero padd the borders to reach the size of clean finger
        //marche le mieux
        copyMakeBorder(output,padded,3,1,2,2, BORDER_CONSTANT, 0);
        //mirror the borders to reach the size of clean finger
        //copyMakeBorder(output,padded,3,1,2,2, BORDER_REFLECT);

        //--------------------------------------------

        Mat result = least_squares_result(doubly_block,0.5,padded);
        img picture = img(result);
        picture.save("clean_solver.png");
    }



    // real_1d_array x = "[1,2,3,4]";

    // // Mat result = tab_to_mat(x);
    // // cout<<result;
    // Mat input = (Mat_<float>(2,2,CV_32F)<<0,5,0,1,1,5,5,0,6,0,0,4);
    // cout<<tab_to_matrix(x,input);
    // sparsematrix m1 = matrix_to_sparse(input, 2);
    // print_sparse(m1);
    // cout<<input<<endl;
    //cout<<matrix_to_vector_dense(input, 5);
    

    // cout<<input<<endl;
    // real_1d_array t= vector_to_vector_dense(input, 2);
    // cout<<t<<endl;
    // Mat a = tab_to_mat(t);
    // cout<<a<<endl;
    
    // cout<<padd_output(input, 4,4);
    // //cout<<input;
    // Mat resu = padd_output(input, 4,4);
    // cout<<resu;
    // cout<<input<<endl;
    // switch_rows(input);
    // cout<<input<<endl;
    // input_dense = (Mat_<float>(2,2,CV_32F)<<1,2,3,4);
    // Mat vector = vectorise(input_dense);
    // cout<<matricise(vector, 2,2);
    // Mat kernel = (Mat_<float>(4,1,CV_32F)<<1,2,3,4);
    // cout<<kernel;
    // Mat K = create_K(input, kernel);
    // cout<<K;
    //cout<<kernel_vector<<endl;
    //cout<<picture;
    //Mat image = vectorise(picture);
    // Mat output = matricise(kernel, 2, 2);
    // cout<<output;
    //cout <<output;
    //cout<<image;
    //cout<<m1 * image;
    //Mat K = create_K(4,4,4,4,kernel_vector);
    //cout<<K;

    // Mat dest = (Mat_<float>(3,3,CV_32F)<<1,2,1,4,0,0,1,0,0);
    // cout<<dest<<endl;
    // Mat src = (Mat_<float>(2,2,CV_32F)<<5,5,6,9);
    // modif_block(1,1,2,2,src, dest);
    // cout<<dest;
    

}