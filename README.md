#Parallel Computing

This repo contains the labs and projects associated with Parallel Computing 1 & 2.  Please note that this does not contain all files and programs created during this time period.  Other projects completed can be viewed within the syllabus.  All projects completed in this class were built in C++.  A sample syllabus can be viewed within this repository.

#Labs/Projects

While not all labs and projects from this class will be available, the following will be available for viewing:

  Ray Tracing
  Prefix sums
  Forest Fire
  Orbit Simulation
  
#Ray Tracing

Ray tracing is a ray tracing simulation that uses openMPI for optimization.  It implements Lamberts Law to determine the light intensity level to generate realistic shadows.

There are two versions of this program:  

    checkerboard generates a still of a ray traced image
    movie generates a series of images that can be combined into a gif to form a movie

#Movie Program

This program generates a series of images that simulates a movie.

  To run this program use the following commands:

    gcc movie.c -lm
    ./a.out

  This should generate a series of images.  Simply copy these images into a gif maker online to create your movie!
  
  This should produce a gif like the one below.
  
  ![Ray tracing image](https://raw.githubusercontent.com/z-ng/Parallel_Computing/main/ray_tracing/checkerboard/image.ppm)


 #Checkerboard
 
This program generates a ray traced still of three balls.

  To run this program use the following commands:
  
    gcc checkerboard.c -lm
    ./a.out
    display image.ppm
    
  This should produce a gif like the one below.

  ![Ray tracing image](https://raw.githubusercontent.com/z-ng/Parallel_Computing/main/ray_tracing/movie/movie.gif)
