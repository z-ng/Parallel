#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//
// https://physics.nist.gov/cgi-bin/cuu/Value?bg
//
#define G 6.674e-11 // (m^3)(kg^-1)(s^-2)
//
// https://ssd.jpl.nasa.gov/?planet_phys_par
//
#define M 5.972e+24 // kg
#define R 6.371e+6  // m
//
// parameters
//
#define DT 0.25     // s
//
int main()
{
	//
	// time intervals - duration is 90 minutes
	//
	int n = (int)( 0.5 + ( 100 * 60 * 60 ) / DT ) ; //1.5 is 1.5 hours (1.5 * 60 *60) replace 1.5
	//
	//////////////////////////////////////////////////
	//
	double*  t_moon = malloc(n * sizeof(double));
	double*  x_moon = malloc(n * sizeof(double));
	double*  y_moon = malloc(n * sizeof(double));
	double* vx_moon = malloc(n * sizeof(double));
	double* vy_moon = malloc(n * sizeof(double));
	//
	double*  t_apollo = malloc(n * sizeof(double));
	double*  x_apollo = malloc(n * sizeof(double));
	double*  y_apollo = malloc(n * sizeof(double));
	double* vx_apollo = malloc(n * sizeof(double));
	double* vy_apollo = malloc(n * sizeof(double));
	//////////////////////////////////////////////////
	//
	FILE* fout   ;
	//
	int j        ;
	//
	double r_moon , a_moon , r_moon_apollo, a_moon_apollo, r_earth_apollo, a_earth_apollo;
	//
	// double m = 28801.0 ; // kg - Apollo 11
	double m = 419725.0 ; // kg - ISS
	double m_moon = 7.34767309e+22;
	//
	//////////////////////////////////////////////////
	//
	// International Space Station
	//
	// https://www.nasa.gov/sites/default/files/atoms/files/np-2015-05-022-jsc-iss-guide-2015-update-111015-508c.pdf
	//
	// Page 54 - altitude : 370 km to 460 km
	// Page 54 - speed    : 28,000 km per hour
	//
	double theta = 27.0/180 * M_PI;
	
	t_moon[0]  = 0.0          ; //original is 0.0
	x_moon[0]  = R + 384400000          ; //original is 0.0
	y_moon[0]  = 0 ; //original is R + 400000.0
	vx_moon[0] = 0     ; // change for more elliptical - and change duration //7777.77 is the original	
	vy_moon[0] = 1000.0       ; // original is 0
	
        t_apollo[0]  = 0         ; //original is 0.0
	x_apollo[0]  = (R+202751774.4) * cos(theta)         ; //original is 0.0
	y_apollo[0]  = (R+202751774.4) * sin(theta) ; //original is R + 400000.0
	vx_apollo[0] = 1527.048 * cos(theta)     ; // change for more elliptical - and change duration //7777.77 is the original	
	vy_apollo[0] = 1527.048 * sin(theta)       ; // original is 0
	//
	// hyperbolic changes both initial (x,y) and (vx,vy) - compare to circular
	//
	//////////////////////////////////////////////////
	//
	for( j = 1 ; j < n ; j ++ )
	{
                //earth on moon
		t_moon[j] = t_moon[j-1] + DT           ;
		x_moon[j] = x_moon[j-1] + DT * vx_moon[j-1] ;
		y_moon[j] = y_moon[j-1] + DT * vy_moon[j-1] ;
		//
		r_moon = sqrt( x_moon[j-1]*x_moon[j-1] + y_moon[j-1]*y_moon[j-1] ) ;
		//
		a_moon = G * M / ( r_moon * r_moon ) ;
		//
		vx_moon[j] = vx_moon[j-1] - a_moon * ( x_moon[j-1] / r_moon ) * DT ;
		vy_moon[j] = vy_moon[j-1] - a_moon * ( y_moon[j-1] / r_moon ) * DT ;
                
                //earth on apollo
                t_apollo[j] = t_apollo[j-1] + DT           ;
		x_apollo[j] = x_apollo[j-1] + DT * vx_apollo[j-1] ;
		y_apollo[j] = y_apollo[j-1] + DT * vy_apollo[j-1] ;
		//
		r_earth_apollo = sqrt( (x_apollo[j-1]*x_apollo[j-1]) + ( y_apollo[j-1]*y_apollo[j-1] )) ;
		//
		a_earth_apollo = G * M / ( r_earth_apollo * r_earth_apollo ) ;
		//
		vx_apollo[j] = vx_apollo[j-1] - a_earth_apollo * ( x_apollo[j-1] / r_earth_apollo ) * DT ;
		vy_apollo[j] = vy_apollo[j-1] - a_earth_apollo * ( y_apollo[j-1] / r_earth_apollo ) * DT ;
                
                //moon on apollo
		//
		r_moon_apollo = sqrt( ( (x_moon[j-1]-x_apollo[j-1])*(x_moon[j-1]-x_apollo[j-1]) ) + ( (y_moon[j-1]-y_apollo[j-1])*(y_moon[j-1]-y_apollo[j-1]) ) ) ;
		//
                if(r_moon_apollo < 1737000)
                {
                    printf("%s", "collision\n");
                }
		a_moon_apollo = G * m_moon / ( r_moon_apollo * r_moon_apollo ) ;
		//
		vx_apollo[j] = vx_apollo[j] - a_moon_apollo * ( (x_apollo[j-1]-x_moon[j-1]) / r_moon_apollo ) * DT ;
		vy_apollo[j] = vy_apollo[j] - a_moon_apollo * ( (y_apollo[j-1]-y_moon[j-1]) / r_moon_apollo ) * DT ;
	}
	//
	//////////////////////////////////////////////////
        //
        
        fout = fopen( "apollo.txt" , "w" ) ;
	//
	for( j = 0 ; j < n ; j ++ )
	{
		fprintf( fout , "%d %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f\n" ,
		j , t_apollo[j] , x_apollo[j] , y_apollo[j] , vx_apollo[j] , vy_apollo[j] , sqrt( vx_apollo[j]*vx_apollo[j] + vy_apollo[j]*vy_apollo[j] ), sqrt( x_apollo[j]*x_apollo[j] + y_apollo[j]*y_apollo[j] ) ) ;
	}
	//
	fclose( fout ) ;
        
	//
	fout = fopen( "orbit.txt" , "w" ) ;
	//
	for( j = 0 ; j < n ; j ++ )
	{
		fprintf( fout , "%d %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f\n" ,
		j , t_moon[j] , x_moon[j] , y_moon[j] , vx_moon[j] , vy_moon[j] , sqrt( vx_moon[j]*vx_moon[j] + vy_moon[j]*vy_moon[j] ), sqrt( x_moon[j]*x_moon[j] + y_moon[j]*y_moon[j] ) ) ;
	}
	//
	fclose( fout ) ;
	//
	//////////////////////////////////////////////////
	//
	fout = fopen( "earth.txt" , "w" ) ;
	//
	for( j = 0 ; j <= 360 ; j ++ )
	{
		fprintf( fout , "%0.16f %0.16f\n" , R * cos( j * M_PI / 180.0 ) , R * sin( j * M_PI / 180.0 ) ) ;
	}
	//
	fclose( fout ) ;
	//
	// done
	//
	return 0 ;
}
/*circle

n hours = 1.5
t = 0
x=0
y= 400000
vx = 7600
vy=0*/

/*ellipse
n hours = 10
t_moon[0]  = 0.0
x_moon[0]  = 0.0 
y_moon[0]  = R + 400000.0 
vx_moon[0] = 10000.777 
vy_moon[0] = 100.0 */

/*hyperbolic
 * 	int n = (int)( 0.5 + ( 0.5 * 60 * 60 ) / DT ) ; //1.5 is 1.5 hours (1.5 * 60 *60) replace 1.5
 * 
 * 	t_moon[0]  = 0.0          ; //original is 0.0
	x_moon[0]  = 0.0          ; //original is 0.0
	y_moon[0]  = R + 400000.0 ; //original is R + 400000.0
	vx_moon[0] = 6000.777     ; // change for more elliptical - and change duration //7777.77 is the original	
	vy_moon[0] = 6000.0       ; // original is 0
	*/
