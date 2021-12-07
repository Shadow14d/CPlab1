#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include "Magma_CBC.c"
//uint32_t key[32];
//uint64_t block[64];

#define BUFF_SIZE 64

uint64_t buff[BUFF_SIZE];
uint

int main(){
	uint32_t key[32] = {0xffeeddcc, 0xbbaa9988,0x77665544,0x33221100,0xf0f1f2f3,0xf4f5f6f7,0xf8f9fafb,0xfcfdfeff,
		    0xffeeddcc, 0xbbaa9988,0x77665544,0x33221100,0xf0f1f2f3,0xf4f5f6f7,0xf8f9fafb,0xfcfdfeff,
                    0xffeeddcc, 0xbbaa9988,0x77665544,0x33221100,0xf0f1f2f3,0xf4f5f6f7,0xf8f9fafb,0xfcfdfeff,
                    0xfcfdfeff, 0xf8f9fafb,0xf4f5f6f7,0xf0f1f2f3,0x33221100,0x77665544,0xbbaa9988,0xffeeddcc};

	uint32_t key_rev[32] = {0xffeeddcc,0xbbaa9988,0x77665544,0x33221100,0xf0f1f2f3,0xf4f5f6f7,0xf8f9fafb,0xfcfdfeff,
                        0xfcfdfeff, 0xf8f9fafb,0xf4f5f6f7,0xf0f1f2f3,0x33221100,0x77665544,0xbbaa9988,0xffeeddcc,
                        0xfcfdfeff, 0xf8f9fafb,0xf4f5f6f7,0xf0f1f2f3,0x33221100,0x77665544,0xbbaa9988,0xffeeddcc,
	   	        0xfcfdfeff, 0xf8f9fafb,0xf4f5f6f7,0xf0f1f2f3,0x33221100,0x77665544,0xbbaa9988,0xffeeddcc};
	uint32_t rk[8];

	printf("%lx\n", encryption(&key, 0xfedcba9876543210));
	printf("%lx\n", decryption(&key_rev, 0x4ee901e5c2d8ca3d));

	FILE *fp = fopen("file_dima", "wb");

	if ((fp = fopen(name, "r")) == NULL)
  	{
    		printf("Не удалось открыть файл");
  		  return 1;
  	}

	key_schedule(&rk, &key);
	while (!feof(fp)) {
		fread(&buffer, sizeof(uint64_t), BUFF_SIZE, fp)
		CBCencrypt(&buffer, r
  	}


return 0;
}
