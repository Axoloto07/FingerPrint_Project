#include <iostream>
#include "../include/deconvolution.hpp"
#include "../include/check_convergence.hpp"

//function to test some tools for the deconvolution
int main(){
    
    cout<<"PLEASE CHOOSE THE OPTION YOU WANT TO RUN : enter 'if(1)' instead of 'if(0)'"<<endl;
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

        cout<<endl<<"Test of matrix of convolution : "<<endl;
        cout<<"Verification coefficient per coefficient..."<<endl;
        vector<Mat> v = list_circulante(kernel, input_dense);
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
                    cout<<"Coefficients "<<i<<" "<<j<<" don't match"<<endl;
                    b=1;
                    goto exit;
                }
            }
        }
        exit:
        if(b == 0){
            cout<<"Matrices are the same"<<endl;
        }
        else{
            cout<<"Matrices are different"<<endl;

        }

    }
//#######################################################################
//VERIFICATION OF THE SPARSE MATRIX CONSTRUCTION
//#######################################################################
    
    if(1){
        cout<<endl<<"Test of sparse matrix : "<<endl;
        sparsematrix m1 = matrix_to_sparse(input_dense, 2);
        cout<<"Dense matrix : "<<endl;
        cout<<input_dense<<endl;
        cout<<"Sparse matrix : "<<endl;
        print_sparse(m1);
    }


    if(1){
        cout<<endl<<"Test of vectorisation/matricisation : "<<endl;
        cout<<"Input : "<<endl<<input_dense<<endl;
        real_1d_array result = matrix_to_vector_dense(input_dense, 5);
        real_1d_array verif = "[1, 2, 3, 5, 5, 9, 6, 5, 9]";
        cout<<"Result : "<<result;
        cout<<"Verification : "<<verif;
        cout<<"Verification coefficient per coefficient..."<<endl;
        int b=0;
        for (int i = 0; i<verif.length(); i++){
            if (verif[i] != result[i]){
                    cout<<"Coefficients "<<i<<" don't match"<<endl;
                    b=1;
                    goto exit1;
            }

        }
        exit1:
        if(b == 0){
            cout<<"Vectors are the same"<<endl;
        }
        else{
            cout<<"Vectors are different"<<endl;

        }

        Mat matrix = tab_to_matrix(result, input_dense);
        cout<<endl<<"Input : "<<endl<<verif;
        cout<<"Result : "<<endl<<matrix<<endl;
        cout<<"Verification : "<<endl<<input_dense<<endl;
        cout<<"Verification coefficient per coefficient..."<<endl;
        b = 0;
        for (int i = 0; i<matrix.rows; i++){
            for (int j=0; j<matrix.cols; j++){
                if (matrix.at<float>(i,j) != input_dense.at<float>(i,j)){
                    cout<<"Coefficients "<<i<<" "<<j<<" don't match"<<endl;
                    b=1;
                    goto exit2;
                }
            }
        }
        exit2:
        if(b == 0){
            cout<<"Matrices are the same"<<endl;
        }
        else{
            cout<<"Matrices are different"<<endl;
        }
    }
return 0;
}