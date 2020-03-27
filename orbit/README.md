# Orbit

Orbit is a program that simulates the movement of objects in space, most notably the Apollo spacecraft and international space station (ISS) as it orbits both the Earth and the moon.  It generates a visual representation of the orbit itself, the speed at which the orbit is occurring, and the distance from the Earth.  Different types of orbits can be applied, including a circular, an elliptical, and a hyperbollic orbit.  Also included are instructions on how to run the program in parallel on TJ's computer cluster infosphere.

There are two versions of this program:  

orbit_sim simualtes the movement of the ISS as it orbits the earth
free_return simualtes the movement of the Apollo spacecraft as it preforms a slingshot maneuver as it orbits the moonto return to earth

## Orbit Sim

This program simulates the movement of the ISS as it orbits the earth.  It generates an image that visualizes the orbit of the ISS, the distance from the earth, and the speed at which the orbit is occurring.  Different types of orbits can be applied, including a circular, an elliptical, and a hyperbollic orbit.

  To run this program use the following commands:

    gcc orbit.c -lm
    ./a.out
    gnuplot orbit.gnu
    display "IMAGE.PNG"

Please note that gnuplot must be installed for this program to work.

This should generate a text file that is the numerical representation of the orbit calculated by the program, as well as the visual representation presented in several images.  To view the images, simply run the command "display" with the name of the image file you which to view.
  
  This should produce a series of images similiar to the one below:

###### Orbit Graph

![Ray tracing image](https://raw.githubusercontent.com/z-ng/Parallel_Computing/main/orbit/orbit_sim/orbit.png)

###### Distance Graph

![Ray tracing image](https://raw.githubusercontent.com/z-ng/Parallel_Computing/main/orbit/orbit_sim/distance.png)

###### Speed Graph

![Ray tracing image](https://raw.githubusercontent.com/z-ng/Parallel_Computing/main/orbit/orbit_sim/speed.png)

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

![Ray tracing image](https://raw.githubusercontent.com/z-ng/Parallel_Computing/main/orbit/free_return/orbit.png)

###### Distance Graph

![Ray tracing image](https://raw.githubusercontent.com/z-ng/Parallel_Computing/main/orbit/free_return/distance.png)

###### Speed Graph

![Ray tracing image](https://raw.githubusercontent.com/z-ng/Parallel_Computing/main/orbit/free_return/speed.png)

