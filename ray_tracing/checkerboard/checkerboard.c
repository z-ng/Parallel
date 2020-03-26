#include <stdio.h>
#include <math.h> //include -lm flag during compile time

#define M 640
#define N 480
#define num_sphere 4

//
	int rgb[N][M][3] ; // red-green-blue for each direction

int main(void)
{
	int y , x, z ;
	FILE* fout ;
	z = 1.00;
	/*
	Spheres represents the coordinates of the spheres in the xyz plane
	Eye represents the coordinates of the eye in the xyz plane
	Light represents the coordinates of the light source from which the ray is being project in the xyz plane
	Radii represents the radius of the red, green, blue, and floor sphere respectively
	Note that the floor is a sphere for this program
	*/
	double spheres[4][3] = { {0, 0.75, 1.25}, {1.00, 0.5, 1.00},  {0.5, 0.5, 0.5}, {0.5, -20000.00, 0.5}};
	double eye[3] = { 0.50 , 0.50 , -1.00 };
	double light[3] = { 0.00, 1.25, -0.50 };
	double radii[4] = {0.5, 0.25, 0.25, 20000.25} ;

	for( y = 0 ; y < N ; y++ )  //eye to point
	{			
		/*runs the ray tracing in parallel*/				
		#pragma omp parallel for private(x,h)		

		for( x = 0 ; x < M ; x++)
		{
			int sphere_hit = 0;
			int floor_hit = 0;
			double direction[3];

			/*
			Formula for generating the direction of the ray assuming they are lines
			xo is starting point of the ray
			xd is the direction of the ray 
			t is the time
			xd * t represents how far we are going from the starting point
			X the ray's endpoint
			X = xo + xd*t
			Y = yo + yd*t
			Z = zo + zd*t
			*/
			//Note that this is calculating the direction in the frame where we are casting the ray (not a point a vector)
			
			direction[0] = (x+0.5)/480 - (1.0/6.0) - eye[0];
			direction[1] = (1 - ( y + .5) /480) - eye[1];
			direction[2] = 0 - eye[2];

			double mag = sqrt( direction[0]*direction[0] + direction[1]*direction[1] + direction[2]*direction[2] );
			
			/*normalizing the vector*/
			
			direction[0]/=mag;
			direction[1]/=mag;
			direction[2]/=mag;

			double t_final = 999999999999999;
			int final_color = -1;
			double B, C, t_x, t_y, t_tmp;

			/*Determines collision for sphere*/
			for(int color = 0; color < num_sphere; color++)
			{
				B = 2*(direction[0] * (eye[0] - spheres[color][0]) + direction[1] * (eye[1] - spheres[color][1]) + direction[2] * (eye[2] - spheres[color][2]));
				C = ( pow( (eye[0] - spheres[color][0]), 2 ) + pow( (eye[1] - spheres[color][1]) , 2 ) + pow( (eye[2] - spheres[color][2]) , 2 ) - pow( radii[color], 2 ));

				t_x = ( (-1*B) + (sqrt( pow( B, 2 ) - (4 * C) )) ) / ( 2 );
				t_y = ( (-1*B) - (sqrt( pow( B, 2 ) - (4 * C) )) ) / ( 2 );

				if( t_x > 0 && ( t_x <= t_y || t_y < 0 ) &&  t_x <= t_final )		
				{
					t_final = t_x;
					final_color = color;
				}
				else if(t_y > 0 && ( t_y <= t_x || t_x < 0) && t_y <= t_final)
				{
					t_final = t_y;
					final_color = color;
				}
			}

			if(final_color == -1)
			{
				sphere_hit = 1;
			}
			else if (final_color == 0)  
			{ 
				rgb[y][x][0] = 255;
			}
			else if (final_color == 1)  
			{ 
				rgb[y][x][1] = 255;
			}
			else if (final_color == 2)  
			{
				rgb[y][x][2] = 255;
			}
			else if (final_color == 3)  
			{
				rgb[y][x][0] = 205;  
				rgb[y][x][1] = 133; 
				rgb[y][x][2] = 66; 
				floor_hit = 1;
			} 
			
			/*Determines if in shadow*/
			
			if(sphere_hit == 0)
			{
				double point[3];
				
				/* calculates where the sphere is */

				point[0] = eye[0] + (direction[0]*t_final);  
				point[1] = eye[1] + (direction[1]*t_final);
				point[2] = eye[2] + (direction[2]*t_final);

				/* determines the direction of the ray */
				
				direction[0] = light[0] - point[0];		
				direction[1] = light[1] - point[1];
				direction[2] = light[2] - point[2];

				double mag = sqrt( pow(direction[0], 2) + pow(direction[1], 2) + pow(direction[2], 2) );

				/* Normalizing */

				direction[0]/=mag;
				direction[1]/=mag;
				direction[2]/=mag;
				int in_shadow = 0;
				
				if(floor_hit == 1)
				{
					
					double point_x = 0 + point[0];
					double point_z = 0 + point[2];
					
					/*
					To generate the checkerboard pattern, we add the two together, draw xz coordinates like a matrix ( -1 0 1 on top, -1 0 1 on the sides, add them then mod 2 to find pattern )
					*/
				
					if(( (int)floor(point[0]*10) + (int)floor(point[2]*10) ) % 2)  
					{
						rgb[y][x][0] = 178;
						rgb[y][x][1] = 255;
						rgb[y][x][2] = 255;
					}
					else
					{
						rgb[y][x][0] = 120;
						rgb[y][x][1] = 81;
						rgb[y][x][2] = 169;
					}
				}
				
				for(int sphere_num = 0; sphere_num < 3; sphere_num++)
				{
					B = 2*(direction[0] * (point[0] - spheres[sphere_num][0]) + direction[1] * (point[1] - spheres[sphere_num][1]) + direction[2] * (point[2]-spheres[sphere_num][2]));
					C = ( pow( (spheres[sphere_num][0] - point[0]), 2 ) + pow( (spheres[sphere_num][1] - point[1]) , 2 ) + pow( (spheres[sphere_num][2] - point[2]) , 2 ) - pow( radii[sphere_num], 2 ));
					
					t_x = ( (-1*B) + (sqrt( pow( B, 2 ) - (4 * C) )) ) / ( 2 );
					t_y = ( (-1*B) - (sqrt( pow( B, 2 ) - (4 * C) )) ) / ( 2 );
					
					if(t_x > 0.0001 || t_y > 0.0001)
					{
						rgb[y][x][0] /= 2;
						rgb[y][x][1] /= 2;
						rgb[y][x][2] /= 2;
						in_shadow = 1;
						break;
					}
				}

				/*
				we need to find the difference between the point on the sphere and the center of the sphere to find the normal
				we normalize it using by turning it into a unit vector
				we dot product it with the ray between the light and the sphere because the more normal a light ray, the higher the light intensity
				a dot product of 1 will signify normal, so the closer it is to 1 the less the shadows
				*/
				/*generating shadows*/

				if(in_shadow == 0)
				{					
					double point_center[3];
					double light_point[3];
					for(int count = 0; count < 3; count++)
					{
						point_center[count] = point[count] - spheres[final_color][count];
					}
					double mag = sqrt( pow(point_center[0], 2) + pow(point_center[1], 2) + pow(point_center[2], 2) );
					for(int count = 0; count < 3; count++)
					{
						point_center[count] /= mag;  //normalize
					}
					for(int count = 0; count < 3; count++)
					{
						light_point[count] = light[count] - point[count];
					}
					mag = sqrt( pow(light_point[0], 2) + pow(light_point[1], 2) + pow(light_point[2], 2) );
					for(int count = 0; count < 3; count++)
					{
						light_point[count] /= mag;  //normalize
					}
					double dot_product = ( point_center[0] * light_point[0] ) + ( point_center[1] * light_point[1] ) + ( point_center[2] * light_point[2] ) ;
					if(dot_product < 0)
					{
						dot_product = 0;
					}
					for(int count = 0; count < 3; count++)
					{	
						rgb[y][x][count] = ( rgb[y][x][count] / 2 ) + ( ( rgb[y][x][count] / 2 ) * dot_product );
					}
				}
			}
		}
	}

	/*generating image*/

	fout = fopen( "image.ppm" , "w" ) ;
	fprintf( fout , "P3\n" ) ;
	fprintf( fout , "%d %d\n" , M , N ) ;
	fprintf( fout , "255\n" ) ;
	
	for( y = 0 ; y < N ; y++ )
	{
		for( x = 0 ; x < M ; x++)
		{
			fprintf( fout , "%d %d %d\n" ,
			rgb[y][x][0] , rgb[y][x][1] , rgb[y][x][2] ) ;
		}
	}

	fclose( fout ) ;
	return 0 ;
}