
#include "../include/morphological.hpp"
#include "../include/image.hpp"
#include "../include/check_convergence.hpp"


//fonction to create the moist finger
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
    float b = (float) 0.37*m1.cols;
    float radius = 0.47*m1.rows;

    //choose the option to run
    bool bin;
    cout<<"Do you want the binary version? (enter 1 for yes, 0 for no)"<<endl;
    cin>>bin;
    bool gray;
    cout<<"Do you want the grayscale version? (enter 1 for yes, 0 for no)"<<endl;
    cin>>gray;

//#######################################################################
//NON UNIFORM DILATION WITH BINARY IMAGES
//####################################################################### 

    if(bin){
        //binarization of the clean finger
        vector<float> proba = proba_distr(m1);
        float threshold = find_threshold(proba);
        Mat binary = binarization(m1,threshold);

        //binarization of the moist finger
        img fingerprint("../Project_Infra/images/moist_finger.png");
        img tmp = fingerprint.cast_to_float();
        Mat m2 = tmp.get_matrix();
        proba = proba_distr(m2);
        threshold = find_threshold(proba);
        Mat binary_moist = binarization(m2,threshold);
        convert_negative(binary_moist);
        //save the image
        img verif = img(binary_moist);
        verif.save("demo_results/moist_binary.png");

        //apply the non uniform dilation to the binarized 'clean_finger'
        Mat result_bin = dilation_nunif(3, 3, 1.3*b, 0.95*b, radius, center, binary, "bin");
        convert_negative(result_bin);

        //save the result in a new image
        img test = img(result_bin);
        test.save("demo_results/moist_finger_bin.png");

        //compare binarized 'moist_finger' with binarized dilated output
        convergence("demo_results/moist_binary.png","demo_results/moist_finger_bin.png",0.05);
        mean_squared_error("demo_results/moist_binary.png","demo_results/moist_finger_bin.png");


    }

//#######################################################################
//NON UNIFORM DILATION WITH GRAYSCALE IMAGES
//####################################################################### 
    
    if (gray){ 
        //apply the non uniform dilation
        Mat result_gray = dilation_nunif(3, 3, 1.3*b, 0.95*b, radius, center, m1, "gray");
        
        //save the result in a new image
        img test = img(result_gray);
        test.save("demo_results/moist_finger_gray.png");

        //compare 'moist_finger' with dilated output
        convergence("../Project_Infra/images/moist_finger.png","demo_results/moist_finger_gray.png",0.05);
        mean_squared_error("../Project_Infra/images/moist_finger.png","demo_results/moist_finger_gray.png");
        histogram("../Project_Infra/images/moist_finger.png", "demo_results/moist_finger_gray.png", "demo_results");

    }
return 0;
}