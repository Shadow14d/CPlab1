#include <stdio.h>
#include <stdlib.h>
#include <string.h>


uint32_t L[32];
uint32_t R[32];
uint64_t Block[64];

uint32_t P0[16] = {12,4,6,2,10,5,11,9,14,8,13,7,0,3,15,1};
uint32_t P1[16] = {6,8,2,3,9,10,5,12,1,14,4,7,11,13,0,15};
uint32_t P2[16] = {11,3,5,8,2,15,10,13,14,1,7,4,12,9,6,0};
uint32_t P3[16] = {12,8,2,1,13,4,15,6,7,0,10,5,3,14,9,11};
uint32_t P4[16] = {7,15,5,10,8,1,6,13,0,9,3,14,11,4,2,12};
uint32_t P5[16] = {5,13,15,6,9,2,12,10,11,7,8,1,4,3,14,0};
uint32_t P6[16] = {8,14,2,5,6,9,1,12,15,4,11,0,13,10,3,7};
uint32_t P7[16] = {1,7,14,13,0,5,8,3,4,15,10,6,9,12,11,2};



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

void key_shedule(uint32_t *rk, uint32_t *key) {	
	for (int i = 0; i < 8; i++) 
	      	rk[i] = key[4*i] << 24 | key[4*i + 1] << 16 | key[4*i + 2] << 8 | key[4*i + 3];	
}

uint64_t encryption(uint32_t *key, uint64_t block){
		uint32_t res;	
		uint32_t L = block >> 32;
	       	uint32_t R = block & 0xffffffff;
		printf("T - %lx\n",T(0xfdb97531));
	for(int i = 0; i < 24; i++) {
		res = T(R+key[i]); 
		printf("L - %08lx\n", L);
	       	printf("R - %08lx\n",R);	
		printf("key - %08lx\n",key[i]);
	       	res = (res << 11) | (res >> (32-11));
		printf("R^key - %08lx\n", R+key[i % 8]);
		printf("T(R^key) - %08lx\n",T(R+key[i]));
		printf("res - %08lx\n\n", res);
		res = res^L;
		L = R;
		R = res;
	}
	for(int i = 7; i >= 0; i--) {
		res = T(R+key[i]); 
		printf("L - %08lx\n", L);
	       printf("R - %08lx\n",R);	
		printf("key - %08lx\n",key[i]);
	       	res = (res << 11) | (res >> (32-11));
		printf("R^key - %08lx\n", R+key[i]);
		printf("T(R^key) - %08lx\n",T(R+key[i]));
		printf("res - %08lx\n\n", res);
		res = res^L;
		L = R;
		R = res;
	}
	L ^= R;
	R ^= L;
	L ^= R;
       	return ((uint64_t) L << 32) | R; 
}
uint64_t decryption(uint32_t *key_rev, uint64_t block) {
		uint32_t res;
		uint32_t L = block >> 32;
		uint32_t R = block & 0xffffffff;
                printf("T-rev - %lx\n",T(0xfdb97531));
        for(int i = 0; i < 32; i++) {
                res = T(R+key_rev[i]);
                printf("L-rev - %08lx\n", L);
                printf("R-rev - %08lx\n",R);
                printf("key_rev - %08lx\n",key_rev[i]);
                res = (res << 11) | (res >> (32-11));
                printf("R+rev_key - %08lx\n", R+key_rev[i]);
                printf("T(R+rev_key) - %08lx\n",T(R+key_rev[i]));
                printf("res-rev - %08lx\n\n", res);
                res = res^L;
                L = R;
                R = res;
        }
        L ^= R;
        R ^= L;
        L ^= R;
        return ((uint64_t) L << 32) | R;
}
uint64_t CBC_enc(uint64_t *C, uint64_t IV,uint64_t key, size_t size, uint64_t *P) {
	uint64_t C[0] = encrypt(rk, P[0]^IV);
	for(int i = 1; i < size; i++) {
		uint64_t tmp = C[i]^C[i-1];
		C[i] = encryption(key,tmp);
	}
	return C[i];
}


uint64_t CBC_dec(uint64_t IV, uint64_t rev_key uint64_t Block) {
	uint64_t C0 = IV;
	for(int i = 1; i < 64; i++) {
		uint64_t tmp = Block[i]^Block[i-1];
		Block[i] = decryption(rev_key, tmp);
	}
	return P[i];
}

//основные виды протоколов,протокол с нулевым разглашением
//


//uint64_t stribog256(uint64_t length) {
	
/*	uint16_t Sbox0[16] = {252, 238, 221, 17, 207, 110, 49, 22, 251, 196, 250, 218, 35, 197, 4, 77, 233};
	uint16_t Sbox1[16] = {119, 240, 219, 147, 46, 153, 186, 23, 54, 241, 187, 20, 205, 95, 193, 249};
	uint16_t Sbox2[16] = {24, 101, 90, 226, 92, 239,33, 129, 28, 60, 66, 139, 1, 142, 79, 5};
	uint16_t Sbox3[16] = {132, 2, 174, 227, 106, 143, 160, 6, 11, 237, 152, 127,212, 211, 31, 235};
	uint16_t Sbox4[16] = {52, 44, 81, 234, 200, 72, 171, 242, 42, 104, 162, 253, 58, 206, 204, 181};
	uint16_t Sbox5[16] = {112, 14, 86, 8, 12, 118, 18, 191, 114, 19, 71, 156, 183, 93, 135, 21};
	uint16_t Sbox6[16] = {161, 1,50, 41, 16, 123,154, 199, 243, 145, 120, 111, 157, 158, 178, 177, 50};
	uint16_t Sbox7[16] = {117, 25, 61, 255, 53, 138, 126, 109,84, 198, 128, 195, 189, 13, 87, 223};
	uint16_t Sbox8[16] = {245, 36, 169, 62, 168, 67, 201, 215, 121, 214, 246, 124,34, 185, 3, 224};
	uint16_t Sbox9[16] = {15, 236, 222, 122, 148, 176, 188, 220, 232, 40, 80, 78, 51, 10, 74, 167};
	uint16_t Sbox10[16] = {151,96, 115, 30, 0, 98, 68, 26, 184, 56, 130, 100, 159, 38, 65, 173};
	uint16_t Sbox11[16] = {69, 70, 146, 39, 94, 85, 47,140, 163, 165, 125, 105, 213, 149, 59, 7};
	uint16_t Sbox12[16] = {88, 179, 64, 134, 172, 29, 247, 48, 55, 107, 228,136, 217, 231, 137, 225};
	uint16_t Sbox13[16] = {27, 131, 73, 76, 63, 248, 254, 141, 83, 170, 144, 202, 216, 133, 97,32};
	uint16_t Sbox14[16] = {113, 103, 164, 45, 43, 9, 91, 203, 155, 37, 208, 190, 229, 108, 82, 89};
	uint16_t Sbox15[16] = {166, 116, 210,230, 244, 180, 192, 209, 102, 175, 194, 57, 75, 99, 182};

}

*/




