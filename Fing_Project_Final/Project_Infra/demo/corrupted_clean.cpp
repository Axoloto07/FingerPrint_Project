#include <iostream>
#include "../include/deconvolution.hpp"
#include "../include/check_convergence.hpp"

int main(){

//#######################################################################
//GET THE INPUTS
//#######################################################################  

    //get the input image
    img fingerprint("images/clean_blur_ex.png");
    img tmp = fingerprint.cast_to_float();
    Mat input_dense = tmp.get_matrix();
    //choose the option to run
    bool corr;
    cout<<"Do you want the corrupted version? (enter 1 for yes, 0 for no)"<<endl;
    cin>>corr;
    bool check = 0;
    if (corr){
        cout<<"Do you want the checking of our result? (enter 1 for yes, 0 for no)"<<endl;
        cin>>check;
    }
    bool clean;
    cout<<"Do you want the clean version? (enter 1 for yes, 0 for no)"<<endl;
    cin>>clean;


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


//#######################################################################
//CREATION OF THE MATRIX OF CONVOLUTION
//#######################################################################

    vector<Mat> v = list_circulante(kernel, input_dense);
    Mat doubly_block = circulate_matrix(v, input_dense);


//#######################################################################
//TEST OF THE CONVOLUTION MATRIX
//#######################################################################

    if(corr){
        Mat result = blurr(doubly_block, input_dense, kernel);

        Mat result_1 = cut(result, 3,1,4);

        //Please decomment to adjust the colors of the image
        // for (int i=0; i<result.rows; i++){
        //     for (int j=0; j<result.cols; j++){
        //         result.at<float>(i, j) *= 1.15;
        //     }
        // }

        img picture = img(result);
        picture.save("corrupted.png");
        picture = img(result_1);
        picture.save("corrupted_cut.png");

        convergence("corrupted_cut.png","corrupted_blur_ex.png", 0.05);
        mean_squared_error("corrupted_cut.png","corrupted_blur_ex.png");
    
    }

    //----------------check with convolution algorithm--------------------

    if(check){
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

    if(clean){
        //-------------get the output-------------------
        img fingerprint("images/corrupted_blur_ex.png");
        img tmp = fingerprint.cast_to_float();
        Mat output = tmp.get_matrix();

        Mat padded = Mat::zeros(output.rows+4,output.cols+4,output.type());

        //zero padd the borders to reach the size of clean finger
        copyMakeBorder(output,padded,3,1,2,2, BORDER_CONSTANT, 0);

        //replicate the border to reach the size of clean_finger
        //copyMakeBorder(output,padded,3,1,2,2, BORDER_REPLICATE);
        
        //mirror the borders to reach the size of clean finger
        //copyMakeBorder(output,padded,3,1,2,2, BORDER_REFLECT);

        //--------------------------------------------

        Mat result = least_squares_result(doubly_block,0.5,padded);
        img picture = img(result);
        picture.save("clean.png");
        convergence("clean_blur_ex.png", "clean.png", 0.05);
        mean_squared_error("clean_blur_ex.png", "clean.png");
    }
return 0;
}