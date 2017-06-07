# Phods-algorithm-optimization

This is a repository regarding function time calculation and optimisation of phods algorithm,which is used in picture motion estimation of 144x176 images.

The code for this repository was created for academic course "Design of Embedded Systems!"

The repository includes phods1.c which was a given code for the purposes of the assignment and was to be optimised.The techniques used for optimisation were loop unrolling, loop tiling, loop skewing, loop merging and loop interchanges wherever that was possible inside the critical section of the code.

All the codes have been configured to measure the execution time
of phods_estimation function with gettimeofday() function, as asked by the exercise.

phods2.c is the optimized version.
phods3.c is identical to phods2.c (therefore phods2.c does not need to be uploaded) ,except that it is manipulated by Phods_script.sh to run for spesific values of B,which is the size of the image block, in which we process the image.All the possible values of B are the common divisors of M and N,where NxM are the dimensions of the image.

phods4.c is configured to take separately a value for Bx and By,where Bx and By are the dimensions of the block.All possible values of Bx are divisors of N and all possible values of By are divisors of M,respectively.The goal is to find the optimal combination of Bx and By.

There is an extra part of the exercise, which is an extension of the 4th question.An heuristic, faster method is to be implemented, in order to find the optimal combination of Bx and By.The script asks for phods4b.c which is identical to phods4.c, therefore it is not uploaded as well.

Phods_script.sh is a bash script which is used as a tool for executing and configuring the above codes.With the appropriate argument,it runs phods1.c ,phods2.c , phods3.c for all possible values of B and phods4.c for all possible combinations of all possible values of Bx and By.
