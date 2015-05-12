#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int FFT_3(double *x_r, double *x_i, double *y_r, double *y_i, int N);
int FFT_2(double *x_r, double *x_i, double *y_r, double *y_i, int N);
int FFT_5(double *x_r, double *x_i, double *y_r, double *y_i, int N);
int Generate_N(int p, int q, int r);
int Initial(double *x, double *y, int N);
int Print_Complex_Vector(double *x, double *y, int N);

int main()
{
	int N, p, q, r;
	double *y_r, *y_i, *x_r, *x_i;
	clock_t t1, t2;
	while(1){
		printf("Please input p q r(all 0 is exit):");// Input N
		scanf("%d %d %d", &p, &q, &r);
		N = Generate_N(p, q, r);
		printf("N=2^%d 3^%d 5^%d = %d\n",p,q,r,N);
		// Create Memory for x and y
		x_r = (double *) malloc(N*sizeof(double));
		x_i = (double *) malloc(N*sizeof(double));
		y_r = (double *) malloc(N*sizeof(double));
		y_i = (double *) malloc(N*sizeof(double));
		
		Initial(x_r, x_i, N);
		if (p == 0 && q == 0 && r == 0){
			return 0;
		}
		else if((N%5) == 0){
			t1 = clock();
			FFT_5(x_r, x_i, y_r, y_i, N);
			t2 = clock();
			printf("%f secs\n", 1.0*(t2-t1)/CLOCKS_PER_SEC);	
			system("pause");
			//Print_Complex_Vector(y_r, y_i, N);	
		}
		else if((N%3) == 0){
			t1 = clock();
			FFT_3(x_r, x_i, y_r, y_i, N);
			t2 = clock();
			printf("%f secs\n", 1.0*(t2-t1)/CLOCKS_PER_SEC);	
			system("pause");
			//Print_Complex_Vector(y_r, y_i, N);	
		}
		else if((N%2) == 0){
			t1 = clock();
			FFT_2(x_r, x_i, y_r, y_i, N);
			t2 = clock();
			printf("%f secs\n", 1.0*(t2-t1)/CLOCKS_PER_SEC);	
			system("pause");
			//Print_Complex_Vector(y_r, y_i, N);	
		}
		else {
			printf("OH!have some error!");
			return 0;
		}
		
		free(x_r);
		free(x_i);
		free(y_r);
		free(y_i);
	}
	return 0;
	
}

int FFT_2(double *x_r, double *x_i, double *y_r, double *y_i, int N)
{
	if(N==1)
	{
		y_r[0] = x_r[0];
		y_i[0] = x_i[0];
		return 0; 
	}
	// input : x = x_r + i * x_i
	// output: y = y_r + i * y_i
	int k, n;
	double *u_r, *u_i, *v_r, *v_i, w_r, w_i;
	
	u_r = (double *) malloc(N*sizeof(double));
	u_i = (double *) malloc(N*sizeof(double));
	v_r = (double *) malloc(N*sizeof(double));
	v_i = (double *) malloc(N*sizeof(double));
	for(n=0;n<N/2;n++)
	{
		u_r[n] = x_r[2*n];
		u_i[n] = x_i[2*n];
		u_r[n+N/2] = x_r[2*n+1];
		u_i[n+N/2] = x_i[2*n+1];
	}
	if((n%5) == 0){
		FFT_5(u_r, u_i, v_r, v_i, N/2);
		FFT_5(u_r+N/2, u_i+N/2, v_r+N/2, v_i+N/2, N/2);
	}
	else if((n%3) == 0){
		FFT_3(u_r, u_i, v_r, v_i, N/2);
		FFT_3(u_r+N/2, u_i+N/2, v_r+N/2, v_i+N/2, N/2);
	}
	else{
		FFT_2(u_r, u_i, v_r, v_i, N/2);
		FFT_2(u_r+N/2, u_i+N/2, v_r+N/2, v_i+N/2, N/2);
	}
	
	for(k=0;k<N/2;++k)
	{
		// w^{-k} 
		w_r = cos(-k*2*M_PI/N);
		w_i = sin(-k*2*M_PI/N);
		y_r[k] = v_r[k] + (w_r*v_r[k+N/2] - w_i*v_i[k+N/2]);
		y_i[k] = v_i[k] + (w_r*v_i[k+N/2] + w_i*v_r[k+N/2]);
		y_r[k+N/2] = v_r[k] - (w_r*v_r[k+N/2] - w_i*v_i[k+N/2]);
		y_i[k+N/2] = v_i[k] - (w_r*v_i[k+N/2] + w_i*v_r[k+N/2]);
	}
	
	free(u_r);
	free(u_i);
	free(v_r);
	free(v_i);
	
	return 0;
}

int FFT_5(double *x_r, double *x_i, double *y_r, double *y_i, int N)
{
	if(N==1)
	{
		y_r[0] = x_r[0];
		y_i[0] = x_i[0];
		return 0; 
	}
	int k, n;
	double *u_r, *u_i, *v_r, *v_i, w_r, w_i,wr,wi;
	u_r = (double *) malloc(N*sizeof(double));
	u_i = (double *) malloc(N*sizeof(double));
	v_r = (double *) malloc(N*sizeof(double));
	v_i = (double *) malloc(N*sizeof(double));
	for(n=0;n<N/5;n++)
	{
		u_r[n] = x_r[5*n];
		u_i[n] = x_i[5*n];
		u_r[n+N/5] = x_r[5*n+1];
		u_i[n+N/5] = x_i[5*n+1];
		u_r[n+2*N/5] = x_r[5*n+2];
		u_i[n+2*N/5] = x_i[5*n+2];
		u_r[n+3*N/5] = x_r[5*n+3];
		u_i[n+3*N/5] = x_i[5*n+3];
		u_r[n+4*N/5] = x_r[5*n+4];
		u_i[n+4*N/5] = x_i[5*n+4];
		
	}
	if((n%5) == 0){
		FFT_5(u_r, u_i, v_r, v_i, N/5);
		FFT_5(u_r+N/5, u_i+N/5, v_r+N/5, v_i+N/5, N/5);
		FFT_5(u_r+2*N/5, u_i+2*N/5, v_r+2*N/5, v_i+2*N/5, N/5);
		FFT_5(u_r+3*N/5, u_i+3*N/5, v_r+3*N/5, v_i+3*N/5, N/5);
		FFT_5(u_r+4*N/5, u_i+4*N/5, v_r+4*N/5, v_i+4*N/5, N/5);
	}
	else if((n%3) == 0){
		FFT_3(u_r, u_i, v_r, v_i, N/5);
		FFT_3(u_r+N/5, u_i+N/5, v_r+N/5, v_i+N/5, N/5);
		FFT_3(u_r+2*N/5, u_i+2*N/5, v_r+2*N/5, v_i+2*N/5, N/5);
		FFT_3(u_r+3*N/5, u_i+3*N/5, v_r+3*N/5, v_i+3*N/5, N/5);
		FFT_3(u_r+4*N/5, u_i+4*N/5, v_r+4*N/5, v_i+4*N/5, N/5);
	}
	else{
		FFT_2(u_r, u_i, v_r, v_i, N/5);
		FFT_2(u_r+N/5, u_i+N/5, v_r+N/5, v_i+N/5, N/5);
		FFT_2(u_r+2*N/5, u_i+2*N/5, v_r+2*N/5, v_i+2*N/5, N/5);
		FFT_2(u_r+3*N/5, u_i+3*N/5, v_r+3*N/5, v_i+3*N/5, N/5);
		FFT_2(u_r+4*N/5, u_i+4*N/5, v_r+4*N/5, v_i+4*N/5, N/5);
	}
	
	
	for(k=0;k<N/5;++k)
	{
		w_r = cos(-k*2*M_PI/N);
		w_i = sin(-k*2*M_PI/N);
		y_r[k] = v_r[k] + w_r*v_r[k+N/5] - w_i*v_i[k+N/5];
		y_i[k] = v_i[k] + w_r*v_i[k+N/5] + w_i*v_r[k+N/5];
		w_r = cos(-k*4*M_PI/N);
		w_i = sin(-k*4*M_PI/N);
		y_r[k] += w_r*v_r[k+2*N/5] - w_i*v_i[k+2*N/5]; 
		y_i[k] += w_r*v_i[k+2*N/5] + w_i*v_r[k+2*N/5];
		w_r = cos(-k*6*M_PI/N);
		w_i = sin(-k*6*M_PI/N);
		y_r[k] += w_r*v_r[k+3*N/5] - w_i*v_i[k+3*N/5];
		y_i[k] += w_r*v_i[k+3*N/5] + w_i*v_r[k+3*N/5];
		w_r = cos(-k*8*M_PI/N);
		w_i = sin(-k*8*M_PI/N);
		y_r[k] += w_r*v_r[k+4*N/5] - w_i*v_i[k+4*N/5];
		y_i[k] += w_r*v_i[k+4*N/5] + w_i*v_r[k+4*N/5];
		
		w_r = cos(-(k+N/5)*2*M_PI/N);
		w_i = sin(-(k+N/5)*2*M_PI/N);
		y_r[k+N/5] = v_r[k] + w_r*v_r[k+N/5] - w_i*v_i[k+N/5];
		y_i[k+N/5] = v_i[k] + w_r*v_i[k+N/5] + w_i*v_r[k+N/5];
		w_r = cos(-(k+N/5)*4*M_PI/N);
		w_i = sin(-(k+N/5)*4*M_PI/N);
		y_r[k+N/5] += w_r*v_r[k+2*N/5] - w_i*v_i[k+2*N/5]; 
		y_i[k+N/5] += w_r*v_i[k+2*N/5] + w_i*v_r[k+2*N/5];
		w_r = cos(-(k+N/5)*6*M_PI/N);
		w_i = sin(-(k+N/5)*6*M_PI/N);
		y_r[k+N/5] += w_r*v_r[k+3*N/5] - w_i*v_i[k+3*N/5];
		y_i[k+N/5] += w_r*v_i[k+3*N/5] + w_i*v_r[k+3*N/5];
		w_r = cos(-(k+N/5)*8*M_PI/N);
		w_i = sin(-(k+N/5)*8*M_PI/N);
		y_r[k+N/5] += w_r*v_r[k+4*N/5] - w_i*v_i[k+4*N/5];
		y_i[k+N/5] += w_r*v_i[k+4*N/5] + w_i*v_r[k+4*N/5];
		
		w_r = cos(-(k+2*N/5)*2*M_PI/N);
		w_i = sin(-(k+2*N/5)*2*M_PI/N);
		y_r[k+2*N/5] = v_r[k] + w_r*v_r[k+N/5] - w_i*v_i[k+N/5];
		y_i[k+2*N/5] = v_i[k] + w_r*v_i[k+N/5] + w_i*v_r[k+N/5];
		w_r = cos(-(k+2*N/5)*4*M_PI/N);
		w_i = sin(-(k+2*N/5)*4*M_PI/N);
		y_r[k+2*N/5] += w_r*v_r[k+2*N/5] - w_i*v_i[k+2*N/5]; 
		y_i[k+2*N/5] += w_r*v_i[k+2*N/5] + w_i*v_r[k+2*N/5];
		w_r = cos(-(k+2*N/5)*6*M_PI/N);
		w_i = sin(-(k+2*N/5)*6*M_PI/N);
		y_r[k+2*N/5] += w_r*v_r[k+3*N/5] - w_i*v_i[k+3*N/5];
		y_i[k+2*N/5] += w_r*v_i[k+3*N/5] + w_i*v_r[k+3*N/5];
		w_r = cos(-(k+2*N/5)*8*M_PI/N);
		w_i = sin(-(k+2*N/5)*8*M_PI/N);
		y_r[k+2*N/5] += w_r*v_r[k+4*N/5] - w_i*v_i[k+4*N/5];
		y_i[k+2*N/5] += w_r*v_i[k+4*N/5] + w_i*v_r[k+4*N/5];
		
		w_r = cos(-(k+3*N/5)*2*M_PI/N);
		w_i = sin(-(k+3*N/5)*2*M_PI/N);
		y_r[k+3*N/5] = v_r[k] + w_r*v_r[k+N/5] - w_i*v_i[k+N/5];
		y_i[k+3*N/5] = v_i[k] + w_r*v_i[k+N/5] + w_i*v_r[k+N/5];
		w_r = cos(-(k+3*N/5)*4*M_PI/N);
		w_i = sin(-(k+3*N/5)*4*M_PI/N);
		y_r[k+3*N/5] += w_r*v_r[k+2*N/5] - w_i*v_i[k+2*N/5]; 
		y_i[k+3*N/5] += w_r*v_i[k+2*N/5] + w_i*v_r[k+2*N/5];
		w_r = cos(-(k+3*N/5)*6*M_PI/N);
		w_i = sin(-(k+3*N/5)*6*M_PI/N);
		y_r[k+3*N/5] += w_r*v_r[k+3*N/5] - w_i*v_i[k+3*N/5];
		y_i[k+3*N/5] += w_r*v_i[k+3*N/5] + w_i*v_r[k+3*N/5];
		w_r = cos(-(k+3*N/5)*8*M_PI/N);
		w_i = sin(-(k+3*N/5)*8*M_PI/N);
		y_r[k+3*N/5] += w_r*v_r[k+4*N/5] - w_i*v_i[k+4*N/5];
		y_i[k+3*N/5] += w_r*v_i[k+4*N/5] + w_i*v_r[k+4*N/5];
		
		w_r = cos(-(k+4*N/5)*2*M_PI/N);
		w_i = sin(-(k+4*N/5)*2*M_PI/N);
		y_r[k+4*N/5] = v_r[k] + w_r*v_r[k+N/5] - w_i*v_i[k+N/5];
		y_i[k+4*N/5] = v_i[k] + w_r*v_i[k+N/5] + w_i*v_r[k+N/5];
		w_r = cos(-(k+4*N/5)*4*M_PI/N);
		w_i = sin(-(k+4*N/5)*4*M_PI/N);
		y_r[k+4*N/5] += w_r*v_r[k+2*N/5] - w_i*v_i[k+2*N/5]; 
		y_i[k+4*N/5] += w_r*v_i[k+2*N/5] + w_i*v_r[k+2*N/5];
		w_r = cos(-(k+4*N/5)*6*M_PI/N);
		w_i = sin(-(k+4*N/5)*6*M_PI/N);
		y_r[k+4*N/5] += w_r*v_r[k+3*N/5] - w_i*v_i[k+3*N/5];
		y_i[k+4*N/5] += w_r*v_i[k+3*N/5] + w_i*v_r[k+3*N/5];
		w_r = cos(-(k+4*N/5)*8*M_PI/N);
		w_i = sin(-(k+4*N/5)*8*M_PI/N);
		y_r[k+4*N/5] += w_r*v_r[k+4*N/5] - w_i*v_i[k+4*N/5];
		y_i[k+4*N/5] += w_r*v_i[k+4*N/5] + w_i*v_r[k+4*N/5];
	}
	
	free(u_r);
	free(u_i);
	free(v_r);
	free(v_i);
	
	return 0;
}

int FFT_3(double *x_r, double *x_i, double *y_r, double *y_i, int N)
{
	if(N==1)
	{
		y_r[0] = x_r[0];
		y_i[0] = x_i[0];
		return 0; 
	}
	int k, n;
	double *u_r, *u_i, *v_r, *v_i, w_r, w_i,wr,wi;
	u_r = (double *) malloc(N*sizeof(double));
	u_i = (double *) malloc(N*sizeof(double));
	v_r = (double *) malloc(N*sizeof(double));
	v_i = (double *) malloc(N*sizeof(double));
	for(n=0;n<N/3;n++)
	{
		u_r[n] = x_r[3*n];
		u_i[n] = x_i[3*n];
		u_r[n+N/3] = x_r[3*n+1];
		u_i[n+N/3] = x_i[3*n+1];
		u_r[n+2*N/3] = x_r[3*n+2];
		u_i[n+2*N/3] = x_i[3*n+2];
	}
	if((n%5) == 0){
		FFT_5(u_r, u_i, v_r, v_i, N/3);
		FFT_5(u_r+N/3, u_i+N/3, v_r+N/3, v_i+N/3, N/3);
		FFT_5(u_r+2*N/3, u_i+2*N/3, v_r+2*N/3, v_i+2*N/3, N/3);
	}
	else if((n%3) == 0){
		FFT_3(u_r, u_i, v_r, v_i, N/3);
		FFT_3(u_r+N/3, u_i+N/3, v_r+N/3, v_i+N/3, N/3);
		FFT_3(u_r+2*N/3, u_i+2*N/3, v_r+2*N/3, v_i+2*N/3, N/3);
	}
	else{
		FFT_2(u_r, u_i, v_r, v_i, N/3);
		FFT_2(u_r+N/3, u_i+N/3, v_r+N/3, v_i+N/3, N/3);
		FFT_2(u_r+2*N/3, u_i+2*N/3, v_r+2*N/3, v_i+2*N/3, N/3);
	}
	
	
	for(k=0;k<N/3;++k)
	{
		w_r = cos(-k*2*M_PI/N);
		w_i = sin(-k*2*M_PI/N);
		y_r[k] = v_r[k] + w_r*v_r[k+N/3] - w_i*v_i[k+N/3];
		y_i[k] = v_i[k] + w_r*v_i[k+N/3] + w_i*v_r[k+N/3];
		w_r = cos(-k*4*M_PI/N);
		w_i = sin(-k*4*M_PI/N);
		y_r[k] += w_r*v_r[k+2*N/3] - w_i*v_i[k+2*N/3];
		y_i[k] += w_r*v_i[k+2*N/3] + w_i*v_r[k+2*N/3];
		
		w_r = cos(-(k+N/3)*2*M_PI/N);
		w_i = sin(-(k+N/3)*2*M_PI/N);
		y_r[k+N/3] = v_r[k] + w_r*v_r[k+N/3] - w_i*v_i[k+N/3];
		y_i[k+N/3] = v_i[k] + w_r*v_i[k+N/3] + w_i*v_r[k+N/3];
		w_r = cos(-(k+N/3)*4*M_PI/N);
		w_i = sin(-(k+N/3)*4*M_PI/N);
		y_r[k+N/3] += w_r*v_r[k+2*N/3] - w_i*v_i[k+2*N/3];
		y_i[k+N/3] += w_r*v_i[k+2*N/3] + w_i*v_r[k+2*N/3];
		
		w_r = cos(-(k+2*N/3)*2*M_PI/N);
		w_i = sin(-(k+2*N/3)*2*M_PI/N);
		y_r[k+2*N/3] = v_r[k] + w_r*v_r[k+N/3] - w_i*v_i[k+N/3];
		y_i[k+2*N/3] = v_i[k] + w_r*v_i[k+N/3] + w_i*v_r[k+N/3] ;
		w_r = cos(-(k+2*N/3)*4*M_PI/N);
		w_i = sin(-(k+2*N/3)*4*M_PI/N);
		y_r[k+2*N/3] += w_r*v_r[k+2*N/3] - w_i*v_i[k+2*N/3];
		y_i[k+2*N/3] += w_r*v_i[k+2*N/3] + w_i*v_r[k+2*N/3];
	}
	
	free(u_r);
	free(u_i);
	free(v_r);
	free(v_i);
	
	return 0;
}

int Generate_N(int p, int q, int r)
{
	int i, N = 1;
	// N = 2^p 3^q 5^r
	for(i=0;i<p;++i) N = N * 2;
	for(i=0;i<q;++i) N = N * 3;
	for(i=0;i<r;++i) N = N * 5;	
	
	return N;
}
int Initial(double *x, double *y, int N)
{
	int n;
	for(n=0;n<N;++n)
	{
		x[n] = n; 
		y[n] = 0; 
	}

}
int Print_Complex_Vector(double *x, double *y, int N)
{
	int n;
	for(n=0;n<N;++n)
	{
		if(y[n]>=0) printf("%d : %f +%f i\n", n, x[n], y[n]);
		else printf("%d : %f %f i\n", n, x[n], y[n]);
	}

}

