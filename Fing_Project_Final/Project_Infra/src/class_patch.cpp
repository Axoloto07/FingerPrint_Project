#include "../include/class_patch.hpp"

//----------------Constructors---------------------

patch::patch(img image, int size, int ci, int cj){
 // Sample a rectangle from the original image
    matrix = image.get_matrix()(Rect(cj-size/2, ci-size/2, size, size));

}


patch::patch(){
 // Creat a none matrix
    matrix = Mat();

}

patch::patch(int rows, int cols){
 // Create a rows*cols matrix object
    matrix = Mat(rows, cols, CV_8U);

}

patch::patch(std::map<std::pair<int,int>, int> mask, int ci, int cj, int size){
   
    matrix = Mat(size, size, CV_8U, Scalar(1));
    for (int i = 0; i<size; i++){
      for (int j = 0; j<size; j++){

         if (mask.count(std::make_pair(ci - size/2 + i, cj - size/2 + j)) == 1){

            matrix.at<uchar>(i, j) = 0;

         }

      }
    }

}



//----------------Distance---------------------

double patch::dist(patch p){

 // Initialize the distance to 0
    double dist=0.0;

 // Iteration on all the pixels of the patches
    for(int i=0; i<p.get_rows() ; i++){
        for(int j=0; j<p.get_cols() ; j++){

 // Perform the sum of the square difference of each pixels
            dist+= ((*this).get_pix_val(i, j)-p.get_pix_val(i,j))*((*this).get_pix_val(i, j)-p.get_pix_val(i,j));

        }
    }
 // Normalize the distance to have a result between 0 and 1
    dist=  dist/(double)(p.get_rows()*p.get_cols()*255*255);

 // Return the distance between the two patches
    return dist;

}



//----------------Arithmetic operations---------------------

patch patch::mult(patch p){

 // Creation of an empty patch were the result will be stored
    patch mult(p.get_rows(), p.get_cols());

 // Iteration on all the pixels of the patches
    for(int i = 0; i<(*this).get_cols(); i++){
        for(int j = 0; j<(*this).get_rows(); j++){

 // Perform the pixel by pixel multiplication
            mult.modif_pix(i, j, matrix.at<uchar>(i, j)*p.get_pix_val(i, j));

        }
    }

 // Return the result of the multiplication
    return mult;

}
