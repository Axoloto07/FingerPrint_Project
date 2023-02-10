
#include "../include/an_isotrop.hpp"
#include "../include/check_convergence.hpp"

//function to create the weak_finger 
int main(){

//#######################################################################
//GET THE INPUTS
//####################################################################### 

    std::cout<<"Please enter the name of the image. (ex : clean_finger.png)"<<std::endl;
    std::string path;
    std::cin>>path;
    img fingerprint("../Project_Infra/images/" + path);

    //choose the option to run
    bool iso;
    std::cout<<"Do you want the isotropic transformation? (enter 1 for yes, 0 for no)"<<std::endl;
    std::cin>>iso;
    bool aniso;
    std::cout<<"Do you want the anisotropic transformation? (enter 1 for yes, 0 for no)"<<std::endl;
    std::cin>>aniso;

//#######################################################################
//ISOTROPIC TRANSFORMATIONS
//#######################################################################

    if(iso){

        //isotropic transformation
        img resu = isotrop_transf(5, fingerprint);

        //save the result in a new image
        resu.save("demo_results/weak_finger_iso.png");

        //check convergence
        float threshold = 0.05;
        convergence("../Project_Infra/images/weak_finger.png","demo_results/weak_finger_iso.png",threshold);
    }

//#######################################################################
//ANISOTROPIC TRANSFORMATIONS
//#######################################################################

    if(aniso){
        //choice of the main direction of the transform
        float angle;
        std::cout<<"You have chosen the anisotropic transformation."<<std::endl;
        std::cout<<"What is the angle between the x-axis and the direction of high pressure? (in radian, ex : 0.785 for pi/4)"<<std::endl; 
        std::cout<<"If you have chosen clean_finger, the angle to enter is 0"<<std::endl;
        std::cout<<"If you have chosen warp1_finger, the angle to enter is -0.942 (-0.3 pi)"<<std::endl;
        std::cin>>angle;

        //anisotrop transformation
        img resu = anisotrop_transf(angle, fingerprint);

        //save the result in a new image
        resu.save("demo_results/weak_finger_aniso.png");

        //check convergence
        float threshold = 0.05;
        convergence("../Project_Infra/images/weak_finger.png","demo_results/weak_finger_aniso.png",threshold);
        mean_squared_error("../Project_Infra/images/weak_finger.png","demo_results/weak_finger_aniso.png");

    }
return 0;
}