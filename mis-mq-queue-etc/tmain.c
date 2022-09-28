#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union mt
{

	float v;
	uint8_t a[4];

};

enum me{ mea = 65538,meb};


int main()
{
	struct s
	{
		uint8_t state;
		uint8_t gap1;
		uint8_t gap2;
		uint8_t gap3;

		float fv;

	};
	struct s  *sv;



	printf("sizeof struct s is %d\n",sizeof(struct s));
	return 0;

	//uint8_t	buf[5] = {0x00,0xff,0xff,0xff,0xff};
	uint8_t	buf[5] = {0x00,0x00,0x00,0x00,0x00};
	sv = (struct s*)buf;

	printf("fv is %f\n",sv->fv);

	return 0;




	union	mt   x;
	x.a[0]=0xff;
	x.a[1]=0xff;
	x.a[2]=0xff;
	x.a[3]=0xff;

	x.v= -1.0;


	//printf("v is %f\n",x.v);
	printf("a[0] is %2x\n",x.a[0]);
	printf("a[1] is %2x\n",x.a[1]);
	printf("a[2] is %2x\n",x.a[2]);
	printf("a[3] is %2x\n",x.a[3]);
	return 0;


}

