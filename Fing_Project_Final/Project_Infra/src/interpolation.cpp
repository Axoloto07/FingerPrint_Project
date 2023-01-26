#include "../include/interpolation.hpp"

img nearest_interpolation(img &image){
    //creation of the output image
    img res = img(Mat(image.get_matrix().rows, image.get_matrix().cols, image.get_matrix().type()));
    for (int i = 0; i<image.get_matrix().rows; i++){
        for (int j = 0; j<image.get_matrix().cols; j++){
            //filling the white slots that appeared due to geometrical operations using nearest neighbor interpolation method
            //filled by one of the surrounding pixels
            if(image.get_pix_val(i, j)==255 && (image.get_pix_val(i+1, j)!=255 || image.get_pix_val(i-1, j)!=255 || image.get_pix_val(i, j+1)!=255 || image.get_pix_val(i, j-1)!=255)){
                res.modif_pix( i , j , image.get_pix_val(i,j+1));
            }
            else {
                res.modif_pix( i , j , image.get_pix_val(i, j));
            }
        }
    }

    return res;

}


img bilinear_interpolation(img &image){
    //creation of the output image
    img res = img(Mat(image.get_matrix().rows, image.get_matrix().cols, image.get_matrix().type()));
    for (int i = 0; i<image.get_matrix().rows; i++){
        for (int j = 0; j<image.get_matrix().cols; j++){
            //filling the white slots that appeared due to geometrical operations using bilinear interpolation method
            //filled by the average of the surrounding pixels
            if(image.get_pix_val(i, j)==255 && (image.get_pix_val(i+1, j)!=255 || image.get_pix_val(i-1, j)!=255 || image.get_pix_val(i, j+1)!=255 || image.get_pix_val(i, j-1)!=255)){
                res.modif_pix( i , j ,(image.get_pix_val(i+1, j) + image.get_pix_val(i-1, j) + image.get_pix_val(i, j+1) + image.get_pix_val(i, j-1))/4 );
            }
            else {
                res.modif_pix( i , j , image.get_pix_val(i, j));
            }
        }
    }

    return res;

}