#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int tile_count = 1;//tile title_count

//Method to print the grid
int print(int size, int grid[][size]){
	int i = 0, j = 0;
	printf("\nTrimino Tile: \n");
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			if(grid[i][j] != -1){
				printf("%d\t",grid[i][j]);
			}else{
				printf("x\t");
			}
		}
		printf("\n");
	}
}

//Method to do recursive calls for filling up with tiles
int triminoRec(int size, int actualSize, int grid[][actualSize], int row, int col, int holeRow, int holeCol){
	int i = 0, j = 0, subsize = 0;
	if(size == 2){
		//base case. Fill the other parts with tiles leaving the hole
		for(i = 0; i < size; i++){
			for(j = 0; j < size; j++){
				if(grid[row + i][col + j] == 0){
					grid[row + i][col + j] = tile_count;				
				}
			}
		}
		tile_count++;
	}else{
		subsize = size/2;

		if(holeRow < row + subsize && holeCol < col + subsize){  //hole in top left
	
			triminoRec(subsize, actualSize, grid, row, col, holeRow, holeCol);

			//center tile
			grid[row + subsize][col + subsize - 1] = tile_count;
			grid[row + subsize][col + subsize] = tile_count;
			grid[row + subsize - 1][col + subsize] = tile_count;

			tile_count++;
		
			triminoRec(subsize, actualSize, grid, row, col + subsize, holeRow, holeCol);
			triminoRec(subsize, actualSize, grid, row + subsize, col, holeRow, holeCol);
			triminoRec(subsize, actualSize, grid, row + subsize, col + subsize, holeRow, holeCol);
		
		}else if(holeRow < row + subsize && holeCol >= col + subsize){ //hole in top right
		
			triminoRec(subsize, actualSize, grid, row, col + subsize, holeRow, holeCol);
			
			//center tile
			grid[row + subsize][col + subsize - 1] = tile_count;
			grid[row + subsize][col + subsize] = tile_count;
			grid[row + subsize - 1][col + subsize - 1] = tile_count;

			tile_count++;
				
			triminoRec(subsize, actualSize, grid, row, col, holeRow, holeCol);
			triminoRec(subsize, actualSize, grid, row + subsize, col, holeRow, holeCol);
			triminoRec(subsize, actualSize, grid, row + subsize, col + subsize, holeRow, holeCol);
		
		}else if(holeRow >= row + subsize && holeCol < col + subsize){ //hole in bot left
			
			triminoRec(subsize, actualSize, grid, row + subsize, col, holeRow, holeCol);

			//center tile
			grid[row + subsize - 1][col + subsize] = tile_count;
			grid[row + subsize][col + subsize] = tile_count;
			grid[row + subsize - 1][col + subsize - 1] = tile_count;

			tile_count++;
				
			triminoRec(subsize, actualSize, grid, row, col, holeRow, holeCol);
			triminoRec(subsize, actualSize, grid, row, col + subsize, holeRow, holeCol);
			triminoRec(subsize, actualSize, grid, row + subsize, col + subsize, holeRow, holeCol);
		
		}else{ //hole in bot right
		
			triminoRec(subsize, actualSize, grid, row + subsize, col + subsize, holeRow, holeCol);

			//center tile
			grid[row + subsize - 1][col + subsize] = tile_count;
			grid[row + subsize][col + subsize -1] = tile_count; 
			grid[row + subsize - 1][col + subsize - 1] = tile_count;

			tile_count++;
				
			triminoRec(subsize, actualSize, grid, row + subsize, col, holeRow, holeCol);
			triminoRec(subsize, actualSize, grid, row, col + subsize, holeRow, holeCol);
			triminoRec(subsize, actualSize, grid, row, col, holeRow, holeCol);
		}
	}
	return 0;
}

//Wrapper function to call recursive method
int triminoTile(int size, int grid[][size], int holeRow, int holeCol){
	triminoRec(size,size, grid, 0, 0, holeRow, holeCol);
	return 0;
}



int main(int argc, char *argv[]){
	int k = 0, holeRowNum = 0, holeColNum = 0;
	int maxSize = 0;
	
	if(argv[1] == NULL || atoi(argv[1]) < 1){
		printf("Minimum value of k should be 1. Exitting now.. \n");
		exit(0);
	}
	
	k = atoi(argv[1]);
	maxSize = pow(2, k);
	holeRowNum = atoi(argv[2]);
	holeColNum = atoi(argv[3]);
	
	if(holeRowNum >= maxSize || holeColNum >= maxSize){
		printf("Please enter value of hole position less the total size i.e. 2 power k. Exitting now.. \n");
		exit(0);
	}

	int grid[maxSize][maxSize];
	memset(grid, 0.0, sizeof(grid[0][0]) * maxSize * maxSize);
	grid[holeRowNum][holeColNum] = -1;

	triminoTile(maxSize, grid, holeRowNum, holeColNum);
	print(maxSize, grid);

	return 0;
}
