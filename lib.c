#include"lib.h"
#include<float.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>


void update(GWO *gwo,int iteration);
void update_wolves(GWO *gwo);
double update_a(int iteration);
double get_random(int M,int N);
double fitness(double *x);
double function(double *x);
void initialize(GWO *gwo);
int elitism(GWO *gwo,float found_maximum);


double get_random(int M,int N){

	return (M + rand() / (RAND_MAX / (N - M + 1) + 1));

}

double* optimize(GWO *gwo){
	double a;
	initialize(gwo);
	for(int i=0;i<MAX_IT;i++){	
		update_wolves(gwo);
		update(gwo,i);
	}
	
	printf("f(x,y) = %lf x = %lf y = %lf\n",function(gwo->alphaPos),gwo->alphaPos[0],gwo->alphaPos[1]);
	return gwo->alphaPos;


}

void initialize(GWO *gwo){
	for(int i=0;i<AGENT;i++){
			gwo->wolves[i][0] = get_random(-15,-5);
			gwo->wolves[i][1] = get_random(-3,3);
	}




	gwo->alpha = elitism(gwo,FLT_MAX);
	gwo->beta = elitism(gwo,fitness(gwo->wolves[gwo->alpha]));
	gwo->delta = elitism(gwo,fitness(gwo->wolves[gwo->beta]));
	
	memcpy(gwo->alphaPos,gwo->wolves[gwo->alpha],sizeof gwo->wolves[gwo->alpha]);
	memcpy(gwo->betaPos,gwo->wolves[gwo->beta],sizeof gwo->wolves[gwo->beta]);
	memcpy(gwo->deltaPos,gwo->wolves[gwo->delta],sizeof gwo->wolves[gwo->delta]);

}

int elitism(GWO *gwo,float found_maximum){
	// Inicializa o valor máximo com o primeiro valor de Result
	float maximum=fitness(gwo->wolves[0]);	
	int i, index_maximum=0;															
		for(i=1;i<AGENT;i++){
			if( fitness(gwo->wolves[i]) > maximum && fitness(gwo->wolves[i]) < found_maximum){
				// Guarda o índice do valor máximo
				index_maximum = i;
				// Atualiza o valor mínimo 
				maximum = fitness(gwo->wolves[i]);										
			}
		
	}
	// Retorna o índice do valor máximo (Corresponde ao indivíduo)
	return index_maximum;													
}


void update_wolves(GWO *gwo){
	double result;
	int aux_index_alpha;
	int aux_index_beta;
	int aux_index_delta;
	int i;
	for(i=0;i<AGENT;i++){
		result = fitness(gwo->wolves[i]);
		if(result > fitness(gwo->alphaPos)){
			aux_index_alpha = gwo->alpha;
			aux_index_beta = gwo->beta;
			
			memcpy(gwo->alphaPos,gwo->wolves[i],sizeof gwo->wolves[i]);
			memcpy(gwo->betaPos,gwo->wolves[aux_index_alpha],sizeof gwo->wolves[aux_index_alpha]);
			memcpy(gwo->deltaPos,gwo->wolves[aux_index_beta],sizeof gwo->wolves[aux_index_beta]);
			

		}
		else if(result > fitness(gwo->betaPos) && result < fitness(gwo->alphaPos)){
			aux_index_beta = gwo->beta;
			aux_index_delta = gwo->delta;
			
			memcpy(gwo->betaPos,gwo->wolves[i],sizeof gwo->wolves[i]);
			memcpy(gwo->deltaPos,gwo->wolves[aux_index_beta],sizeof gwo->wolves[aux_index_beta]);
			
		}
		else if (result > fitness(gwo->deltaPos) && result < fitness(gwo->betaPos)){
			gwo->delta = i;
			memcpy(gwo->deltaPos,gwo->wolves[i],sizeof gwo->wolves[i]);
		}
	}

}

double fitness(double *x){

	if(function(x) >= 0)
		return 1/(1+function(x));
	else 	
		return 1 + (-1*(function(x)));

}

double function(double *x){
	// return  100*pow(x[1] - pow(x[0],3),2) + pow(1 - x[0],2);		    // Leon Function
	//return pow(pow(x[0],2) + x[1]- 11,2) + pow(x[0] + pow(x[1],2) - 7,2);  // Himmelblau Function
	  return  pow(10,5)*pow(x[0],2) + pow(x[1],2) - pow(pow(x[0],2) + pow(x[1],2),2) + pow(10,-5)*pow(pow(x[0],2) + pow(x[1],2),4); 	//Deckkers-Aarts Function
	// return 0.26*(pow(x[0],2) + pow(x[1],2)) - 0.48*x[0]*x[1];                 // Matyas Function
	// return pow(x[0] + 10,2) + pow(x[1] + 10,2) + exp(-pow(x[0],2)-pow(x[1],2)); // Brent  Function
	// return pow(1.5 - x[0] + x[0]*x[1],2) + pow(2.25 - x[0] + x[0]*pow(x[1],2),2) + pow(2.625 -x[0] + x[0]*pow(x[1],3),2); //Beale Function
	// return 100*(sqrt(fabs(x[1] - 0.01*pow(x[0],2)))) + 0.01*fabs(x[0] + 10);	// Bukin N. 6 Function
	
}

double update_a(int iteration){
	return 2 -(iteration*(2/MAX_IT-1));

}	


void update(GWO *gwo,int iteration){
	srand(time(NULL));
	double a = update_a(iteration);
	for(int i=0;i<AGENT;i++){
		for(int j=0;j<DIMENSION;j++){
		    
			double r1 = (double) rand()/RAND_MAX;
			double r2 = (double) rand()/RAND_MAX;
			double a1 = 2*a*r1 - a;
			double c1 = 2*r2;
			double dAlpha = (c1*gwo->alphaPos[j] - gwo->wolves[i][j]);
			double x1 = (gwo->alphaPos[j] - (a1*dAlpha));
						

			r1 = (double) rand()/RAND_MAX;
			r2 = (double) rand()/RAND_MAX;
			double a2 = 2*a*r1 - a;
			double c2 = 2*r2;
			double dBeta = (c2*gwo->betaPos[j] - gwo->wolves[i][j]);
			double x2 = (gwo->betaPos[j] - (a2*dBeta));
		

			r1 = (double) rand()/RAND_MAX;
			r2 = (double) rand()/RAND_MAX;
			double a3 = 2*a*r1 - a;
			double c3 = 2*r2;
			double dDelta = (c3*gwo->deltaPos[j] - gwo->wolves[i][j]);
			double x3 = (gwo->deltaPos[j] - (a3*dDelta));

			gwo->wolves[i][j] = (x1+x2+x3)/3;

		}
	}

}
