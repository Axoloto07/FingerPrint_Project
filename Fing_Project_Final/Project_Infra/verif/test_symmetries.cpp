#include "class_image.hpp"


//function to test all the symmetries for an image already chosen
void test_symmetries(){
    img fingerprint("images/weak_finger_small.png");
    //symmetry wrt the diagonal y = -x
    img symd = fingerprint.sym_diag();

    //symmetry wrt x
    img symx = fingerprint.sym_x();
    
    //symmetry wrt y
    img symy = fingerprint.sym_y();

    //symmetry wrt the diagonal y = x
    img symd2 = fingerprint.sym_diag_inv();

    symd.save("sym_diag.png");
    symx.save("sym_x.png");
    symy.save("sym_y.png");
    symd2.save("sym_diag_inv.png");


}