#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
	int W = 0, i = 0, j = 0, max_profit_set = 0, size = 0, count = 0, number_of_elements = 0;
	int weights[number_of_elements];
	int profits[number_of_elements];
	int total_weight = 0, max_profit = 0;
	int temp_weight = 0, temp_profit = 0;
	int items[100][100];	
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

	//Initialize items array
	size = pow(2, number_of_elements);
	for(i = 0; i < size; i++){
		for(j = 0; j < number_of_elements+2; j++){
			items[i][j] = -1;
		}
	}
	//Brute force logic 
	for(i = 0; i < size; i++){
		temp_profit = 0;
		temp_weight = 0;
		max_profit = 0;
		count = 0;
		for(j = 0; j < number_of_elements; j++){
			if( i & (1 << j)){	
				temp_weight += weights[j];
				temp_profit += profits[j];			
				if(temp_weight <= W ){
					items[i][count] = j;
					items[i][number_of_elements] = temp_profit;
					items[i][number_of_elements+1] = temp_weight;
				}
				count++;
			}
		}
	}
	
	for(i = 0; i < size; i++){
		for(j = 0; j < number_of_elements+2; j++){
			if(max_profit < items[i][number_of_elements]){
				max_profit = items[i][number_of_elements];
				total_weight = items[i][number_of_elements+1];
				max_profit_set = i;
			}
		}
	}

	printf("--------Items in knacksack------- \n");
	for(j = 0; j < number_of_elements; j++){
		if(items[max_profit_set][j] != -1)
			printf("Item - %d \t", items[max_profit_set][j]);	
	}
	printf("\n---------------------------------\n");
	printf("\nMax Profit %d, Total Weight %d\n", max_profit, total_weight);
	printf("---------------------------------\n");
	return 0;
}
