#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define VV  0x1D16

int main(int argc,char* argv[])
{
	float v = 50.0/100;

	float vv = v*VV;
	uint32_t x = (uint32_t)vv;


	printf("vv is %f\n",vv);
	printf("x is %d\n",x);



	return 0;

}
