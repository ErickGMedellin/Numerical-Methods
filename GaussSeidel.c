#include <stdio.h>
#include <math.h>

void GS(float* r1, float* r2, float* r3){
	float x=0, y=0, z=0, ex=1, ey=1, ez=1, ep=0.0001, xn, yn, zn;
	int it=0;
	while (ex>ep && ey>ep && ez>ep && it<200){
		it=1+it;
		xn = (r1[3] - r1[1]*y - r1[2]*z)/r1[0];
		if (it>2){
			ex = fabs((xn-x)/x)*100;
		}
		x=xn;
		yn = (r2[3] - r2[0]*x - r2[2]*z)/r2[1];
		if (it>2){
			ey = fabs((yn-y)/y)*100;
		}
		y=yn;
		zn = (r3[3] - r3[0]*x - r3[1]*y)/r3[2];
		if (it>2){
			ez = fabs((zn-z)/z)*100;
		}
		z=zn;
	}
	if(it<2000){
		printf("Se obtuvo un error menor a %f en la iteracion: %d \n", ep, it);
	}
	printf("Los valores solucion son: (x, y, z) = (%f, %f, %f) \n", x, y, z);
}


int main(){
	//printf("Inserte uno a uno los coeficientes de la matriz aumentada (por renglones): ");
	int n=4;
	float r1[n], r2[n], r3[n];
	for (int i=0; i<n; i++){
		scanf("%f ", &r1[i]);
	}
	//printf("Siguiente renglon\n");
	for (int i=0; i<n; i++){
		scanf("%f ", &r2[i]);
	}
	//printf("Renglon final\n");
	for (int i=0; i<n; i++){
		scanf("%f ", &r3[i]);
	}
	GS(r1, r2, r3);
	return 0;
}