#include "../include/optimization.hpp"
#include "../include/geometrical_op.hpp"



int main(){

    img fingerprint("../Project_Infra/images/clean_finger_small.png");

    img fingerprint_tx("../Project_Infra/images/tx_finger.png");

    img fingerprint_big("../Project_Infra/images/clean_finger.png");

    img fingerprint_txy("../Project_Infra/images/txy_small_finger_homemade.png");

    img fingerprint_rtxy("../Project_Infra/images/rtxy_small_finger_homemade.png");

    int n = fingerprint.get_rows()/2;
    int m = fingerprint.get_cols()/2;
    int mb = fingerprint_big.get_cols();


//-----------------------1D translation--------------------------------------------

    std::cout << "1D translation: \n";
    find_min_x(fingerprint_big, fingerprint_tx);
    std::cout <<"\n";


//-----------------------2D translation--------------------------------------------

    std::cout << "2D translation: \n";
    find_min_xy(fingerprint, fingerprint_txy, -n, n, -m, m);
    std::cout<<"\n";


//-----------------------2D translation + rotation--------------------------------------------

    std::cout << "2D translation + rotation: \n";
    find_min_xytheta(fingerprint, fingerprint_rtxy, -n/4, n/4, -m/4, m/4, -0.3, 0.3);
    std::cout<<"\n";

    return 0;
}