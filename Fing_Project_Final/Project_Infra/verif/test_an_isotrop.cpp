
#include "../include/an_isotrop.hpp"
#include "../include/check_convergence.hpp"

//test the an/isotropic transformations of the fingerprint
int main(){

    std::cout<<"PLEASE CHOOSE THE OPTION YOU WANT TO RUN : enter 'if(1)' instead of 'if(0)'"<<std::endl;

    img fingerprint("../Project_Infra/images/clean_finger.png");

//#######################################################################
//ISOTROPIC TRANSFORMATIONS
//#######################################################################


    if(1){

        //isotropic transformation
        img resu = isotrop_transf(5, fingerprint);
        resu.save("verif_results/isotropic_transf.png");

        //check convergence
        float threshold = 0.05;
        convergence("../Project_Infra/images/weak_finger.png","verif_results/isotropic_transf.png",threshold);

    }

//#######################################################################
//ANISOTROPIC TRANSFORMATIONS
//#######################################################################

    if(1){
        //anisotropic transformation without rotation
        img resu = anisotrop_transf(0, fingerprint);
        resu.save("verif_results/anisotropic_transf_non_rotation.png");

        //check convergence
        float threshold = 0.05;
        convergence("../Project_Infra/images/weak_finger.png","verif_results/anisotropic_transf_non_rotation.png",threshold);

    }

    if(1){
        //anisotropic transformation with rotation
        img fingerprint("../Project_Infra/images/warp1_finger.png");
        img resu = anisotrop_transf(-0.3*3.14, fingerprint);
        resu.save("verif_results/anisotropic_transf_rotation.png");
    }
return 0;
}