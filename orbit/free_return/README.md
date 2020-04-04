## Free Return

This program simulates the movement of the Apollo spacecraft as it orbits the moon, slingshotting to return to Earth.  It generates an image that visualizes the orbit of the Apollo spacecraft, the distance from the earth, and the speed at which the orbit is occurring.  Different types of orbits can be applied, including a circular, an elliptical, and a hyperbollic orbit.  Also included are instructions on how to run the program in parallel on TJ's computer cluster infosphere.

  To run this program use the following commands:

    gcc freereturn.c -lm
    ./a.out
    gnuplot apollo.gnu
    display "IMAGE.PNG"

Please note that gnuplot must be installed for this program to work.

This should generate a text file that is the numerical representation of the orbit calculated by the program, as well as the visual representation presented in several images.  To view the images, simply run the command "display" with the name of the image file you which to view.
  
  This should produce a series of images similiar to the one below:

###### Orbit Graph

![Ray tracing image](https://raw.githubusercontent.com/zac-ng/Parallel_Computing/main/orbit/free_return/orbit.png)

###### Distance Graph

![Ray tracing image](https://raw.githubusercontent.com/zac-ng/Parallel_Computing/main/orbit/free_return/distance.png)

###### Speed Graph

![Ray tracing image](https://raw.githubusercontent.com/zac-ng/Parallel_Computing/main/orbit/free_return/speed.png)

