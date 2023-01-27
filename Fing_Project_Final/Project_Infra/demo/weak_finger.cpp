
#include "../include/an_isotrop.hpp"
#include "../include/check_convergence.hpp"

//test the an/isotropic transformations of the fingerprint
//the result is saved in the image called : "isotropic_transf.png" and "anisotropic_transf.png"
int main(){
    //get the input image
    cout<<"Please enter the name of the image. (ex : clean_finger.png)"<<endl;
    string path;
    cin>>path;
    img fingerprint("../Project_Infra/images/" + path);
    //choose the option to run
    bool iso;
    cout<<"Do you want the isotropic transformation? (enter 1 for yes, 0 for no)"<<endl;
    cin>>iso;
    bool aniso;
    cout<<"Do you want the anisotropic transformation? (enter 1 for yes, 0 for no)"<<endl;
    cin>>aniso;

//#######################################################################
//ISOTROPIC TRANSFORMATIONS
//#######################################################################


    if(iso){

        //isotropic transformation
        img resu = isotrop_transf(5, fingerprint);
        resu.save("demo_results/weak_finger_iso.png");
        float threshold = 0.05;
        //check convergence
        convergence("../Project_Infra/images/weak_finger.png","demo_results/weak_finger_iso.png",threshold);
    }

//#######################################################################
//ANISOTROPIC TRANSFORMATIONS
//#######################################################################

    if(aniso){
        float angle;
        cout<<"You have chosen the anisotropic transformation."<<endl;
        cout<<"What is the angle between the x-axis and the direction of high pressure? (in radian, ex : 0.785 for pi/4)"<<endl; 
        cout<<"If you have chosen clean_finger, the angle to enter is 0"<<endl;
        cout<<"If you have chosen warp1_finger, the angle to enter is -0.942 (-0.3 pi)"<<endl;
        cin>>angle;
        //anisotrop transformation
        img resu = anisotrop_transf(angle, fingerprint);
        resu.save("demo_results/weak_finger_aniso.png");
        float threshold = 0.05;
        //check convergence
        convergence("../Project_Infra/images/weak_finger.png","demo_results/weak_finger_aniso.png",threshold);
        mean_squared_error("../Project_Infra/images/weak_finger.png","demo_results/weak_finger_aniso.png");

    }
return 0;
}