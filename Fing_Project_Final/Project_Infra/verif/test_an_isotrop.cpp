#include <iostream>

using namespace std;

#include "class_image.hpp"
#include "check_convergence.hpp"

//test the anisotrop transformation of the fingerprint
//the result is save in the image called : "test_anisotrop.png"
void test_an_isotrop(){
    img fingerprint("images/clean_finger.png");
    //img fingerprint("images/warp1_finger.png");

//#######################################################################
//ISOTROPIC TRANSFORMATIONS
//#######################################################################


    if(1){

        //isotropic transformation
        img resu = fingerprint.isotrop_transf(5);
        resu.save("isotropic_transf.png");
        float threshold = 0.05;
        //check convergence
        convergence("images/weak_finger.png","isotropic_transf.png",threshold);

    }

//#######################################################################
//ANISOTROPIC TRANSFORMATIONS
//#######################################################################

    if(1){
        //anisotrop transformation
        img resu = fingerprint.anisotrop_transf(3.14/4);
        resu.save("anisotropic_transf.png");
        float threshold = 0.05;
        //check convergence
        convergence("images/weak_finger.png","anisotropic_transf.png",threshold);

    }
    if (0){
        img resu = fingerprint.anisotrop_transf_1();
        resu.save("essai.png");
    }

}