/*Source: A1.c
  Purpose: Used to calculate the densities over given years 
  Input: the amount of years to be calculated as-well as the name of the file with densities
  Output: yearly calculations of densities until steady rate.
  Exit: 0 upon successful execution, when densities are at steady rate.
*/


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

//define constants for easy modification
#define tolorence 0.01
#define GRID_SIZE 12


int NextDensities(double fromGrid[GRID_SIZE][GRID_SIZE], double toGrid[GRID_SIZE][GRID_SIZE]);
int check(double a[GRID_SIZE][GRID_SIZE], double b[GRID_SIZE][GRID_SIZE]);
int main(int argc, char *argv[]){
	
	double a[GRID_SIZE][GRID_SIZE] = {};
	double c[GRID_SIZE][GRID_SIZE] = {};

	int arg1 = atoi(argv[1]);
	
	//checking for input errors and outputing to stderr
	if(argc != 3){
		fprintf(stderr,"Error: 2 correct arguments required for execution!\n");
		exit(1);
	} else if((strcmp(argv[1],"0") != 0 && arg1 == 0) || arg1 > 100 || arg1 < 0) {		
	 		fprintf(stderr,"Error: first argument needs to be an integer in range[0-100]!\n");
			exit(1);
	} else {
		FILE *file = fopen(argv[2], "r");
				
		if(file == 0){
			fprintf(stderr,"Could not open/find file: \"%s\"\n", argv[2]);
			exit(1);
		} else {		
			if(file){
				
				//reading the file and printing values that were read in
				printf("Read in these year 0 densities:\n");
				int i, j, x, y;
				for (i = 0; i < GRID_SIZE; i++)
       					for (j = 0; j < GRID_SIZE; j++)
           					if (fscanf(file, "%lf", &a[i][j]) == EOF)
               						return 1;
				
				for (x = 0; x < GRID_SIZE; x++) {
       					for (y = 0; y < GRID_SIZE; y++) {
           					printf("%.1lf ", a[x][y]);
       					 }
       					 printf("\n");
   				}
				
				//printing the grids as-well as calling the function
				for(i = 1; i <= arg1; i++){
					printf("\nYear %d densities:\n", i);
					int stop = NextDensities(a,c);
					for(x = 0; x < GRID_SIZE; x++){
                                        	for(y = 0; y < GRID_SIZE; y++){
                                                	printf("%.1lf ", c[x][y]);
                                        	}
                                       		printf("\n");
                                	}
					//when steady state is reached stop printning		
					if(stop == 1){
                         	               printf("\nsteady-state reached after %d years\n", i);
                                               return 0;
                                        }
				}
				fclose(file);
			}		
		}
	}
	return 0;
}

//mathematicians 2 grid approach
int NextDensities(double fromGrid[GRID_SIZE][GRID_SIZE], double toGrid[GRID_SIZE][GRID_SIZE]){
	int i, j, x;
	
	//copy fromGrid to toGrid(for border)
	for (i = 0; i < GRID_SIZE; i++)
		for (j = 0; j < GRID_SIZE; j++)
			toGrid[i][j] = fromGrid[i][j];

	//fill in the values using previouse grid.
	for(i = 1; i < GRID_SIZE-1; i++)
		for(j = 1; j < GRID_SIZE-1; j++)
			toGrid[i][j] = (fromGrid[i-1][j] + fromGrid[i][j-1] +
					fromGrid[i][j] + fromGrid[i][j+1] +
					fromGrid[i+1][j]) / (double) 5;	
	
	//check if steady rate is reached.
	if(check(toGrid, fromGrid) == 1){
		return 1;	
	}

	//make grid first grid equal second grid for the ability to recall func.
	for(i = 0; i < GRID_SIZE; i++)
		for(j = 0; j < GRID_SIZE; j++)
			fromGrid[i][j] = toGrid[i][j];	
	
}



//checking if steady rate is reached.
int check(double a[GRID_SIZE][GRID_SIZE], double b[GRID_SIZE][GRID_SIZE]){
	int i, j, x;
        for(i = 1; i < GRID_SIZE-1; i++)
                for(j = 1; j < GRID_SIZE-1; j++)
			if(fabs(a[i][j] - b[i][j]) > tolorence)
				return 0;
	return 1;
}			

