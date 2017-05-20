#include<stdio.h>
#include<stdlib.h>
int main(){
	int W = 0, i = 0, count = 0, number_of_elements = 0;
	int weights[number_of_elements];
	int profits[number_of_elements];
	int temp_weights[number_of_elements];
	int temp_profits[number_of_elements];
	int items_added[number_of_elements];
	int benefit[number_of_elements];
	int total_profit = 0, total_weight = 0, temp_profit = 0;
	int temp_weight = 0, max_profit = 0, max_item = 0, temp_benefit = 0;
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
			temp_weights[number_of_elements];
			temp_profits[number_of_elements];
			benefit[number_of_elements];
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

	//Max Benefit First
	printf("--------Max Benefit First-------- \n");
	count = 0;
	for (i = 0; i < number_of_elements; i++){
		items_added[i] = -1;
	}
	for (i = 0; i < number_of_elements; i++){
		temp_weights[i] = weights[i];
		temp_profits[i] = profits[i];
   	} 
	while(total_weight <= W){
		temp_profit = 0;
		for(i = 0; i < number_of_elements; i++){
			if(temp_profit < temp_profits[i]){
				temp_profit = temp_profits[i];
				max_item = i;
			}
		}
		total_weight += temp_weights[max_item];
		if(total_weight <= W){
			max_profit += temp_profit;
			items_added[count] = max_item;
			temp_profits[max_item] = -1;
			temp_weights[max_item] = -1;
			count++;
		}else{
			total_weight -= temp_weights[max_item];		
			break;	
		}
	}
	printf("-------Items in Knacksack---------\n");
	for (i = 0; i < number_of_elements; i++){
		if(items_added[i] != -1)
			printf("item - %d profit - %d weight - %d\n",items_added[i], profits[items_added[i]], weights[items_added[i]]);		
	}
	printf("-------------------------------\n");	
	printf("\nTotal profit %d, Total weight %d \n",max_profit, total_weight);	
	printf("-------------------------------\n");	
	printf("\n\n");
	
	//Min Weight First	
	printf("\n-------Min Weight First--------\n");
	count = 0;
	max_profit = 0;
	total_weight = 0;
	for (i = 0; i < number_of_elements; i++){
		items_added[i] = -1;
	}
	for (i = 0; i < number_of_elements; i++){
		temp_weights[i] = weights[i];
		temp_profits[i] = profits[i];
   	} 
	while(total_weight <= W){
		temp_weight = 10000;
		for(i = 0; i < number_of_elements; i++){
			if(temp_weight > temp_weights[i]){
				temp_weight = temp_weights[i];
				temp_profit = temp_profits[i];
				max_item = i;
			}
		}
		total_weight += temp_weights[max_item];
		if(total_weight <= W){
			max_profit += temp_profit;
			items_added[count] = max_item;
			temp_profits[max_item] = 100000;
			temp_weights[max_item] = 100000;
			count++;
		}else{
			total_weight -= temp_weights[max_item];		
			break;	
		}
	}

	printf("-----Items in Knacksack-------\n");
	for (i = 0; i < number_of_elements; i++){
		if(items_added[i] != -1)
			printf("item - %d profit - %d weight - %d\n",items_added[i], profits[items_added[i]], weights[items_added[i]]);		
	}
	printf("-------------------------------\n");	
	printf("\nTotal profit %d, Total weight %d \n",max_profit, total_weight);	
	printf("-------------------------------\n");	
	printf("\n\n");
	
	//Max Weight First
	printf("\n------Max Weight First-------\n");	
	count = 0;
	max_profit = 0;
	total_weight = 0;
	for (i = 0; i < number_of_elements; i++){
		items_added[i] = -1;
	}
	for (i = 0; i < number_of_elements; i++){
		temp_weights[i] = weights[i];
		temp_profits[i] = profits[i];
   	} 
	while(total_weight <= W){
		temp_weight = 0;
		for(i = 0; i < number_of_elements; i++){
			if(temp_weight < temp_weights[i]){
				temp_weight = temp_weights[i];
				temp_profit = temp_profits[i];
				max_item = i;
			}
		}
		total_weight += temp_weights[max_item];
		if(total_weight <= W){
			max_profit += temp_profit;
			items_added[count] = max_item;
			temp_profits[max_item] = -1;
			temp_weights[max_item] = -1;
			count++;
		}else{
			total_weight -= temp_weights[max_item];		
			break;	
		}
	}

	printf("-----Items in Knacksack-------\n");
	for (i = 0; i < number_of_elements; i++){
		if(items_added[i] != -1)
			printf("item - %d profit - %d weight - %d\n",items_added[i], profits[items_added[i]], weights[items_added[i]]);		
	}
	printf("-----------------------------\n");	
	printf("\nTotal profit %d, Total weight %d \n",max_profit, total_weight);	
	printf("-----------------------------\n");	
	printf("\n\n");



	//Max Benefit per Unit item
	printf("\n----Max Benefit per Unit Item----\n");	
	count = 0;
	max_profit = 0;
	total_weight = 0;
	for (i = 0; i < number_of_elements; i++){
		items_added[i] = -1;
	}
	for (i = 0; i < number_of_elements; i++){
		temp_weights[i] = weights[i];
		temp_profits[i] = profits[i];
		benefit[i] = temp_profits[i]/temp_weights[i];
   	}
	 
	while(total_weight <= W){
		temp_benefit = -1;
		for(i = 0; i < number_of_elements; i++){
			if(temp_benefit < benefit[i]){
				temp_benefit = benefit[i];
				temp_weight = temp_weights[i];
				temp_profit = temp_profits[i];
				max_item = i;
			}
		}
		total_weight += temp_weights[max_item];
		if(total_weight <= W){
			max_profit += temp_profit;
			items_added[count] = max_item;
			temp_profits[max_item] = -1;
			temp_weights[max_item] = -1;
			benefit[max_item] = -1;
			count++;
		}else{
			total_weight -= temp_weights[max_item];		
			break;	
		}
		count++;	
	}
	
	printf("-----Items in Knacksack-------\n");
	for (i = 0; i < number_of_elements; i++){
		if(items_added[i] != -1)
			printf("item - %d profit - %d weight - %d\n",items_added[i], profits[items_added[i]], weights[items_added[i]]);		
	}
	printf("-----------------------------\n");	
	printf("\nTotal profit %d, Total weight %d \n",max_profit, total_weight);	
	printf("-----------------------------\n");	

	
	return 0;
}

