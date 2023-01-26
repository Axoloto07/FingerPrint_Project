
#include "../include/morphological.hpp"
#include "../include/class_image.hpp"
#include "../include/check_convergence.hpp"


//fonction to create the moist finger
void dry_finger(){

//------------get the input--------------------------------------
    //get the input image
    cout<<"Please enter the full path of the image. (ex : images/clean_finger.png)"<<endl;
    string path;
    cin>>path;
    img fingerprint(path);
    img tmp = fingerprint.cast_to_float();
    Mat m1 = tmp.get_matrix();
    vector<int> center = fingerprint.coord_center();


    //choose the option to run
    bool bin;
    cout<<"Do you want the binary version? (enter 1 for yes, 0 for no)"<<endl;
    cin>>bin;
    bool gray;
    cout<<"Do you want the grayscale version? (enter 1 for yes, 0 for no)"<<endl;
    cin>>gray;


//---------------------------------------------------------------

//---------Creation of the structural element--------------------
    //Mat elt_structure = elt_struct_cross_col_row(3,3, "cross");
//---------------------------------------------------------------

//------------erosion nunif with binary image--------------

    if(bin){
        //binarisation of the clean finger
        vector<float> proba = proba_distr(m1);
        float threshold = find_threshold(proba);
        Mat binary = binarization(m1,threshold);

        //binarisation of the moist finger
        img fingerprint("images/dry_finger.png");
        img tmp = fingerprint.cast_to_float();
        Mat m2 = tmp.get_matrix();
        proba = proba_distr(m2);
        threshold = find_threshold(proba);
        Mat binary_dry = binarization(m2,threshold);
        convert_negative(binary_dry);
        img verif = img(binary_dry);
        verif.save("dry_binary.png");

        //apply the dilation
        //Mat result_ero_1 = erosion_dilatation(elt_structure, binary, "ero_bin");
        // Mat result_ero = erosion_nunif(5,5,result_ero_1, 1.1*m1.cols/2, m1.cols, "bin");
        Mat result_ero = erosion_nunif(5,5,binary, m1.cols/2, m1.cols, center,0.1*m1.rows,  "gray");
        convert_negative(result_ero);
        img test = img(result_ero);
        test.save("dry_finger_bin.png");

        //convergence
        convergence("dry_binary.png","dry_finger_bin.png",0.05);


    }
//---------------------------------------------------------------

//------------erosion nunif with grayscale image--------------
    
    if (gray){ 
        //Mat result_ero_1 = erosion_dilatation(elt_structure, m1, "ero_gray");
        //Mat result_ero = erosion_nunif(5,5,result_ero_1, 1.1*m1.cols/2, m1.cols, "gray");
        Mat result_ero = erosion_nunif(5,5,m1, m1.cols/2, m1.cols, center,0.1*m1.rows,  "gray");
        img test = img(result_ero);
        test.save("dry_finger_gray.png");

        //convergence
        convergence("images/dry_finger.png","dry_finger_gray.png",0.05);
    }
    
        
//-----------------------------------------------------------------------------------

}