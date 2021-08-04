#include<stdio.h>
#include<stdlib.h>
#include"lib.h"

void printSolution(double *solution);

int main(void){
	GWO wolves;
	double *solution = optimize(&wolves);
	printSolution(solution);
	return 1;

}


void printSolution(double *solution){

	for(int i=0;i<DIMENSION;i++)
		printf("%lf ",solution[i]);
	printf("\n");


}
