#include "../include/morphological.hpp"
#include "../include/class_image.hpp"



//fonction to test the morphological filtering
int main(){
    cout<<"PLEASE CHOOSE THE OPTION YOU WANT TO RUN : enter 'if(1)' instead of 'if(0)'"<<endl;

//#######################################################################
//GET THE INPUTS
//#######################################################################  

    img fingerprint("../Project_Infra/images/clean_finger.png");
    img tmp = fingerprint.cast_to_float();
    Mat m1 = tmp.get_matrix();
    vector<int> center = fingerprint.coord_center();
    Mat elt_structure;
    Mat result;
    img test;

//#######################################################################
//BINARISATION OF THE INPUT
//#######################################################################

    vector<float> proba = proba_distr(m1);
    float threshold = find_threshold(proba);
    Mat bin = binarization(m1,threshold);


//#######################################################################
//DILATION WITH BINARY IMAGE
//#######################################################################

    if (1){
        elt_structure = elt_struct_cross_col_row(3,3, "cross");
        result = erosion_dilatation(elt_structure, bin,"dil_bin");
        convert_negative(result);
        test = img(result);
        test.save("verif_results/dilation_bin_cross.png");
    }

//#######################################################################
//DILATION WITH GRAY SCALE IMAGE
//#######################################################################

    if (1){
        elt_structure = elt_struct_cross_col_row(3,3, "col");
        result = erosion_dilatation(elt_structure, m1,"dil_gray");
        test = img(result);
        test.save("verif_results/dilation_gray_col.png");
    }

//#######################################################################
//EROSION WITH BINARY IMAGE
//#######################################################################

    if (1){
        elt_structure = elt_struct_disc(5,5);
        result = erosion_dilatation(elt_structure, bin,"ero_bin");
        convert_negative(result);
        test = img(result);
        test.save("verif_results/erosion_bin_disc.png");
    }

//#######################################################################
//EROSION WITH GRAY SCALE IMAGE
//#######################################################################

    if (1){
        elt_structure = elt_struct_diamond(5,5);
        result = erosion_dilatation(elt_structure, m1,"ero_gray");
        test = img(result);
        test.save("verif_results/erosion_gray_diamond.png");
    }

//#######################################################################
//EROSION/DILATION VS DILATION/EROSION
//#######################################################################

    if (1){
        elt_structure = elt_struct_square(3,3);
        result = erosion_dilatation(elt_structure, m1,"ero_gray");
        result = erosion_dilatation(elt_structure, result, "dil_gray");
        test = img(result);
        test.save("verif_results/erosion_dilation.png");
        result = erosion_dilatation(elt_structure, m1,"dil_gray");
        result = erosion_dilatation(elt_structure, result, "ero_gray");
        test = img(result);
        test.save("verif_results/dilation_erosion.png");
    }


//------------current tries-----------------------------------
    
    // Mat result_ero = erosion_nunif(5,5,m1, m1.cols/2, m1.cols, center,0.1*m1.rows,  "gray");
    // test = img(result_ero);
    // test.save("ero_essai.png");

//-----------------------------------------------------------------------------------

return 0;
}