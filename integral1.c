#include <stdio.h>
#include <math.h>

double dIntegral(double from, double to, double step, double (*func)(double)){
 double res=0;
 /* some magic here calculating res via from, to, step and func() */
 return res;
}

int main(){
 printf("Integral: %lf\n", dIntegral(0, 3.14159/2., 0.0001, sin)); 
 return 0;
}