#include "../include/class_image.hpp"


//function to test all the symmetries for an image already chosen
int main(){

//#######################################################################
//GET THE INPUTS
//####################################################################### 
    img fingerprint("../Project_Infra/images/weak_finger.png");

//#######################################################################
//SYMMETRIES
//####################################################################### 

    //symmetry wrt the diagonal y = -x
    img symd = fingerprint.sym_diag();

    //symmetry wrt x
    img symx = fingerprint.sym_x();
    
    //symmetry wrt y
    img symy = fingerprint.sym_y();

    //symmetry wrt the diagonal y = x
    img symd2 = fingerprint.sym_diag_inv();

    //save the images
    symd.save("verif_results/sym_diag.png");
    symx.save("verif_results/sym_x.png");
    symy.save("verif_results/sym_y.png");
    symd2.save("verif_results/sym_diag_inv.png");

return 0;
}