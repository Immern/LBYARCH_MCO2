#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
extern void asmKernel();

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

float kernel_c_call(float* x1, float* x2, float* y1, float* y2, int input, float* z){
	float c_totalTime = 0.0;
	float c_time;
	clock_t c_startTime, c_endTime;
	int i;
	for(i = 0; i< 30; i++){
		c_startTime = clock();
		kernel_c_version(x1, x2, y1, y2, input, z);
		c_endTime = clock();
		
		c_time = (float)(c_endTime-c_startTime) / CLOCKS_PER_SEC;
		c_totalTime += c_time;
	}
	
	return c_totalTime;
}

float kernel_asm_call(float* x1, float* x2, float* y1, float* y2, int input, float* z){
	float asm_totalTime = 0.0;
	float asm_time;
	clock_t asm_startTime, asm_endTime;
	int i;
	for(i = 0; i< 30; i++){
		asm_startTime = clock();
		asmKernel(x1, x2, y1, y2, z, input);
		asm_endTime = clock();
		
		asm_time = (float)(asm_endTime-asm_startTime) / CLOCKS_PER_SEC;
		asm_totalTime += asm_time;
	}
	
	return asm_totalTime;
}

int main()
{
	int inputSize[3] = {20, 24, 26}; // decided to just use these as well for the seeds
	
	int inputs[3] = {pow(2, inputSize[0]), pow(2, inputSize[1]), pow(2, inputSize[2])};
	int out_loop;
	float c_totalTime[3];
	float asm_totalTime[3];
	int i;
	for(out_loop=0; out_loop<3; out_loop++){
	
		float *x1 = malloc(inputs[out_loop] * sizeof(float));
	    float *x2 = malloc(inputs[out_loop] * sizeof(float));
	    float *y1 = malloc(inputs[out_loop] * sizeof(float));
	    float *y2 = malloc(inputs[out_loop] * sizeof(float));
		float *z_c = malloc(inputs[out_loop] * sizeof(float));
		float *z_asm = malloc(inputs[out_loop] * sizeof(float));
		
	    srand(inputSize[out_loop]); 
	    for (i = 0; i < inputs[out_loop]; i++) {
	        x1[i] = rand_float();
	        x2[i] = rand_float();
	        y1[i] = rand_float();
	        y2[i] = rand_float();
	    }
	    
		/* =================== C KERNEL VERSION ===================*/
		printf("============================= 30 runs of the same inputs for the C KERNEL Version for 2^%d Inputs =============================\n", inputSize[out_loop]);
		c_totalTime[out_loop] = kernel_c_call(x1, x2, y1, y2, inputs[out_loop], z_c);
		/* =================== ASM KERNEL VERSION ===================*/
		printf("============================= 30 runs of the same inputs for the ASM KERNEL Version for 2^%d Inputs =============================\n", inputSize[out_loop]);
		asm_totalTime[out_loop] = kernel_asm_call(x1, x2, y1, y2, inputs[out_loop], z_asm);
		
		free(x1);
        free(x2);
        free(y1);
        free(y2);
        free(z_c);
        free(z_asm);
	}
	
	float c_avgTime[3];
	float asm_avgTime[3];
		
	for(i=0; i<3; i++){
		c_avgTime[i] = c_totalTime[i]/30.0;
		asm_avgTime[i] = asm_totalTime[i]/30.0;	
		printf("Average C kernel time for n=%d: %f seconds\n", 30, c_avgTime[i]);
		printf("Average ASM kernel time for n=%d: %f seconds\n\n", 30, asm_avgTime[i]);
	}
	return 0;    
}
