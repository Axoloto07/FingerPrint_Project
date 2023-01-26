#include "../include/geometrical_op.hpp"

img rotate(img &image,int ci,int cj,float angle){
    //creation of the output image
    img rot = img(Mat(image.get_matrix().rows, image.get_matrix().cols, image.get_matrix().type(),Scalar(255)));
    for (int i = 0; i<image.get_matrix().rows; i++){
        for (int j = 0; j<image.get_matrix().cols; j++){
            //creating the coordinates for the rotated image
            float ir = (i-ci) * cos(angle)-(j-cj)*sin(angle)+ci;
            float jr = (i-ci) * sin(angle)+(j-cj)*cos(angle) + cj;
            //filling the new coordinates by the appropriate pixels from the original image
            if(ir<image.get_matrix().rows && jr<image.get_matrix().cols && ir>0 && jr>0){
                rot.modif_pix( (int)ir, (int)jr , image.get_pix_val(i, j));

            }
        }
    }

    return rot;

}

img transform(img &image,float a0, float a1, float a2,float b0, float b1,float b2){
    //creation of the output image
    img trans = img(Mat(image.get_matrix().rows, image.get_matrix().cols, image.get_matrix().type(),Scalar(255)));
    for (int i = 0; i<image.get_matrix().rows; i++){
        for (int j = 0; j<image.get_matrix().cols; j++){
            //creating the coordinates for the transformed image
            float ir = a0*i + a1*j + a2 ;
            float jr = b0*i + b1*j + b2 ;
            //filling the new coordinates by the appropriate pixels from the original image
            if(ir<image.get_matrix().rows && jr<image.get_matrix().cols && ir>0 && jr>0){
                trans.modif_pix( (int)ir, (int)jr , image.get_pix_val(i, j));

            }
        }
    }

    return trans;

}