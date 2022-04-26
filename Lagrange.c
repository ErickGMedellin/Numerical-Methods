#include <stdio.h>

void lagin(float x, float* X, float* Y, int k){
	float sum=0;
	for (int i=0; i<=k; i++){
		float prod = Y[i];
		for (int j=0; j<=k; j++){
			if (i != j){
				prod = prod*(x - X[j])/(X[i] - X[j]);
			}
		}
		sum = sum + prod;
	}
	printf("f(%f) = %f con un polinomio grado %d \n", x, sum, k);
}

int main(){
	int n, k;
	printf("Escribe la cantidad de puntos: ");
	scanf("%d ", &n);
	float X[n], Y[n];
	printf("Escribe los valores de X, y de los puntos \n");
	for (int i=0; i<n; i++){
		scanf("%f, %f", &X[i], &Y[i]);
	}
	printf("Escribe los valores de Y de los puntos \n");
	for (int i=0; i<n; i++){
		scanf("%f ", &Y[i]);
	}
	printf("Escribe el grado del polinomio que quieras\n");
	scanf("%d ", &k);
	float xx;
	printf("Escribe el valor que deseas interpolar \n");
	scanf("%f ", &xx);
	lagin(xx, X, Y, k);
	return 0;
}