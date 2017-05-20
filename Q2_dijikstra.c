#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define V 5

//Finding the shortest distance vertex
int get_shortest_distance_vertex(int total_distance[], int visited[]){
	int min = 100000, min_vertex, j;
	for(j = 0; j < V; j++){
		if(visited[j] == 0 && total_distance[j] <= min){
			min = total_distance[j];
			min_vertex = j;
		}
	}	
	return min_vertex;
}

//Dijikstra's Algorithm
void dijikstra(int matrix[V][V], int src){
	int total_distance[V], i = 0, j = 0, count = 0, min_vertex;
	int visited[V];
	for(i = 0; i < V; i++){
		total_distance[i] = 100000;
		visited[i] = 0;
	}
	
	total_distance[src] = 0;

	for(i = 0; i < V; i++){
		min_vertex = get_shortest_distance_vertex(total_distance, visited);
		visited[min_vertex] = 1;
		for(j = 0; j < V; j++){
			if(visited[j] == 0 && matrix[min_vertex][j]!= -99 
				&& total_distance[min_vertex] != 10000
				&& total_distance[min_vertex] + matrix[min_vertex][j] < total_distance[j]){
				total_distance[j] = total_distance[min_vertex] + matrix[min_vertex][j];
			}
		}
	}
	printf("Vertex \t\t Distance\n");
	for(i = 0; i < V; i++){
		printf("%d \t\t %d\n", i, total_distance[i]);
	}
}

int main(){
	char line[100];
	FILE *fp;
	int matrix[V][V];
	int count = 0;
	//Reading file
	fp = fopen("matrix_input.txt","r");
	if(fp == NULL){
		printf("File not found.. \n");
		exit(0);
	}
	while(fgets(line, 100, fp) != NULL){
		sscanf(line,"%d, %d, %d, %d, %d", &matrix[count][0], &matrix[count][1], &matrix[count][2], &matrix[count][3], &matrix[count][4]);
		count++;
	}	
	fclose(fp);
	
	dijikstra(matrix, 0);
	return 0;
}
