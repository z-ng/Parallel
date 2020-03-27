#include <stdio.h>
#include <math.h>
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
	int n = (int)( 0.5 + ( 10 * 60 * 60 ) / DT ) ; //1.5 is 1.5 hours (1.5 * 60 *60) replace 1.5
	//
	//////////////////////////////////////////////////
	//
	double  t[n] ;
	double  x[n] ;
	double  y[n] ;
	double vx[n] ;
	double vy[n] ;
	//
	//////////////////////////////////////////////////
	//
	FILE* fout   ;
	//
	int j        ;
	//
	double r , a ;
	//
	// double m = 28801.0 ; // kg - Apollo 11
	double m = 419725.0 ; // kg - ISS
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
	t[0]  = 0.0          ; //original is 0.0
	x[0]  = 0.0          ; //original is 0.0
	y[0]  = R + 400000.0 ; //original is R + 400000.0
	vx[0] = 10000.777     ; // change for more elliptical - and change duration //7777.77 is the original	
	vy[0] = 100.0       ; // original is 0
	//
	// hyperbolic changes both initial (x,y) and (vx,vy) - compare to circular
	//
	//////////////////////////////////////////////////
	//
	for( j = 1 ; j < n ; j ++ )
	{
		t[j] = t[j-1] + DT           ;
		x[j] = x[j-1] + DT * vx[j-1] ;
		y[j] = y[j-1] + DT * vy[j-1] ;
		//
		r = sqrt( x[j-1]*x[j-1] + y[j-1]*y[j-1] ) ;
		//
		a = G * M / ( r * r ) ;
		//
		vx[j] = vx[j-1] - a * ( x[j-1] / r ) * DT ;
		vy[j] = vy[j-1] - a * ( y[j-1] / r ) * DT ;
	}
	//
	//////////////////////////////////////////////////
	//
	fout = fopen( "orbit.txt" , "w" ) ;
	//
	for( j = 0 ; j < n ; j ++ )
	{
		fprintf( fout , "%d %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f\n" ,
		j , t[j] , x[j] , y[j] , vx[j] , vy[j] , sqrt( vx[j]*vx[j] + vy[j]*vy[j] ), sqrt( x[j]*x[j] + y[j]*y[j] ) ) ;
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
//
// end of file
//

/*circle
n hours = 1.5
t = 0
x=0
y= 400000
vx = 7600
vy=0*/

/*ellipse
n hours = 10
t[0]  = 0.0
x[0]  = 0.0 
y[0]  = R + 400000.0 
vx[0] = 10000.777 
vy[0] = 100.0 */

/*hyperbolic
 * 	int n = (int)( 0.5 + ( 0.5 * 60 * 60 ) / DT ) ; //1.5 is 1.5 hours (1.5 * 60 *60) replace 1.5
 * 
 * 	t[0]  = 0.0          ; //original is 0.0
	x[0]  = 0.0          ; //original is 0.0
	y[0]  = R + 400000.0 ; //original is R + 400000.0
	vx[0] = 6000.777     ; // change for more elliptical - and change duration //7777.77 is the original	
	vy[0] = 6000.0       ; // original is 0
	*/
