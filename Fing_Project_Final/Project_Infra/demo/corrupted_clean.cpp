#include <iostream>
#include "../include/convolution.hpp"
#include "../include/deconvolution.hpp"
#include "../include/check_convergence.hpp"

//function to obtain the corrupted_finger by matrix multiplication and recover the clean_finger 
int main(){

//#######################################################################
//GET THE INPUTS
//#######################################################################  


    img fingerprint("../Project_Infra/images/clean_blur_ex.png");
    img tmp = fingerprint.cast_to_float();
    Mat input_dense = tmp.get_matrix();

    //choose the option to run
    bool corr;
    std::cout<<"Do you want the corrupted version? (enter 1 for yes, 0 for no)"<<std::endl;
    std::cin>>corr;
    bool check = 0;
    if (corr){
        std::cout<<"Do you want the checking of our results? (enter 1 for yes, 0 for no)"<<std::endl;
        std::cin>>check;
    }
    bool clean;
    std::cout<<"Do you want the clean version? (enter 1 for yes, 0 for no)"<<std::endl;
    std::cin>>clean;


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

    std::vector<Mat> v = list_circulante(kernel, input_dense);
    Mat doubly_block = circulate_matrix(v, input_dense);


//#######################################################################
//TEST OF THE CONVOLUTION MATRIX
//#######################################################################

    if(corr){
        //create the corrupted image
        Mat result = blurr(doubly_block, input_dense);
        //cut the image to have the good dimensions
        Mat result_1 = cut(result, 3,1,4);

        //adjust the colors of the image cut
        for (int i=0; i<result_1.rows; i++){
            for (int j=0; j<result_1.cols; j++){
                result_1.at<float>(i, j) *= 1.15;
            }
        }

        //save the result in a new image
        img picture = img(result);
        picture.save("demo_results/corrupted.png");
        picture = img(result_1);
        picture.save("demo_results/corrupted_cut.png");

        //check convergence
        convergence("demo_results/corrupted_cut.png","../Project_Infra/images/corrupted_blur_ex.png", 0.05);
        mean_squared_error("demo_results/corrupted_cut.png","../Project_Infra/images/corrupted_blur_ex.png");
        histogram("../Project_Infra/images/corrupted_blur_ex.png", "demo_results/corrupted_cut.png", "demo_results");
    }
//#######################################################################
//CHECK WITH THE CONVOLUTION ALGORITHM
//#######################################################################

    if(check){
        //construction of the kernel
        Mat kernel_1= Mat::zeros(5,5,CV_32F);
        for (int i=0; i<kernel_1.rows; i++){
            kernel_1.at<float>(i,kernel_1.rows-1-i) = 1.0/7;
        }
        kernel_1.at<float>(3,2) = 1.0/7;
        kernel_1.at<float>(4,2) = 1.0/7;

        //do the convolution with the algorithm of Opencv
        Mat result_2 = conv_using_filter(input_dense, kernel_1, 'z');

        //save the result in a new image
        img verif = img(result_2);
        verif.save("demo_results/corrupted_verif.png");

        //check convergence
        convergence("demo_results/corrupted_verif.png", "demo_results/corrupted.png", 0.05);
        mean_squared_error("demo_results/corrupted_verif.png", "demo_results/corrupted.png");
    }
    

//#######################################################################
//LEAST SQUARES DECONVOLUTION
//#######################################################################

    if(clean){
        //-------------get the output-------------------
        img fingerprint("../Project_Infra/images/corrupted_blur_ex.png");
        img tmp = fingerprint.cast_to_float();
        Mat output = tmp.get_matrix();

        Mat padded = Mat::zeros(output.rows+4,output.cols+4,output.type());

        //zero pad the borders to reach the size of clean finger
        copyMakeBorder(output,padded,3,1,2,2, BORDER_CONSTANT, 0);

        //solve the system with the least squares method
        Mat result = least_squares_result(doubly_block,0.5,padded);

        //save the result in a new image
        img picture = img(result);
        picture.save("demo_results/clean.png");
        
        //check convergence
        convergence("../Project_Infra/images/clean_blur_ex.png", "demo_results/clean.png", 0.05);
        mean_squared_error("../Project_Infra/images/clean_blur_ex.png", "demo_results/clean.png");
        histogram("../Project_Infra/images/clean_blur_ex.png", "demo_results/clean.png", "demo_results");
    }
return 0;
}