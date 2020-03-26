This is a ray tracing program created in my Parallel Computing class.

This program attempts to simulate ray tracing in a virtual, 2-d enviroment.  
It was built in c++, and utilizes openMPI for parallelization.

There are two versions of this program:  

    checkerboard generates a still of a ray traced image
    movie generates a series of images that can be combined into a gif to form a movie

Movie Program

This program generates a series of images that simulates a movie.

    To run this program run the following commands:

        gcc movie.c -lm
        ./a.out

    This should generate a series of images.  Simply copy these images into a gif maker online to create your movie!