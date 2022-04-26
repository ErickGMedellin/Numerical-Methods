#include <stdio.h>
#include <math.h>

void bisect (int* f, float a, float b, float es, int imax, int n){
	float ea=1;
	float xr=0, xold=0;
	int iter=0;
		while(es < ea && iter <= imax){
			float fa=0, fr=0;
			xold=xr;
			xr = (a+b)/2;
			iter = iter+1;
			if (xr != 0){
				ea = fabs((xr-xold)/xr)*100;
			}
			for (int i = 0; i <= n; ++i){
				fr = fr + f[i]*pow(xr,n-i);
				//printf("%f\n", fr);
			}
			for (int i = 0; i <= n; ++i){
				fa = fa + f[i]*pow(a,n-i);
				//printf("%f\n", fa);
			}
			float test;
			test = fa*fr;
			if (test < 0){
				b = xr;
			}
			else if (test > 0){
				a = xr;
			}
			else {
				ea=0;
			}
		}
		printf("Una raiz de f es: %f \n", xr);
}

void falsep (int* f, float a, float b, float es, int imax, int n){
	float ea=0;
	float xr=0, xold=0, fl=0, fu=0;
	int iter=0, i1, iu;
	for (int i = 0; i <= n; ++i){
		fl = fl + f[i]*pow(a,n-i);
	}
	for (int i = 0; i <= n; ++i){
		fu = fu + f[i]*pow(b,n-i);
	}
		while(es < ea || iter <= imax){
			xold=xr;
			float c, fr;
			c= fl-fu;
			xr = b-fu*(a-b)/c;
			fr=0;
			for (int i = 0; i <= n; ++i){
				fr = fr + f[i]*pow(xr,n-i);
			}
			iter = iter+1;
			if (xr != 0){
				ea = fabs((xr-xold)/xr)*100;
			}
			float test;
			test = fl*fr;
			if (test < 0){
				b = xr;
				fu=0;
				for (int i = 0; i <= n; ++i){
				fu = fu + f[i]*pow(b,n-i);
				}
				iu=0;
				i1=i1+1;
				if (i1>=2)
				{
					fl=fl/2;
				}
			}
			else if (test > 0){
				a = xr;
				fl=0;
				for (int i = 0; i <= n; ++i){
				fl = fl + f[i]*pow(a,n-i);
				}
				i1=0;
				iu=iu+1;
				if (iu>=2)
				{
					fu=fu/2;
				}
			}
			else {
				ea=0;
			}
		}
		printf("Una raiz de f es: %f \n", xr);
}


void NewRap(int* f, float xi, int imax, int n){
	int m=n-1;
	int fp[m];
	int iter=0;
	float xr;
	printf("Escribe los coeficientes de la derivada: \n");
	for (int i=0; i<=m; i++){
		scanf("%d", &fp[i]);
	}
	while (iter<=imax){
		iter = iter +1;
		float auxf=0;
		for (int i = 0; i <= n; ++i)
		{
			auxf = auxf + f[i]*pow(xi, n-i);
		}
		float auxfp = 0;
		for (int i = 0; i <= m; ++i)
		{
			auxfp = auxfp + fp[i]*pow(xi, m-i);
		}
		xr= xi - auxf/auxfp;
		xi=xr;
	}
	printf("Una raiz de f es: %f \n", xi);
}

void secante(int* f, float xi, int imax, int n){
	float a, b, xold, xr, ea=1;
	int iter=0;
	xold=0;
	while (iter <= imax && 0.0001 < ea){
		iter = iter+1;
		float fi=0, fo=0;
		for (int i = 0; i <= n; ++i){
			fi = fi + f[i]*pow(xi,n-i);
		}
		for (int i = 0; i <= n; ++i){
			fo = fo + f[i]*pow(xold,n-i);
		}
		ea = fabs(fi-fo);
		a= fi*(xold-xi);
		b= fo-fi;
		xr= xi - a/b;
		xold =xi;
		xi=xr;
	printf("Una raiz de f es: %f \n", xr);
	}
}


int main()
{
	printf("Este programa ayuda a encontrar las raices de un polinomio.\n");
	int n, m;
	printf("Introduce el grado del polinomio: \n");
	scanf("%d", &n);
	int f[n];
	printf("Escribe los coeficientes del polinomio \n(incluso los terminos nulos (0) y la constante): \n");
	for (int i=0; i<=n; i++){
		scanf("%d", &f[i]);
	}
	int met;
	float es;
	printf("Escribe el metodo a utilizar: 1 si es biseccion,\n 2 para falsa posicion, 3 para Newton-Raphson o 4 para secante. \n");
	scanf("%d", &met);

	if (met==1){
		int imax;
		printf("Escribe el maximo de iteraciones\n");
		scanf("%d", &imax);
		printf("Escribe el valor minimo del intervalo \n");
		float a, b, es;
		scanf("%f", &a);
		printf("Ahora el maximo \n");
		scanf("%f", &b);
		printf("Y el error \n");
		scanf("%f", &es);
		bisect(f, a, b, es, imax, n);

	}
	else if (met ==2){
	int imax;
	printf("Escribe el maximo de iteraciones\n");
	scanf("%d", &imax);
	printf("Escribe el valor minimo del intervalo \n");
	float a, b, es;
	scanf("%f", &a);
	printf("Ahora el maximo \n");
	scanf("%f", &b);
	printf("Y el error \n");
	scanf("%f", &es);
	falsep(f, a, b, es, imax, n);
	}
	else if (met==3){
		printf("Escribe el valor semilla: \n");
		int xi, imax;
		scanf("%d", &xi);
		printf("Escribe el maximo de iteraciones: \n");
		scanf("%d", &imax);
		NewRap(f, xi, imax, n);
	}
	else if(met==4){
		printf("Escribe el valor semilla: \n");
		int xi, imax;
		scanf("%d", &xi);
		printf("Escribe el maximo de iteraciones: \n");
		scanf("%d", &imax);
		secante(f, xi, imax, n);
	}
	return 0;
}