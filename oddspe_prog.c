#include <stdio.h>
#include <spu_intrisics.h>

int A[32] __attribute__((aligned(16)))={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,33,34};
int B[32] __attribute__((aligned(16)));
int E[32] __attribute__((aligned(16)));

int i,j,s,t;

int main(unsigned long long spe, unsigned long long argv, unsigned long long envp)
{
	__vector signed int *vA=(__vector signed int *)A;
	__vector signed int *vB=(__vector signed int *)B;
	__vector signed int vC[8];
	__vector signed int vD[8];
	__vector signed int *vE=(__vector signed int *)E;

	
	__vector unsigned char vpos1={0x00,0x01,0x02,0x03,
				       0x04,0x05,0x06,0x07,
				       0x10,0x11,0x12,0x13,
				       0x18,0x19,0x1a,0x1b};
	__vector unsigned char vpos2={0x08,0x09,0x0a,0x0b,
				       0x14,0x15,0x16,0x17,
				       0x0c,0x0d,0x0e,0x0f,
				       0x1c,0x1d,0x1e,0x1f};	
	__vector unsigned char vpos3={0x00,0x01,0x02,0x03,
				       0x10,0x11,0x12,0x13,
				       0x08,0x09,0x0a,0x0b,
				       0x0c,0x0d,0x0e,0x0f};
	__vector unsigned char vpos4={0x04,0x05,0x06,0x07,
				       0x14,0x15,0x16,0x17,
				       0x18,0x19,0x1a,0x1b,
				       0x1c,0x1d,0x1e,0x1f};		

	vC[0]=spu_shuffle(vA[0],vA[1],vpos1);
        vC[1]=spu_shuffle(vA[0],vA[1],vpos2);
	vC[2]=spu_shuffle(vA[2],vA[3],vpos1);
        vC[3]=spu_shuffle(vA[2],vA[3],vpos2);
 	vC[4]=spu_shuffle(vA[4],vA[5],vpos1);
	vC[5]=spu_shuffle(vA[4],vA[5],vpos2);
 	vC[6]=spu_shuffle(vA[6],vA[7],vpos1);
 	vC[7]=spu_shuffle(vA[6],vA[7],vpos2);

	vB[0]=spu_shuffle(vC[0],vC[1],vpos3);
	vB[1]=spu_shuffle(vC[0],vC[1],vpos4);
	vB[2]=spu_shuffle(vC[2],vC[3],vpos3);
	vB[3]=spu_shuffle(vC[2],vC[3],vpos4);
	vB[4]=spu_shuffle(vC[4],vC[5],vpos3);
	vB[5]=spu_shuffle(vC[4],vC[5],vpos4);
	vB[6]=spu_shuffle(vC[6],vC[7],vpos3);
	vB[7]=spu_shuffle(vC[6],vC[7],vpos4);

	//This is a for loop to print the odd number matrix
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			printf("%2d\t",B[i*8+j]);
		}
		printf("\n");

	}
	
	__vector unsigned char vpos5={0x00,0x01,0x02,0x03,
				       0x18,0x19,0x1a,0x1b,
				       0x14,0x15,0x16,0x17,
				       0x0c,0x0d,0x0e,0x0f};
	__vector unsigned char vpos6={0x10,0x11,0x12,0x13,
				       0x08,0x09,0x0a,0x0b,
				       0x04,0x05,0x06,0x07,
				       0x1c,0x1d,0x1e,0x1f};	
	__vector unsigned char vpos7={0x00,0x01,0x02,0x03,
				       0x14,0x15,0x16,0x17,
				       0x18,0x19,0x1a,0x1b,
				       0x0c,0x0d,0x0e,0x0f};
	__vector unsigned char vpos8={0x10,0x11,0x12,0x13,
				       0x04,0x05,0x06,0x07,
				       0x08,0x09,0x0a,0x0b,
				       0x1c,0x1d,0x1e,0x1f};		


	vD[0]=vB[0];
	vD[1]=spu_shuffle(vB[1],vB[3],vpos5);
	vD[2]=vB[2];
	vD[3]=spu_shuffle(vB[1],vB[3],vpos6);
	vD[4]=vB[4];
	vD[5]=spu_shuffle(vB[5],vB[7],vpos5);
	vD[6]=vB[6];
	vD[7]=spu_shuffle(vB[5],vB[7],vpos6);

	vE[0]=vB[0];
	vE[1]=spu_shuffle(vD[0],vD[1],vpos7);
	vE[2]=vB[2];
	vE[3]=spu_shuffle(vD[0],vD[1],vpos8);
	vE[4]=vB[4];
	vE[5]=spu_shuffle(vD[2],vD[3],vpos7);
	vE[6]=vB[6];
	vE[7]=spu_shuffle(vD[2],vD[3],vpos8);


	//This is a for loop to print the even number matrix
	for(s=0;s<4;s++)
	{
		for(t=4;t<8;t++)
		{
			printf("%2d\t",E[s*8+t]);
		}
		printf("\n");

	}
	return 0;

}
