#include "../include/morphological.hpp"
#include "../include/image.hpp"



//fonction to test the morphological filtering
int main(){
    std::cout<<"PLEASE CHOOSE THE OPTION YOU WANT TO RUN : enter 'if(1)' instead of 'if(0)'"<<std::endl;

//#######################################################################
//GET THE INPUTS
//#######################################################################  

    img fingerprint("../Project_Infra/images/clean_finger.png");
    img tmp = fingerprint.cast_to_float();
    Mat m1 = tmp.get_matrix();
    std::vector<int> center = fingerprint.coord_center();
    Mat elt_structure;
    Mat result;
    img test;

//#######################################################################
//BINARISATION OF THE INPUT
//#######################################################################

    std::vector<float> proba = proba_distr(m1);
    float threshold = find_threshold(proba);
    Mat bin = binarization(m1,threshold);

//#######################################################################
//DILATION WITH BINARY IMAGE
//#######################################################################

    if (1){
        //uniform dilation with a cross motif
        elt_structure = elt_struct_cross_col_row(3,3, "cross");
        result = erosion_dilatation(elt_structure, bin,"dil_bin");
        convert_negative(result);

        //save the result in a new image
        test = img(result);
        test.save("verif_results/dilation_bin_cross.png");
    }

//#######################################################################
//DILATION WITH GRAY SCALE IMAGE
//#######################################################################

    if (1){
        //uniform dilation with a motif 'column'
        elt_structure = elt_struct_cross_col_row(3,3, "col");
        result = erosion_dilatation(elt_structure, m1,"dil_gray");

        //save the result in a new image
        test = img(result);
        test.save("verif_results/dilation_gray_col.png");
    }

//#######################################################################
//EROSION WITH BINARY IMAGE
//#######################################################################

    if (1){
        //uniform dilation with a disc motif
        elt_structure = elt_struct_disc(5,5);
        result = erosion_dilatation(elt_structure, bin,"ero_bin");
        convert_negative(result);

        //save the result in a new image
        test = img(result);
        test.save("verif_results/erosion_bin_disc.png");
    }

//#######################################################################
//EROSION WITH GRAY SCALE IMAGE
//#######################################################################

    if (1){
        //uniform dilation with a diamond motif
        elt_structure = elt_struct_diamond(5,5);
        result = erosion_dilatation(elt_structure, m1,"ero_gray");

        //save the result in a new image
        test = img(result);
        test.save("verif_results/erosion_gray_diamond.png");
    }

//#######################################################################
//EROSION/DILATION VS DILATION/EROSION
//#######################################################################

    if (1){
        //opening with a square motif
        elt_structure = elt_struct_square(3,3);
        result = erosion_dilatation(elt_structure, m1,"ero_gray");
        result = erosion_dilatation(elt_structure, result, "dil_gray");

        //save the result in a new image
        test = img(result);
        test.save("verif_results/erosion_dilation.png");

        //closing with a square motif
        result = erosion_dilatation(elt_structure, m1,"dil_gray");
        result = erosion_dilatation(elt_structure, result, "ero_gray");

        //save the result in a new image
        test = img(result);
        test.save("verif_results/dilation_erosion.png");
    }

return 0;
}