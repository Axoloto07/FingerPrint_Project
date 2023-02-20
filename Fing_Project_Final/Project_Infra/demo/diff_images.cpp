#include "../include/optimization.hpp"
#include "../include/geometrical_op.hpp"



int main(){

    img fingerprint = img("../../Project_Infra/images/clean_finger_small.png");

    img fingerprint_tx = img("../../Project_Infra/images/tx_finger.png");

    img fingerprint_big = img("../../Project_Infra/images/clean_finger.png");

    img fingerprint_txy = img("../../Project_Infra/images/txy_small_finger_homemade.png");

    img fingerprint_rtxy = img("../../Project_Infra/images/rtxy_small_finger_homemade.png");

    int n = fingerprint.get_rows()/2;
    int m = fingerprint.get_cols()/2;
    int mb = fingerprint_big.get_cols();


//-----------------------1D translation--------------------------------------------

    img diff_res = fingerprint_tx.difference(fingerprint_big.translation(-35,0));
    img diff = fingerprint_tx.difference(fingerprint_big.translation(0,0));

    diff_res.save("../../Project_Infra/demo_results/diff_res.png");
    diff.save("../../Project_Infra/demo_results/diff.png");


//-----------------------2D translation--------------------------------------------


    img diff_2d_res = fingerprint_txy.difference(fingerprint.translation(-10,14));
    img diff_2d = fingerprint_txy.difference(fingerprint.translation(0,0));

    diff_2d_res.save("../../Project_Infra/demo_results/diff_2d_res.png");
    diff_2d.save("../../Project_Infra/demo_results/diff_2d.png");


//-----------------------2D translation + rotation--------------------------------------------


    img diff_3d = fingerprint.difference(fingerprint_rtxy);

    img t = fingerprint;

    img r = rotate(t, t.coord_center()[0], t.coord_center()[1], -0.26);
    img diff_3d_res = (r.translation(-31.4,12.8)).difference(fingerprint_rtxy);

    diff_3d_res.save("../../Project_Infra/demo_results/diff_3d_res.png");
    diff_3d.save("../../Project_Infra/demo_results/diff_3d.png");







    return 0;
}