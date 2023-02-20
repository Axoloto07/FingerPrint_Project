#include "../include/image.hpp"
#include "../include/geometrical_op.hpp"
#include "../include/interpolation.hpp"

int main(){
    std::cout<<"Please enter the name of the image. (ex : clean_finger.png)"<<std::endl;
    std::string path;
    std::cin>>path;
    img original("../Project_Infra/images/" + path);

    //applying rotation for the image
    img rotated = rotate(original,original.get_rows()/2,original.get_cols()/2,3.14/6);
    rotated.save("demo_results/rotation.png");

    //applying affine transformation for the image
    img transformed = transform(original,0.8,0.5,1.2,0.5,1.2,0.8);
    transformed.save("demo_results/transformation.png");
    
    //applying the nearest neighbor interpolation for affine translation
    img nearest_interpolated_affinetrans = nearest_interpolation(transformed);
    nearest_interpolated_affinetrans.save("demo_results/nearest_interpolated_affinetrans.png");
    
    //applying the bilinear interpolation for affine translation
    img bilinear_interpolated_affinetrans = bilinear_interpolation(transformed);
    bilinear_interpolated_affinetrans.save("demo_results/bilinear_interpolated_affinetrans.png");
    
    //applying the nearest neighbor interpolation for rotation
    img nearest_interpolated_rotation = nearest_interpolation(rotated);
    nearest_interpolated_rotation.save("demo_results/nearest_interpolated_rotation.png");
    
    //applying the bilinear interpolation for rotation
    img bilinear_interpolated_rotation = bilinear_interpolation(rotated);
    bilinear_interpolated_rotation.save("demo_results/bilinear_interpolated_rotation.png");
    
    //reversing the rotated image into its initial place
    img origin = rotate(rotated,original.get_rows()/2,original.get_cols()/2,-3.14/6);
    origin = nearest_interpolation(origin);
    origin.save("demo_results/reversedrot.png");

    // reversing the translated image into its initial place
    img origin1 = transform(bilinear_interpolated_affinetrans,1.7,-0.7,-1.4,-0.7,1.1,-0.05);
    origin1 = nearest_interpolation(origin1);
    origin1.save("demo_results/reversedtrans.png");

    return 0;
}