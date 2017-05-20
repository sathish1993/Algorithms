#include<stdio.h>
#include<stdlib.h>

int main(){
	int i = 0, w = 0, count = 0;
	int j = 0, k = 0, x = 1, y =1;	
	int weights[10];
	int profits[10];
	int items_added[10];
	int total_weight = 0;
	int W = 0, number_of_elements = 0;
	char line[500];
	
	//Reading file	
        FILE *file = fopen("knacksack.txt","r");
        if(file == NULL){
                printf("Error! Could not find the file\n");
                exit(-1);
        }
        while(fgets(line, sizeof line,file)!=NULL){
		if(count == 0){
			sscanf(line, "%d",&number_of_elements);
			weights[number_of_elements];
			profits[number_of_elements];
			items_added[number_of_elements];
		}
		else if(count == 1){
			sscanf(line, "%d, %d, %d ", &weights[0], &weights[1], &weights[2]);		
		}else if(count == 2){
			sscanf(line, "%d, %d, %d ", &profits[0], &profits[1], &profits[2]);		
		}else{
			sscanf(line, "%d",&W);
		}
		count++;
	}
	int B[number_of_elements+1][W+1];	
	
	//Initialise array
	for(w = 0; w < number_of_elements; w++){
		items_added[w] = -1;		
	}

	for(w = 0; w <= W; w++){
		B[0][w] = 0;
	}

	//Dynamic Prog
	for(x = 1; x <= number_of_elements; x++){
		B[x][0] = 0;
		for(y = 1; y <= W; y++){
			if( (weights[x-1] <= y) && (B[x-1][ y-weights[x-1] ] + profits[x-1] > B[x-1][y]) ){
				printf("x \n");
				B[x][y] = B[x-1][y-weights[x-1]] + profits[x-1];
			}else{
				printf("y \n");
				B[x][y] = B[x-1][y];
			}

		}
	}
	
	for(int s=0;s<=30;s++){
	printf("%d\t", s);
	}	
	printf("\n");
	for(int s=0;s<=3;s++){
		for(int t=0; t<=30;t++){
			printf("%d\t", B[s][t]);
		}
		printf("\n\n\n");
	}

	//Finding elements in the knacksack
	i = number_of_elements;
	w = W;
	while(i > 0){
		if(B[i][w] != B[i-1][w]){
			i = i-1;
			total_weight += weights[i];
			items_added[i] = i;
			w = w - weights[i];
		}else{
			i = i-1;
		}
	}

	printf("\n-------Items in Knacksack--------- \n");
	for(i = 0; i < number_of_elements; i++){
		if(items_added[i] != -1)
			printf("item - %d \t", items_added[i]);
	}
	printf("\n--------------------------------\n");	
	printf("Total Weight : %d\t", total_weight);
	printf("Max Profit %d \n", B[number_of_elements][W]);
	printf("--------------------------------\n");	
	return 0;
}
