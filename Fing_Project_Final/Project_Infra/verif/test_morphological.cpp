#include <iostream>
// #include <opencv2/opencv.hpp>
#include "morphological.hpp"
#include "class_image.hpp"


#include <vector>
using namespace std;


//fonction to test the convolution 
void test_morphological(){

//------------get the input--------------------------------------
    img fingerprint("images/clean_finger.png");
    img tmp = fingerprint.cast_to_float();
    Mat m1 = tmp.get_matrix();
    vector<int> center = fingerprint.coord_center();

//---------------------------------------------------------------

//---------------binarisation-------------------------------------
    vector<float> proba = proba_distr(m1);
    //cout<<proba.size()<<endl;
    float threshold = find_threshold(proba);
    //cout<<threshold<<endl;
    Mat bin = binarization(m1,threshold);
    // convert_negative(test_bin);
    // img binaire = img(test_bin);
    // binaire.save("dry_binaire.png");
//---------------------------------------------------------------

//---------test of structural elements---------------------------
    Mat elt_structure = elt_struct_cross_col_row(3,3, "cross");
    //Mat elt_structure = elt_struct_square(3,3);
    //Mat elt_structure = elt_struct_disc(5,5);
    //Mat elt_structure = elt_struct_hole(5,5);
    //Mat elt_structure = (Mat_<float>(7,7,CV_32F)<<0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0);
    //cout<<elt_structure<<endl;

    //Mat elt_structure = elt_struct_diamond(7,7);

    //Mat elt_structure = elt_struct_diag(3,3, "diag");

    //Mat elt_structure_1 = elt_struct_square(3,3);
    //Mat elt_structure_1 = elt_struct_disc(3,3);
    //Mat elt_structure_1 = elt_struct_hole(3,3);
    //Mat elt_structure_1 = elt_struct_cross_col_row(5,5, "row");
    //Mat elt_structure_1 = elt_struct_diag(3,3, "diag");


    //Mat elt_structure_2 = elt_struct_hole(7,7);
    //Mat elt_structure_2 = (Mat_<float>(5,5,CV_32F)<<1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
   // Mat elt_structure_2 = elt_struct_diag(3,3, "diag_inv");
 
   // Mat elt_structure_3 = (Mat_<float>(5,5,CV_32F)<<0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1);
 
  // Mat elt_structure_4 = elt_struct_cross_col_row(5,5, "col");








    //cout<<elt_structure;
//----------------------------------------------------------------

    // // Mat input= (Mat_<float>(3,3,CV_32F)<<1,1,0,1,1,1,0,1,0);
    // // cout<<erosion_coeff(elt_structu, input)<<endl;

//------------erosion/dilatation with binary image-----------------------------------
    
    Mat result_ero_1 = erosion_dilatation(elt_structure, m1, "ero_gray");
    Mat result_ero = erosion_nunif(5,5,result_ero_1, 1.1*m1.cols/2, m1.cols);
  







    //convert_negative(result_ero);
    img test = img(result_ero);
    test.save("gray_essai.png");
    // //dilater plusieurs fois ou dilater eroder
    //col ou cross
    // Mat result_dil = erosion_dilatation(elt_structure,bin, "dil_bin", 0);
    // //Mat result_1 = erosion_dilatation(elt_structure,result_dil, "dil_bin", 0);
    // convert_negative(result_dil);
    // img test = img(result_dil);
    // test.save("dilatation_diamond.png");
//-----------------------------------------------------------------------------------

//-------------erosion/dilatation with grayscale image-------------------------------
    // Mat result = erosion_dilatation(elt_structure, m1, "ero_gray");
    // Mat result_2 = erosion_dilatation(elt_structure, result, "ero_gray");
    // img test = img(result_2);
    // test.save("erosion_grayscale.png");
    // Mat result_1 = erosion_dilatation(elt_structure, m1, "dil_gray");

    // test = img(result_1);
    // test.save("dilatation_grayscale.png");
//----------------------------------------------------------------------------------

//------------dilatation nunif with grayscale image-----------------------------------
 
    // float b = (float) 0.37*m1.cols;
    // float radius = 0.47*m1.rows;
    // Mat result = dilation_nunif(3, 3, 1.3*b, 0.95*b, radius, center, m1);
    // //convert_negative(result);

    // img test = img(result);
    // test.save("dilatation_nunif.png");

//-----------------------------------------------------------------------------------

//------------erosion nunif with grayscale image--------------------------------------

//-----------------------------------------------------------------------------------


    //Mat input= (Mat_<float>(6,7,CV_32F)<<1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,0);
    
    //erosion(elt_structure, input);
}