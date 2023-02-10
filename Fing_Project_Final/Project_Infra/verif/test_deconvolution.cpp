#include <iostream>
#include "../include/deconvolution.hpp"
#include "../include/check_convergence.hpp"

//function to test some tools for the deconvolution
int main(){
    
    std::cout<<"PLEASE CHOOSE THE OPTION YOU WANT TO RUN : enter 'if(1)' instead of 'if(0)'"<<std::endl;
//#######################################################################
//GET THE INPUTS
//#######################################################################  

    Mat input_dense = (Mat_<float>(3,3,CV_32F)<<1,2,3,5,5,9,6,5,9);


//#######################################################################
//CONSTRUCTION OF THE KERNEL
//#######################################################################

    Mat kernel= (Mat_<float>(3,3,CV_32F)<<1,2,3,4,5,6,7,8,9);


//#######################################################################
//VERIFICATION OF THE MATRIX OF CONVOLUTION
//#######################################################################

    if(1){

        std::cout<<std::endl<<"Test of matrix of convolution : "<<std::endl;
        std::cout<<"Verification coefficient per coefficient..."<<std::endl;
        std::vector<Mat> v = list_circulante(kernel, input_dense);
        Mat doubly_block = circulate_matrix(v, input_dense);
        Mat verif = (Mat_<float>(9,9,CV_32F)<<
        5,6,0,8,9,0,0,0,0,
        4,5,6,7,8,9,0,0,0,
        0,4,5,0,7,8,0,0,0,
        2,3,0,5,6,0,8,9,0,
        1,2,3,4,5,6,7,8,9,
        0,1,2,0,4,5,0,7,8,
        0,0,0,2,3,0,5,6,0,
        0,0,0,1,2,3,4,5,6,
        0,0,0,0,1,2,0,4,5);
        int b = 0;
        for (int i = 0; i<verif.rows; i++){
            for (int j=0; j<verif.cols; j++){
                if (verif.at<float>(i,j) != doubly_block.at<float>(i,j)){
                    std::cout<<"Coefficients "<<i<<" "<<j<<" don't match"<<std::endl;
                    b=1;
                    goto exit;
                }
            }
        }
        exit:
        if(b == 0){
            std::cout<<"Matrices are the same"<<std::endl;
        }
        else{
            std::cout<<"Matrices are different"<<std::endl;

        }

    }
//#######################################################################
//VERIFICATION OF THE SPARSE MATRIX CONSTRUCTION
//#######################################################################
    
    if(1){
        std::cout<<std::endl<<"Test of sparse matrix : "<<std::endl;
        sparsematrix m1 = matrix_to_sparse(input_dense);
        std::cout<<"Dense matrix : "<<std::endl;
        std::cout<<input_dense<<std::endl;
        std::cout<<"Sparse matrix : "<<std::endl;
        print_sparse(m1);
    }


    if(1){
        std::cout<<std::endl<<"Test of std::vectorisation/matricisation : "<<std::endl;
        std::cout<<"Input : "<<std::endl<<input_dense<<std::endl;
        real_1d_array result = matrix_to_vector_dense(input_dense);
        real_1d_array verif = "[1, 2, 3, 5, 5, 9, 6, 5, 9]";
        std::cout<<"Result : "<<result;
        std::cout<<"Verification : "<<verif;
        std::cout<<"Verification coefficient per coefficient..."<<std::endl;
        int b=0;
        for (int i = 0; i<verif.length(); i++){
            if (verif[i] != result[i]){
                    std::cout<<"Coefficients "<<i<<" don't match"<<std::endl;
                    b=1;
                    goto exit1;
            }

        }
        exit1:
        if(b == 0){
            std::cout<<"std::vectors are the same"<<std::endl;
        }
        else{
            std::cout<<"std::vectors are different"<<std::endl;

        }

        Mat matrix = tab_to_matrix(result, input_dense);
        std::cout<<std::endl<<"Input : "<<std::endl<<verif;
        std::cout<<"Result : "<<std::endl<<matrix<<std::endl;
        std::cout<<"Verification : "<<std::endl<<input_dense<<std::endl;
        std::cout<<"Verification coefficient per coefficient..."<<std::endl;
        b = 0;
        for (int i = 0; i<matrix.rows; i++){
            for (int j=0; j<matrix.cols; j++){
                if (matrix.at<float>(i,j) != input_dense.at<float>(i,j)){
                    std::cout<<"Coefficients "<<i<<" "<<j<<" don't match"<<std::endl;
                    b=1;
                    goto exit2;
                }
            }
        }
        exit2:
        if(b == 0){
            std::cout<<"Matrices are the same"<<std::endl;
        }
        else{
            std::cout<<"Matrices are different"<<std::endl;
        }
    }
return 0;
}