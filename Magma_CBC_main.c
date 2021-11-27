#include <stdio.h>
#include <inttypes.h>
uint32_t key[32];
uint32_t L[32];
uint32_t R[32];

uint32_t encryption(uint32_t key[32],uint32_t L[32],uint32_t R[32]);
	int main(){
uint32_t key[32] = {0x12,0x04,0x06,0x02,0x10,0x05,0x11,0x09,0x014,0x08,0x13,0x07,0x00,0x03,0x15,0x01};
	uint32_t L[32];
uint32_t R[32];
	printf(encryption(key[32],L[32],R[32]), "%llu");


return 0;
}
