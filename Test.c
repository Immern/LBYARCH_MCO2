#include <stdio.h>
extern void asmhello();

int main()
{
	float x1[4] = {1.5, 4.0, 3.5, 2.0};
	float x2[4] = {3.0, 2.5, 2.5, 1.0};
	float y1[4] = {4.0, 3.0, 3.5, 3.0};
	float y2[4] = {2.0, 2.5, 1.0, 1.5};
	
//	float* space = (float*)malloc(12*sizeof(float));
	
	asmhello(x1, x2, y1, y2);
	
	return 0;    
}
