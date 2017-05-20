#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>

int n = 0; //Array size

//Method to add matrices
void add(int l, float A[][l], float B[][l], float C[][l]){
	int  i = 0, j = 0;
        for (i = 0; i < l; i++){
            	for (j = 0; j < l; j++){
        	        C[i][j] = A[i][j] + B[i][j];
		}
	}
}

//Method to sub matrices
void sub(int l, float A[][l], float B[][l], float C[][l]){
	int  i = 0, j = 0;
        for (i = 0; i < l; i++){
            	for (j = 0; j < l; j++){
        	        C[i][j] = A[i][j] - B[i][j];
		}
	}
}

//Method to check if given number is power of 2
int isPowerOfTwo (int x)
{
  return x && (!(x&(x-1)));
}

//Method to find strassens for 2*2 Matrix
void customStrassensMultiplicationfor2by2(int l, float arrA[][l], float arrB[][l], float arrC[][l]){
	float m1, m2, m3, m4, m5, m6, m7;
	
	m1 = (arrA[0][0] + arrA[1][1]) * (arrB[0][0] + arrB[1][1]);
	m2 = (arrA[1][0] + arrA[1][1]) * arrB[0][0];
	m3 = arrA[0][0] * (arrB[0][1] - arrB[1][1]);
	m4 = arrA[1][1] * (arrB[1][0] - arrB[0][0]);
	m5 = (arrA[0][0] + arrA[0][1]) * arrB[1][1];
	m6 = (arrA[1][0] - arrA[0][0]) * (arrB[0][0] + arrB[0][1]);
	m7 = (arrA[0][1] - arrA[1][1]) * (arrB[1][0] + arrB[1][1]);
	
	arrC[0][0] = m1 + m4 - m5 + m7;
  	arrC[0][1] = m3 + m5;
  	arrC[1][0] = m2 + m4;
  	arrC[1][1] = m1 - m2 + m3 + m6;	
}

//Method to run strassensMultiplication
void customStrassensMultiplication(int l, float arrA[][l], float arrB[][l], float arrC[][l]){
	if(l == 1){
		// base case
		arrC[0][0] = arrA[0][0] * arrB[0][0];
		return;
	}else if(l == 2){
		customStrassensMultiplicationfor2by2(l, arrA, arrB, arrC);
	}else{
		int len = l/2;
		float arrA11[len][len], arrA12[len][len], arrA21[len][len], arrA22[len][len];
		float arrB11[len][len], arrB12[len][len], arrB21[len][len], arrB22[len][len];
		float arrC11[len][len], arrC12[len][len], arrC21[len][len], arrC22[len][len];
		float M1[len][len], M2[len][len], M3[len][len], M4[len][len];
		float M5[len][len], M6[len][len], M7[len][len];
		float aMatrix[len][len], bMatrix[len][len];
		int i, j;

		//Divide into 4 sub Matrices
		for(i = 0; i < len; i++){
			for(j = 0; j<len; j++){
				arrA11[i][j] = arrA[i][j];
		                arrA12[i][j] = arrA[i][j + len];
                		arrA21[i][j] = arrA[i + len][j];
		                arrA22[i][j] = arrA[i + len][j + len];

		                arrB11[i][j] = arrB[i][j];
                		arrB12[i][j] = arrB[i][j + len];
		                arrB21[i][j] = arrB[i + len][j];
		                arrB22[i][j] = arrB[i + len][j + len];
			}
		}

		//Calculating M1 to M7
		add(len, arrA11, arrA22, aMatrix);
		add(len, arrB11, arrB22, bMatrix);
		customStrassensMultiplication(len, aMatrix, bMatrix, M1);// M1 = (a11+a22) * (b11+b22)

		add(len, arrA21, arrA22, aMatrix);
        	customStrassensMultiplication(len, aMatrix, arrB11, M2);// M2 = (a21+a22) * (b11)

        	sub(len, arrB12, arrB22, bMatrix);
        	customStrassensMultiplication(len, arrA11, bMatrix, M3);// M3 = (a11) * (b12 - b22)

        	sub(len, arrB21, arrB11, bMatrix);
        	customStrassensMultiplication(len, arrA22, bMatrix, M4);// M4 = (a22) * (b21 - b11)

        	add(len, arrA11, arrA12, aMatrix);
        	customStrassensMultiplication(len, aMatrix, arrB22, M5);// M5 = (a11+a12) * (b22)

        	sub(len, arrA21, arrA11, aMatrix);
        	add(len, arrB11, arrB12, bMatrix);
        	customStrassensMultiplication(len, aMatrix, bMatrix , M6);// M6 = (a21-a11) * (b11+b12)

        	sub(len, arrA12, arrA22, aMatrix);
        	add(len, arrB21, arrB22, bMatrix);
        	customStrassensMultiplication(len, aMatrix, bMatrix, M7);// M7 = (a12-a22) * (b21+b22)

		//Calculating C submatrix
        	add(len, M1, M4, arrC11);
		add(len, arrC11, M7, arrC11);
        	sub(len, arrC11, M5, arrC11);// C11 = M1 + M4 - M5 + M7

		add(len, M3, M5, arrC12);// C12 = M3 + M5
        
	        add(len, M2, M4, arrC21);// C21 = M2 + M4
        
       		add(len, M1, M3, arrC22);
        	add(len, arrC22, M6, arrC22);
	        sub(len, arrC22, M2, arrC22);// C22 = M1 + M3 - M2 + M6

		//Conquer
		for(i = 0; i < len;i++){
			for(j = 0; j < len; j++){
				arrC[i][j] = arrC11[i][j];
				arrC[i][j + len] = arrC12[i][j];
				arrC[i + len][j] = arrC21[i][j];
				arrC[i + len][j + len] = arrC22[i][j];  
			}
		}
		
	}
}


//Method to perform strassensMultiplication
void strassensMultiplication(int l, float arrA[][l], float arrB[][l], float arrC[][l]){
	int i = 0, j = 0, nearestPow = 0;
	if(isPowerOfTwo(n)){
		customStrassensMultiplication(l, arrA, arrB, arrC);	
		printf("Strassen Multiplication Output\n");
		for(i = 0; i < n;i++){
			for(j = 0; j < n; j++){
				printf("%0.2f\t",arrC[i][j]);
			}
		printf("\n");
		}
		printf("\n");
	}else{
		nearestPow = pow(2, ceil(log(n)/log(2)));
		float arrATemp[nearestPow][nearestPow];
		float arrBTemp[nearestPow][nearestPow];
		float arrCTemp[nearestPow][nearestPow];
		memset(arrATemp, 0.0, sizeof(arrATemp[0][0]) * nearestPow * nearestPow);
		memset(arrBTemp, 0.0, sizeof(arrBTemp[0][0]) * nearestPow * nearestPow);
		memset(arrCTemp, 0.0, sizeof(arrCTemp[0][0]) * nearestPow * nearestPow);
		
		//padding with extra zeros
		for(i = 0; i < nearestPow; i++){
			for(j = 0; j < nearestPow; j++){
				if(i < n && j < n){
					arrATemp[i][j] = arrA[i][j];
					arrBTemp[i][j] = arrB[i][j];
				}
			}
		}
			
		customStrassensMultiplication(nearestPow, arrATemp, arrBTemp, arrCTemp);	
		
		printf("Strassen Multiplication Output\n");
		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				printf("%0.2f\t",arrCTemp[i][j]);
			}
		printf("\n");
		}
		printf("\n");
	}
}

//Method to do Standard Multiplication
void customStandardMultiplication(float arrA[][n], float arrB[][n], float arrC[][n], int n){
	int i = 0, j = 0, k = 0;
	
	for(i = 0; i < n;i++){
		for(j = 0; j < n; j++){
			for(k = 0; k < n; k++){
				arrC[i][j] +=  arrA[i][k]*arrB[k][j];
			}
		}
	}
}
	
//Method to run Standard Multiplication
void standardMultiplication(float arrA[][n], float arrB[][n], float arrC[][n], int n){
	int i = 0, j = 0;
	customStandardMultiplication(arrA, arrB, arrC, n);
	printf("Standard Multiplication Output\n");
	for(i = 0; i < n;i++){
		for(j = 0; j < n; j++){
			printf("%0.2f\t",arrC[i][j]);
		}
		printf("\n");
	}	
	printf("\n");
}



int main(int argc, char *argv[]){
	int i = 0, j = 0, k = 0;
	if(argv[1] == NULL || atoi(argv[1]) < 1){
		printf("Please enter value of postive value of n. Exiting System now..\n");
		exit(0);
	}
	n = atoi(argv[1]);
	float arrayA[n][n], arrayB[n][n], arrayC[n][n];
	
	memset(arrayA, 0.0, sizeof(arrayA[0][0]) * n * n);
	memset(arrayB, 0.0, sizeof(arrayB[0][0]) * n * n);
	memset(arrayC, 0.0, sizeof(arrayC[0][0]) * n * n);
	srand(time(NULL));
	
	for(i = 0; i < n;i++){
		for(j = 0; j < n; j++){
			arrayA[i][j] = (5 - (-5)) * ((float)rand() / RAND_MAX) + -5;
			arrayB[i][j] = (5 - (-5)) * ((float)rand() / RAND_MAX) + -5;
		}
	}
	
	printf("Matrix A \n");
	
	for(i = 0; i < n;i++){
		for(j = 0; j < n; j++){
			printf("%0.2f\t",arrayA[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("Matrix B \n");
	
	for(i = 0; i < n;i++){
		for(j = 0; j < n; j++){
			printf("%0.2f\t",arrayB[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	
	//strassensMultiplication
	strassensMultiplication(n, arrayA, arrayB, arrayC);
	
	memset(arrayC, 0, sizeof(arrayC[0][0]) * n * n);
	
	//standard Multiplication
	standardMultiplication(arrayA, arrayB, arrayC, n);
		
	return 0;
}
