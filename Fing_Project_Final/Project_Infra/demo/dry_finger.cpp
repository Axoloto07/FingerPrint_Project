
#include "../include/morphological.hpp"
#include "../include/class_image.hpp"
#include "../include/check_convergence.hpp"


//fonction to create the dry finger
int main(){

//#######################################################################
//GET THE INPUTS
//####################################################################### 

    cout<<"Please enter the name of the image. (ex : clean_finger.png)"<<endl;
    string path;
    cin>>path;
    img fingerprint("../Project_Infra/images/" + path);
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

//#######################################################################
//NON UNIFORM EROSION WITH BINARY IMAGES
//####################################################################### 

    if(bin){

        //binarization of the clean finger
        vector<float> proba = proba_distr(m1);
        float threshold = find_threshold(proba);
        Mat binary = binarization(m1,threshold);

        //binarization of the dry finger
        img fingerprint("../Project_Infra/images/dry_finger.png");
        img tmp = fingerprint.cast_to_float();
        Mat m2 = tmp.get_matrix();
        proba = proba_distr(m2);
        threshold = find_threshold(proba);
        Mat binary_dry = binarization(m2,threshold);
        convert_negative(binary_dry);
        //save the image
        img verif = img(binary_dry);
        verif.save("demo_results/dry_binary.png");

        //apply the non uniform erosion to the binarized 'clean_finger'
        Mat result_ero = erosion_nunif_bin(5,5,binary, 0.45*m1.cols, 3.0/4*m1.cols, center,0.1*m1.rows);
        convert_negative(result_ero);

        //save the result in a new image
        img test = img(result_ero);
        test.save("demo_results/dry_finger_bin.png");

        //compare binarized 'dry_finger' with binarized eroded output
        convergence("demo_results/dry_binary.png","demo_results/dry_finger_bin.png",0.05);
        mean_squared_error("demo_results/dry_binary.png","demo_results/dry_finger_bin.png");


    }

//#######################################################################
//NON UNIFORM EROSION WITH GRAYSCALE IMAGES
//####################################################################### 

    if (gray){

        //apply the non uniform erosion 
        Mat result_ero = erosion_nunif(5,5,m1, m1.cols/2, m1.cols, center,0.1*m1.rows);

        //save the result in a new image
        img test = img(result_ero);
        test.save("demo_results/dry_finger_gray.png");

        //compare 'dry_finger' with eroded output
        convergence("../Project_Infra/images/dry_finger.png","demo_results/dry_finger_gray.png",0.05);
        mean_squared_error("../Project_Infra/images/dry_finger.png","demo_results/dry_finger_gray.png");
        
    }
return 0;
}