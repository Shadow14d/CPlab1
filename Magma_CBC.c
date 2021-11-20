#include <stdio.h>
#include <stdlib.h>

PRF_GOSTR3411(u_int32_t SecurityParameters_enc_key_length, u_int32_t SecurityParameters_mac_key_length, u_int8_t SecurityParameters_fixed_iv_length);
//key_block = PRF(SecurityParameters.master_secret,"key expansion",SecurityParameters.server_random + SecurityParameters.client_random);
u_int32_t L[32];
u_int32_t R[32];
for(int i = 0; i < 32; i++) {
	L[i+1]=R[i] xor f(
