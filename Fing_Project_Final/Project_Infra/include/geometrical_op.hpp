#ifndef GEOMETRICAL_OP_HPP
#define GEOMETRICAL_OP_HPP

#include "image.hpp"

        /**
         * @brief perform a rotation
         * 
         * @param ci the i coordinate of the center of rotation
         * @param cj the j coordinate of the center of rotation
         * @param angle of rotation
         * @return img 
         */
        img rotate(img &image,int ci,int cj,float angle);


        /**
         * @brief perform an affine transformation
         * 
         * @param a0 
         * @param a1 
         * @param a2 
         * @param b0 
         * @param b1 
         * @param b2 
         * @return img 
         */
        img transform(img &image,float a0, float a1, float a2,float b0, float b1,float b2);


#endif