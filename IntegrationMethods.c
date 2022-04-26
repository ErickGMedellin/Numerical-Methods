#include <stdio.h>
#include <math.h>

float lagin(float x, float* X, float* Y, int k){
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
	return sum;
}

float pdx(float* pol, float x, int n){
	//int lenPol = sizeof(pol) / sizeof(pol[0]);
	float valorpdx=0;
	for (int j=0; j <= n; j++){
		valorpdx = valorpdx + pol[j]*pow(x, j);
	}
	return valorpdx;
}

float Trap(float* X, float* Y, int nn, int n, float a, float b){
	float h=(b-a)/n, x=a, sum;
	sum = lagin(x, X, Y, nn);
	for (int i=1; i<n-1; i++){
		x = x + h;
		sum = sum + lagin(x, X, Y, nn)*2;
	}
	sum = sum + lagin(b, X, Y, nn);
	float TrapEq;
	TrapEq = (b-a) * sum / (2*n);
	return TrapEq;
}

float Simpson(float* X, float* Y, int nn, int n, float a, float b){
	float h=(b-a)/n, x=a, sum;
	sum = lagin(x, X, Y, nn);
	for (int i=1; i<n-2; i+=2){
		x = x + h;
		sum = sum + lagin(x, X, Y, nn)*4;
		x = x + h;
		sum = sum + lagin(x, X, Y, nn)*2;
	}
	x = x + h;
	sum = sum + 4*lagin(b, X, Y, nn);
	sum = sum + lagin(b, X, Y, nn);
	float SimpEq;
	SimpEq = (b-a) * sum / (3*n);
	return SimpEq;
}


float romberg(float* X, float* Y, int nn, float a, float b, int maxit, float es) {
   float R1[maxit], R2[maxit];
   float *Rp = &R1[0], *Rc = &R2[0]; 
   float h = (b-a);
   //Rp[0] = (pdx(pol, a, n) + pdx(pol, b, n))*h*.5; 
   Rp[0] = (lagin(a, X, Y, nn) + lagin(b, X, Y, nn))*h*.5; 

   for (int i = 1; i < maxit; ++i) {
      h /= 2.;
      float c = 0;
      int ep = 1 << (i-1); 
      for (int j = 1; j <= ep; ++j) {
         //c += pdx(pol, a+(2*j-1)*h, n);
         c += lagin(a+(2*j-1)*h, X, Y, nn);
      }
      Rc[0] = h*c + .5*Rp[0]; 

      for (int j = 1; j <= i; ++j) {
         float n_k = pow(4, j);
         Rc[j] = (n_k*Rc[j-1] - Rp[j-1])/(n_k-1); 
      }

      if (i > 1 && fabs(Rp[i-1]-Rc[i]) < es) {
         return Rc[i-1];
      }
      float *rt = Rp;
      Rp = Rc;
      Rc = rt;
   }
   return Rp[maxit-1];
}

int main(){
	int n, k, maxit;
	printf("Escribe el grado del polinomio:\n");
	printf("Escribe la cantidad de puntos: ");
	scanf("%d ", &n);
	int nn=n-1;
	float X[n], Y[n];
	printf("Escribe los valores de X de los puntos \n");
	for (int i=0; i<n; i++){
		scanf("%f, %f", &X[i], &Y[i]);
	}
	
	float polin[n];
	printf("Escribe los coeficientes (incluyendo los ceros):\n");
	for(int i=0; i<=n; i++){
		scanf("%f", &polin[i]);
	}
	printf("Ahora escribe los limites de a y b de la integral y el numero de divisiones del intervalo de la forma: n, a, b\n");
	float a, b, es;
	scanf("%d, %f, %f", &k, &a, &b);
	printf("Para la integracion de Romberg, introduce el maximo de iteraciones y el error de la forma: maxit, err\n");
	scanf("%d, %f", &maxit, &es);
	printf("El polinomio a integrar es:\n");
	for (int j=0; j<=n;j++){
		if (j<n) printf("%.1fx^%d + ", polin[j], j);
		else printf("%.1fx^%d\n", polin[j], j);
	}
	printf("A9_DGTH.exe < inp1.txt\n");
	printf("La integral por el metodo del Trapecio da: %f \n", Trap(X, Y, nn, k, a, b));
	printf("La integral por el metodo de Simpson da: %f \n", Simpson(X, Y, nn, k, a, b));
	printf("La integral por el metodo de Romberg da: %f \n", romberg(X, Y, nn, a, b, maxit, es));
	return 0;
}