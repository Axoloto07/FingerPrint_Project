# FingerPrint_Project


Names : **LEBEURRIER Arthur, PERRIN Axel, TOURON Camille, TOURON Eloïse, MAZLOUM Hadi**.

# Before running the code : 

- from the terminal, go in the directory "build" (at the same level as "Project_Infra")
- in the terminal enter : "cmake ../Project_Infra/"


# To run the code : 

- Go in the directory build.
- Enter "make" in the terminal (the compilation is long)

Executable files : 
- the **final executables** are in the directory **"demo"**
they create final results such as "weak_finger".
- go in the directory "build" and enter "./demo/weak_finger" to execute the executable "weak_finger".
- the **images** created are in the directory **"demo_results"**.


- the **test executables** are in the directory **"verif"**
they create tests with images or results in the terminal.
- in some tests, you have to choose the code you want to run : 
enter "if(1)" instead of "if(0)".
- go in the directory "build" and enter "./verif/test_squares" to execute the executable "test_squares".
- the **images** are created in the directory **"verif_results"**.

# List of the created images in directory "demo_results":

- **blurred_finger_non_norm.png** : non normalized version of a blurred fingerprint (energy of the kernels slightly increases)
- **blurred_finger_norm.png** : normalized version of a blurred fingerprint (energy of the kernels is preserved)

- **clean.png** : clean acquisition obtained thanks to least squares resolution
- **corrupted.png** : blurred acquisition (size : 60 x 60) obtained thanks to matrix multiplication
- **corrupted_cut.png** : blurred acquisition obtained thanks to matrix multiplication and resize to 56 x 56
- **corrupted_verif.png** : blurred acquisition obtained with an already implemented method from OpenCV (size : 60 x 60), used to check the result of 'corrupted.png'

- **dry_binary.png** : binarized version of dry_finger (given image)
- **dry_finger_bin.png** : binarized version of a dry fingerprint obtained with non uniform morphological filtering
- **dry_finger_gray.png** : grayscale version of a dry fingerprint obtained with non uniform morphological filtering

- **moist_binary.png** : binarized version of moist_finger (given image)
- **moist_finger_bin.png** : binarized version of a moist fingerprint obtained with non uniform morphological filtering
- **moist_finger_gray.png** : grayscale version of a moist fingerprint obtained with non uniform morphological filtering

- **weak_finger_aniso.png** : weak fingerprint obtained after an anisotropic transformation
- **weak_finger_iso.png** : weak fingerprint obtained after an isotropic transformation

- for the **histograms** : the name of the file contains the names of the 2 input images. The white curve stands for the FIRST input image, and the gray one concerns the SECOND input image.
N.B : If only a gray curve appears, the 2 curves are actually overlapping.





