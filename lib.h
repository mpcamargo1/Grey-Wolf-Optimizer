#ifndef LIB_H
#define LIB_H

#include<stdio.h>

#define AGENT 		50
#define DIMENSION	2
#define MAX_IT 	1000

typedef struct gwo{
        int alpha;
	int beta;
	int delta;
	double wolves[AGENT][DIMENSION];
	double alphaPos[DIMENSION];
	double betaPos[DIMENSION];
	double deltaPos[DIMENSION];

}GWO;

double* optimize(GWO *gwo);
void update_wolves(GWO *gwo);

#endif // LIB_H_
