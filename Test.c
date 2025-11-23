#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
extern void asmhello();

float rand_float() {
    return (float)rand() / (float)RAND_MAX * 5.0f;  
}

void kernel_c_version(float* x1, float* x2, float* y1, float* y2, int input, float* z){
	int i;
	for(i = 0; i < input; i++) {
        float dx = x1[i] - x2[i];
        float dy = y1[i] - y2[i];

        float dx_sq = dx * dx;
        float dy_sq = dy * dy;

        float sum_sq = dx_sq + dy_sq;

        z[i] = sqrtf(sum_sq); 
    }
    printf("Z -> ");
    for(i=0; i < 10; i++){
    	if(i!=9){
    		printf("%lf, ", z[i]);
    	}
    	else{
    		printf("%lf\n", z[i]);
		}
	}
}

double kernel_c_call(float* x1, float* x2, float* y1, float* y2, int input, float* z){
	double c_totalTime = 0.0;
	double c_time;
	clock_t c_startTime, c_endTime;
	int i;
	for(i = 0; i< 30; i++){
		c_startTime = clock();
		kernel_c_version(x1, x2, y1, y2, input, z);
		c_endTime = clock();
		
		c_time = (double)(c_endTime-c_startTime) / CLOCKS_PER_SEC;
		c_totalTime += c_time;
	}
	
	return c_totalTime;
}

int main()
{
	int input;
	printf("Enter the number of values for each vector: ");
	scanf("%d", &input);
	input = pow(2, 26);
	float *x1 = malloc(input * sizeof(float));
    float *x2 = malloc(input * sizeof(float));
    float *y1 = malloc(input * sizeof(float));
    float *y2 = malloc(input * sizeof(float));
	float *z = malloc(input * sizeof(float));
	
    srand(time(NULL)); 
    int i;
    for (i = 0; i < input; i++) {
        x1[i] = rand_float();
        x2[i] = rand_float();
        y1[i] = rand_float();
        y2[i] = rand_float();
    }
    
/* =================== C KERNEL VERSION ===================*/
	printf("============================= 30 runs of the same inputs for the C KERNEL Version =============================\n");
	double c_totalTime;
	c_totalTime = kernel_c_call(x1, x2, y1, y2, pow(2, 20), z);
//	double c_totalTime = 0.0;
//	double c_time;
//	double c_avgTime;
//	clock_t c_startTime, c_endTime;
//	printf("============================= 30 runs of the same inputs for the C KERNEL Version =============================\n");
//	for(i = 0; i< 30; i++){
//		c_startTime = clock();
//		kernel_c_version(x1, x2, y1, y2, input, z);
//		c_endTime = clock();
//		
//		c_time = (double)(c_endTime-c_startTime) / CLOCKS_PER_SEC;
//		c_totalTime += c_time;
//	}
	
	
/* =================== ASM KERNEL VERSION ===================*/
	double asm_totalTime = 0.0;
	double asm_time;
	clock_t asm_startTime, asm_endTime;
	printf("============================= 30 runs of the same inputs for the ASM KERNEL Version =============================\n");
	for(i = 0; i< 30; i++){
		asm_startTime = clock();
		asmhello(x1, x2, y1, y2, z, input);
		asm_endTime = clock();
		
		asm_time = (double)(asm_endTime-asm_startTime) / CLOCKS_PER_SEC;
		asm_totalTime += asm_time;
	}
	
	
	double c_avgTime;
	c_avgTime = c_totalTime/30.0;
	double asm_avgTime;
	asm_avgTime = asm_totalTime/30.0;
	printf("Average C kernel time for n=%d: %f seconds\n", 30, c_avgTime);
	printf("Average ASM kernel time for n=%d: %f seconds\n", 30, asm_avgTime);
	return 0;    
}
