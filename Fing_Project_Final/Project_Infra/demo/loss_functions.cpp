#include "../include/optimization.hpp"
#include "../include/geometrical_op.hpp"



int main(){

    img fingerprint("../Project_Infra/images/clean_finger_small.png");

    img fingerprint_tx("../Project_Infra/images/tx_finger.png");

    img fingerprint_big("../Project_Infra/images/clean_finger.png");

    img fingerprint_txy("../Project_Infra/images/txy_small_finger_homemade.png");

    int n = fingerprint.get_rows()/2;
    int m = fingerprint.get_cols()/2;
    int mb = fingerprint_big.get_cols();
    

    std::cout << " Figure 45 : MSE loss function with respect to x \n";
    draw_loss_function_x(fingerprint_tx, fingerprint_big, -mb, mb, 10000, 0);
    std::cout <<"\n";

    std::cout << " Figure 47 : MSE loss function with respect to x and y\n";
    draw_loss_function_xy(fingerprint, fingerprint_txy, -m, m, -n, n, 100, 0); 
    std::cout <<"\n";

    std::cout << " Figure 49 : cross correlation loss function with respect to x \n";
    draw_loss_function_x(fingerprint_tx, fingerprint_big, -mb, mb, 300, 1);
    std::cout <<"\n";

    std::cout << " Figure 52 : MSE derivative loss function with respect to x \n";
    draw_loss_function_pderivative_x(fingerprint_tx, fingerprint_big, -mb, mb, 300, 0);
    std::cout <<"\n";

    return 0;
}