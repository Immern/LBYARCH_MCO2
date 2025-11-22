#include <stdio.h>
#include <stdlib.h>
#include <time.h>
extern void asmhello();

float rand_float() {
    return (float)rand() / (float)RAND_MAX * 5.0f;  
}

int main()
{
	int input;
	printf("Enter the number of values for each vector: ");
	scanf("%d", &input);
	
	float *x1 = malloc(input * sizeof(float));
    float *x2 = malloc(input * sizeof(float));
    float *y1 = malloc(input * sizeof(float));
    float *y2 = malloc(input * sizeof(float));

    srand(time(NULL)); 
    int i;
    for (i = 0; i < input; i++) {
        x1[i] = rand_float();
        x2[i] = rand_float();
        y1[i] = rand_float();
        y2[i] = rand_float();
    }
    
//    testing
	double totalTime = 0.0;
	double time;
	double avgTime;
	clock_t startTime, endTime;

	for(i = 0; i< 30; i++){
		startTime = clock();
		asmhello(x1, x2, y1, y2);
		endTime = clock();
		
		time = (double)(endTime-startTime) / CLOCKS_PER_SEC;
		totalTime += time;
	}
	
	avgTime = totalTime/30.0;
	printf("Average ASM kernel time for n=%d: %f seconds\n", 30, avgTime);
	return 0;    
}
