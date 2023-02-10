import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt

#img = cv.imread("/home/user/Documents/C++/FingerPrint_Project/Fing_Project_Final/build/demo_results/dry_finger_gray.png", cv.IMREAD_GRAYSCALE)
img = cv.imread("/home/user/Documents/C++/FingerPrint_Project/Fing_Project_Final/Project_Infra/images/clean_finger.png", cv.IMREAD_GRAYSCALE)
img2 = cv.imread("/home/user/Documents/C++/FingerPrint_Project/Fing_Project_Final/Project_Infra/images/moist_finger.png", cv.IMREAD_GRAYSCALE)

img1 = cv.imread("/home/user/Documents/C++/FingerPrint_Project/Fing_Project_Final/Project_Infra/images/dry_finger.png", cv.IMREAD_GRAYSCALE)
#img1 = cv.imread("/home/user/Documents/C++/FingerPrint_Project/Fing_Project_Final/build/demo_results/clean.png", cv.IMREAD_GRAYSCALE)

histr = cv.calcHist([img],[0],None,[256],[0,256])
histr1 = cv.calcHist([img1],[0],None,[256],[0,256])
histr2 = cv.calcHist([img2],[0],None,[256],[0,256])

A = np.zeros(256)
B = np.zeros(256)
C = np.zeros(256)


for i in range(256):
    A[i]=histr[i]
    B[i]=histr1[i]
    C[i]=histr2[i]

#print(A)
#print(histr)
plt.bar(range(256),B,1, color="green", label="Target image")

plt.bar(range(256),A,1, color="red", label="Our result")
plt.bar(range(256),C,1, color="yellow", label="Our result")


plt.xlabel("Gray levels")
plt.ylabel("Nb of pixels")

#plt.plot(histr, color = "red", label="Our result")
#plt.plot(histr1, color="green", label="target image")
plt.legend()
plt.xlim([-1,256])
plt.show()
