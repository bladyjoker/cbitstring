#include <bitstring.h>
#include <string.h>
#include <stdio.h>

int main(){
	
	bitstring_lib_init();

	/*INT TEST, BYTE/BIT ORDERING*/
	fprintf(stdout, "INT TEST, BYTE/BIT ORDERING\n");

	pbitstring_t pbs1;
	
	for(int i=20; i<33; i++){
		pbs1 = bitstring_new_uint(0x12345, i, ORD_NONE, ORD_BE);
		bitstring_print(stdout, pbs1);
		bitstring_del(pbs1);
	}


	for(int i=20; i<33; i++){
		pbs1 = bitstring_new_uint(0x12345, i, ORD_NONE, ORD_LE);
		bitstring_print(stdout, pbs1);
		bitstring_del(pbs1);
	}
	
	
	pbs1 = bitstring_new_uint(-2, 13, ORD_NONE, ORD_BE);
	bitstring_print(stdout, pbs1);
	bitstring_del(pbs1);
	
	pbs1 = bitstring_new_uint(-2, 13, ORD_NONE, ORD_LE);
	bitstring_print(stdout, pbs1);
	bitstring_del(pbs1);
	
	
	pbs1 = bitstring_new_uint(0x1234, SZ_SHORT, ORD_LE, ORD_BE);
	bitstring_print(stdout, pbs1);
	bitstring_del(pbs1);
	pbs1 = bitstring_new_uint(0x1234, SZ_SHORT, ORD_BE, ORD_BE);
	bitstring_print(stdout, pbs1);
	bitstring_del(pbs1);
	pbs1 = bitstring_new_uint(0x1234, SZ_SHORT, ORD_LE, ORD_LE);
	bitstring_print(stdout, pbs1);
	bitstring_del(pbs1);
	pbs1 = bitstring_new_uint(0x1234, SZ_SHORT, ORD_BE, ORD_LE);
	bitstring_print(stdout, pbs1);
	bitstring_del(pbs1);
		
	/*FLOATING POINT TEST*/
	fprintf(stdout, "FP TEST:\n");
	pbs1 = bitstring_new_fp(3.14, SZ_LONG, FP_IEEE754, ORD_LE, ORD_BE);
	bitstring_print(stdout, pbs1);
	fprintf(stdout, "%f\n", *((float*)pbs1->data));
	bitstring_del(pbs1);
	pbs1 = bitstring_new_fp(3.14, SZ_LONG, FP_IEEE754, ORD_BE, ORD_BE);
	bitstring_print(stdout, pbs1);
	fprintf(stdout, "%f\n", *((float*)pbs1->data));
	bitstring_del(pbs1);
	pbs1 = bitstring_new_fp(3.14, SZ_LONG, FP_IEEE754, ORD_LE, ORD_LE);
	bitstring_print(stdout, pbs1);
	fprintf(stdout, "%f\n", *((float*)pbs1->data));
	bitstring_del(pbs1);
	pbs1 = bitstring_new_fp(3.14, SZ_LONG, FP_IEEE754, ORD_BE, ORD_LE);
	bitstring_print(stdout, pbs1);
	fprintf(stdout, "%f\n", *((float*)pbs1->data));
	bitstring_del(pbs1);
	
	/*APPEND, CONCAT, ALLOC TEST*/
	fprintf(stdout, "APPEND AND ALLOC TEST\n");
	pbs1 = bitstring_new_uint(1, 13, ORD_NONE, ORD_BE);
	pbitstring_t pbs2 = bitstring_new_sint(-2, 13, ORD_NONE, ORD_BE);
	for(int i=0; i<10; i++){
		bitstring_print(stdout, pbs1);
		bitstring_append(pbs1, pbs2);
	}
	bitstring_del(pbs1);
	bitstring_del(pbs2);
	
	/*APPEND BIT*/
	pbs1 = bitstring_new_uint(255, 8, ORD_LE, ORD_LE);
	for(int i=0; i<=8; i++){
		bitstring_print(stdout, pbs1);
		bitstring_append_bit(pbs1, 0);
	}
	bitstring_del(pbs1);
	
	pbs1 = bitstring_new_uint(0, 8, ORD_LE, ORD_BE);
	pbs2 = bitstring_new_uint(255, 8, ORD_LE, ORD_BE);
	pbitstring_t pbs3 = bitstring_concat(pbs1, pbs2);
	bitstring_print(stdout, pbs3);
	bitstring_del(pbs1);
	bitstring_del(pbs2);
	bitstring_del(pbs3);
		
	return 0;
}
