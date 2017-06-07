#Phods-algorithm-optimization
This is a repository regarding function time calculation and optimisation of phods algorithm,which is used in picture motion estimation.

The code for this repository was created for academic course "Design of Embedded Systems!"

The repository includes phods1.c which was a given code for the purposes of the assignment and will be optimised.All the codes have been configured to measure the execution time
of phods_estimation function with gettimeofday() function, as asked by the exercise.

phods2.c is the optimized version.
phods3.c is identical to phods2.c ,except that it is manipulated by Phods_script to run for spesific values of B,which is the size of
the image block, in which we process the image.All the possible values of B are the common divisors of M and N,where NxM are the dimensions of the image.

phods4.c is configured to take separately a value for Bx and By,where Bx and By are the dimensions of the block.All possible values of Bx are divisors of N and all possible values of By are divisors of M,respectively.

Phods_script is a bash script which is used as a tool for executing and configuring the above codes.With the appropriate argument,it runs phods1.c ,phods2.c , phods3.c for all possible values of B and phods4.c for all possible combinations of all possible values of Bx and By.

The above calculations concern images with 144x176 dimensions.
