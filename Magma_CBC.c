#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//PRF_GOSTR3411(u_int32_t SecurityParameters_enc_key_length, u_int32_t SecurityParameters_mac_key_length, u_int8_t SecurityParameters_fixed_iv_length);
//key_block = PRF(SecurityParameters.master_secret,"key expansion",SecurityParameters.server_random + SecurityParameters.client_random);

uint32_t L[32];
uint32_t R[32];
uint64_t Block[64];
uint32_t P0[16]=  {0x12,0x04,0x06,0x02,0x10,0x05,0x11,0x09,0x014,0x08,0x13,0x07,0x00,0x03,0x15,0x01};
uint32_t P1[16] = {0x06,0x08,0x02,0x03,0x09,0x10,0x05,0x12,0x01,0x14,0x4,0x07,0x11,0x13,0x00,0x15};
uint32_t P2[16] = {0x11,0x03,0x05,0x08,0x02,0x15,0x10,0x13,0x14,0x01,0x07,0x04,0x12,0x09,0x06,0x00};
uint32_t P4[16] = {0x07,0x15,0x05,0x10,0x08,0x01,0x06,0x13,0x00,0x09,0x03,0x014,0x11,0x04,0x02,0x12};
uint32_t P5[16] = {0x05,0x13,0x15,0x06,0x09,0x02,0x12,0x10,0x11,0x07,0x08,0x01,0x04,0x03,0x14,0x00};
uint32_t P6[16] = {0x08,0x14,0x02,0x05,0x06,0x09,0x01,0x12,0x15,0x04,0x11,0x00,0x13,0x10,0x03,0x07};
uint32_t P7[16] = {0x01,0x07,0x14,0x13,0x00,0x05,0x08,0x03,0x04,0x15,0x10,0x06,0x09,0x12,0x11,0x02};
uint32_t P3[16] = {0x12,0x08,0x02,0x01,0x13,0x04,0x15,0x06,0x07,0x00,0x10,0x05,0x03,0x14,0x09,0x11};

uint32_t T(uint32_t in){
    uint32_t out = 0;
    out |= (P7[in >> 7*4 & 0xF] << 7*4);
    out |= P6[in >> 6*4 & 0xF] << 6*4;
    out |= P5[in >> 5*4 & 0xF] << 5*4;
    out |= P4[in >> 4*4 & 0xF] << 4*4;
    out |= P3[in >> 3*4 & 0xF] << 3*4;
    out |= P2[in >> 2*4 & 0xF] << 2*4;
    out |= P1[in >> 4 & 0xF] << 4;
    out |= P0[in  & 0xF] ;
    return out;
}
uint32_t G(uint32_t k, uint32_t in) {
	//1000 0111 0110 0101 0100 0011 0010 0001  - 87654321
	//1111 1110 1101 1100 1011 1010 1001 1000 -  fedcba98
uint32_t s = k + in;
uint32_t x = T(s);
uint32_t l = (x << 11) | (x >> (32-11));
return l;
}

//uint32_t Gk(uint32_t k, uint32_t in) {
//	uint32_t s;
//	s = (i,(G(k,in)^i+1));
//	return s;
//}

//uint32_t Gk_so_zvezdoi(uint32_t k, uint32_t in) {
//	uint32_t l;
//	l = T((G(k,in)^(i+1)));
//	return l;
//}

//uint32_t key_shedule(char key[32]); //?? вопрос как теперь преобразовать нижестояющее в эту функцию

//char key[32];
//uint32_t rk[8];
//for (int i = 0; i < 8; i++) 
    //   rk[i] = key[4*i] << 24 | key[4*i + 1] << 16 | key[4*i + 2] << 8 | key[4*i + 3];	


uint64_t encryption(uint32_t *key, uint64_t block){
		uint32_t res;	
		uint32_t L = block >> 32;
	       	uint32_t R = block & 0xffffffff;
		printf("T - %lx\n",T(0xfdb97531));
	for(int i = 0; i < 32; i++) {
		res = T(R^key[i]); 
		printf("L - %lx\n", L);
	       printf("R - %lx\n",R);	
		printf("key - %lx\n",key[i]);
	       	res = (res << 11) | (res >> (32-11));
		printf("R^key - %lx\n", R^key[i]);
		printf("T(R^key) - %lx\n",T(R^key[i]));
		printf("res - %lx\n\n", res);
		res = res^L;
		L = R;
		R = res;
	}
       	return ((uint64_t) L << 32) | R; 
}
//uint32_t decryption(uint32_t key[], uint32_t L[], uint32_t R[]) {
//	for(int i = 32; i >0; i--) {
//		uint32_t left = R[i];
//		uint32_t right = G(key[i], T(R[i]^key[i]))^L[i];
//		}	
//	uint32_t result = *strcat(uint32_t *right, uint32_t *left);
//
//		return result;
//}









