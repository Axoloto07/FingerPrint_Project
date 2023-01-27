#include "../include/structuring_element.hpp"

//#######################################################################
//LIBRARY OF STRUCTURING ELEMENTS
//#######################################################################

Mat elt_struct_cross_col_row (int size_i, int size_j, string type){
    //create a structuring element with a central cross, or a single row or a single column

    Mat elt_struct = Mat::zeros(size_i,size_j,CV_32F);
    //in the case where the user wants a cross or a column
    if(type=="cross" || type=="col"){
        for (int i = 0; i<size_i; i++){
            elt_struct.at<float>(i, size_j/2) = 1;   
        }
    }
    //in the case where the user wants a cross or a row
    if(type=="cross" || type=="row"){
        for (int j = 0; j<size_j; j++){
            elt_struct.at<float>(size_i/2,j) = 1;
        }
    }
    return elt_struct;
}

Mat elt_struct_square (int size_i, int size_j){
    //create a squared structuring element

    return Mat::ones(size_i,size_j,CV_32F);
}

Mat elt_struct_disc (int size_i, int size_j){
    //create a disc-formed structuring element
    //dimensions should be odd and equal to have a circle (otherwise it is an ellipse)
    Mat elt_struct = Mat::zeros(size_i,size_j,CV_32F);
    for (int i=0; i<size_i; i++){
        for (int j=0; j<size_j; j++){
            //pixels inside a given circle have value 1, others are null
            if (pow((float)(i-size_i/2)/(size_i/2), 2) + pow((float)(j-size_j/2)/(size_j/2), 2) <=1){
                elt_struct.at<float>(i,j) = 1;
            }
        }
    }
    return elt_struct;

}

Mat elt_struct_id(int size_i, int size_j){
    //create an indentity structuring element with a single non null value
    Mat elt_struct = Mat::zeros(size_i,size_j,CV_32F);
    //the non null value is placed at the center of the kernel
    elt_struct.at<float>(size_i/2,size_j/2) = 1;
    return elt_struct;

}

Mat elt_struct_diamond (int size_i, int size_j){
    //create a diamond-formed structuring element
    //dimensions should be equal to have a well formed diamond
    Mat elt_struct = Mat::zeros(size_i,size_j,CV_32F);
    int pos = (size_j/2)/(size_i/2);
    int decal = 0;
    for (int i=0; i<size_i; i++){
        //at each row, the nb of pixels having value 1 decreases
        for (int j=size_j/2-decal; j<=size_j/2+decal; j++){ 
                elt_struct.at<float>(i,j) = 1;
            
        }

        if(i < size_i/2){
            decal +=pos;
        }
        else{
            decal-=pos;
        }
    }
    return elt_struct;
}

Mat elt_struct_diag(int size_i, int size_j, string position){
    //create a structuring element with a diagonal of ones
    //the dimensions should be equal
    Mat elt_struct = Mat::zeros(size_i,size_j,CV_32F);
    //create a diagonal coming from the top left corner to the bottom right corner
    if (position=="diag"){
        for (int i=0; i<size_i; i++){
            elt_struct.at<float>(i,i) = 1;      
        }
    }
    else{
    //create a diagonal coming from the top right corner to the bottom left corner
        for (int i=0; i<size_i; i++){
            elt_struct.at<float>(i,size_j-1-i) = 1;      
        }
    }
    return elt_struct;

}

Mat elt_struct_hole(int size_i, int size_j){
    //carre
    Mat elt_struct = Mat::zeros(size_i,size_j,CV_32F);
    // for (int i=0; i<size_i; i++){
    //         elt_struct.at<float>(i,i) = 1;      
    // }
    // for (int i=0; i<size_i; i++){
    //         elt_struct.at<float>(i,size_j-1-i) = 1;      
    // }
    // for (int i=0; i<size_i; i++){
    //             elt_struct.at<float>(i,0) = 1;      
    // }
    // for (int j=0; j<size_j; j++){
    //             elt_struct.at<float>(size_i/2,j) = 1;      
    // }
    elt_struct.at<float>(0,0) = 1;   
    // elt_struct.at<float>(0,1) = 1; 
    // elt_struct.at<float>(1,0) = 1;  
    // elt_struct.at<float>(1,1) = 1; 

    elt_struct.at<float>(0,size_j-1) = 1; 
    // elt_struct.at<float>(0,size_j-2) = 1;  
    // elt_struct.at<float>(1,size_j-1) = 1; 
    // elt_struct.at<float>(1,size_j-2) = 1;  

    elt_struct.at<float>(size_i-1,0) = 1; 
    // elt_struct.at<float>(size_i-2,0) = 1;  
    // elt_struct.at<float>(size_i-1,1) = 1;    
    // elt_struct.at<float>(size_i-2,1) = 1;      

    elt_struct.at<float>(size_i-1,size_j-1) = 1; 
    // elt_struct.at<float>(size_i-2,size_j-1) = 1; 
    // elt_struct.at<float>(size_i-1,size_j-2) = 1; 
    // elt_struct.at<float>(size_i-2,size_j-2) = 1;      
    return elt_struct;

}
