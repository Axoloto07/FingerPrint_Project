
# set(SOURCES alglibinternal.cpp alglibmisc.cpp ap.cpp dataanalysis.cpp diffequations.cpp fasttransforms.cpp integration.cpp interpolation.cpp kernels_avx2.cpp kernels_fma.cpp kernels_sse2.cpp linalg.cpp optimization.cpp solvers.cpp specialfunctions.cpp statistics.cpp)
file(GLOB SOURCES ./*.cpp)
add_library (alg ${SOURCES})



