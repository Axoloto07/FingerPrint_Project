
#include "../include/an_isotrop.hpp"
#include "../include/check_convergence.hpp"

//test the an/isotropic transformations of the fingerprint

int main(){

    cout<<"PLEASE CHOOSE THE OPTION YOU WANT TO RUN : enter 'if(1)' instead of 'if(0)'"<<endl;

    img fingerprint("../Project_Infra/images/clean_finger.png");

//#######################################################################
//ISOTROPIC TRANSFORMATIONS
//#######################################################################


    if(0){

        //isotropic transformation
        img resu = isotrop_transf(5, fingerprint);
        resu.save("isotropic_transf.png");
        float threshold = 0.05;
        //check convergence
        convergence("../Project_Infra/images/weak_finger.png","isotropic_transf.png",threshold);

    }

//#######################################################################
//ANISOTROPIC TRANSFORMATIONS
//#######################################################################

    if(1){
        //anisotropic transformation without rotation
        img resu = anisotrop_transf(0, fingerprint);
        resu.save("anisotropic_transf_non_rotation.png");
        float threshold = 0.05;
        //check convergence
        convergence("../Project_Infra/images/weak_finger.png","anisotropic_transf_non_rotation.png",threshold);

    }

    if(1){
        //anisotropic transformation with rotation
        img fingerprint("../Project_Infra/images/warp1_finger.png");
        img resu = anisotrop_transf(-0.3*3.14, fingerprint);
        resu.save("anisotropic_transf_rotation.png");
    }
return 0;
}