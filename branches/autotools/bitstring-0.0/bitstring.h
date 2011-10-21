#ifndef BSTR_H
#define BSTR_H

#include <stdio.h> //FILE
#include <stddef.h> //size_t
#include <inttypes.h> //uintmax_t intmax_t

/*
@desc Common sizes.
@note Size in a bitstring context is in bits rather than in bytes. When size in
	bytes is used it's explicitly stated as such.
*/
#define SZ_BYTE 8
#define SZ_LONG SZ_BYTE*sizeof(long)
#define SZ_SHORT SZ_BYTE*sizeof(short)
#define SZ_CHAR SZ_BYTE*sizeof(char)
size_t get_native_long_int_sz();
/*
@desc Byte/bit order enum. Used to specify byte/bit ordering properities of 
	certain data types.
@note ORD_NONE is for bit-sized data rather than byte-sized data. It designates
	that a binary representation of a certain data type does not have a 
	byte ordering property, only bit ordering.
*/
enum order{
	ORD_BE,
	ORD_LE,
	ORD_NONE
};
typedef enum order order_t;
order_t get_native_byte_order();
order_t get_native_bit_order();

/*
@desc Native byte/bit ordering macros.
*/
#define ORD_NAT_BYTE get_native_byte_order()
#define ORD_NAT_BIT get_native_bit_order()

/*
@desc Floating point representation enum.
*/
enum fprep{
	FP_IEEE754,
	FP_IBM, //not supported
	FP_CRAY, //not supported
	FP_VAX //not supported
};
typedef enum fprep fprep_t;
fprep_t get_native_fp_rep();

/*
@desc Type definitions for bitstring input values. Bitstring library provides
	these data type apstractions to it's users.
*/
typedef uintmax_t bstr_uint_t;
typedef intmax_t bstr_sint_t;
typedef double bstr_fp_t;

/*
@desc Used internally for forward allocation of bitstring internal buffer.
*/
#define BSTR_DATA_SZ 128

/*
@desc Bitstring data type.
*/
struct bitstring{
	char *data;
	size_t size;
	size_t alloc_size_bytes;
	};
typedef struct bitstring bitstring_t;
typedef bitstring_t* pbitstring_t;

/*******************************************************************************
*	Bitstring API.
*/

/*
@desc Initializes the bitstring library. Should be called before lib usage.
@note The assumption is that bitstrings are running on a big endian bit machines.
*/
void bitstring_lib_init(void);

/*
@desc Bitstring constructor.
*/
pbitstring_t bitstring_new(void);

/*
@desc Bitstring destructor.
*/
void bitstring_del(pbitstring_t pbs);

/*
@desc Bitstring setter. Handles allocation and error handling.
@note Makes internal copy of 'data'.
*/
pbitstring_t bitstring_set(pbitstring_t pbs, void* data, size_t size);

/*
@desc Bitstring copy.
*/
pbitstring_t bitstring_copy(pbitstring_t pbs_src);

/*
@desc Get a bit value from a 'pos'.
@note Positions are indexed starting with 0. Assume native big endian bit order.
*/
char bitstring_get_bit(pbitstring_t pbs, unsigned int pos);

/*
@desc Appends a single bit onto a bitstring.
@note Assume native big endian bit order.
*/
void bitstring_append_bit(pbitstring_t pbs, char append_bit);

/*
@desc Append a source bitstring 'src' onto a destination bitstring 'dst'.
*/
pbitstring_t bitstring_append(pbitstring_t dest, pbitstring_t src);

/*
@desc Concatenate two bitstrings into a new one.
*/
pbitstring_t bitstring_concat(pbitstring_t src1, pbitstring_t src2);

/*
@desc Prints a bitstring to a file.
*/
void bitstring_print(FILE *fp, pbitstring_t pbs);

/*
@desc Makes a new bitstring which represents a serialized unsigned integer value.
@arg 'val' Unsigned integer value which is to be serialized into a bitstring.
@arg 'size' Size of serialized object.
@arg 'byte_order' Byte ordering for serialized object.
	ORD_BE - big endian
	ORD_LE - little endian
	ORD_NONE - no byte ordering, the 'val' is to be serialized as bit-sized
@arg 'bit_order' Bit ordering for serialized object.
	ORD_BE - big endian
	ORD_LE - little endian
@note For byte-sized integers bit-ordering is performed per byte.
*/
pbitstring_t bitstring_new_uint(bstr_uint_t val, size_t size, order_t byte_order, order_t bit_order);

/*
@desc Makes a new bitstring which represents a serialized signed integer value.
*/
pbitstring_t bitstring_new_sint(bstr_sint_t val, size_t size, order_t byte_order, order_t bit_order);

/*
@desc Makes a new bitstring which represents a serialized floating point value.
@arg 'val' Floating point value which is to be serialized into a bitstring.
@arg 'size' Bitstring size (32, 64).
@arg 'fp_rep' Floating point representation (see header for list of possible
	values).
@note Currently IEEE754 format is supported with 32 and 64bit sizes.
*/
pbitstring_t bitstring_new_fp(bstr_fp_t val, size_t size, fprep_t fp_rep, order_t byte_order, order_t bit_order);

/*******************************************************************************
*	Basic operations used internally by the bitstring library. 
*	They can be usefull so I decided to export them.
*/

/*
@desc Converts byte order of memory pointed to by "pval".
@note Method is independent of data type you wish to convert byte order to
	(integers, floats, arrays).
*/
void conv_byte_order(void* pval, size_t size_bytes, order_t byte_order);

/*
@desc Converts bit order in a byte pointed to by 'pval'.
*/
void conv_bit_order(char* pval, order_t bit_order);

/*
@desc Converts byte order and bit order in each byte.
*/
void conv_byte_bit_order(char* pval, size_t size_bytes, order_t byte_order, order_t bit_order);

/*
@desc Shifts bits to the left in a byte array (little endian machines).
@example: val_mem = 0x45 | 0x23 | 0x01 ->(shift 3)-> val_mem = 0x29 | 0x18 | 0x08
*/
void shift_left_le(char* pval, size_t size_bytes, unsigned int shift_count);

/*
@desc Shifts bits to the left in a byte array (big endian machines).
@TODO: check
*/
void shift_left_be(char* pval, size_t size_bytes, unsigned int shift_count);

/*
@desc Shifts bits to the left in a byte array.
@note Checks for appropriate shift_left_xx to call by checking native ordering.
*/
void shift_left(char* pval, size_t size_bytes, unsigned int shift_count);

/*
@desc Shifts bits to the right in a byte array (little endian machines).
*/
void shift_right_le(char* pval, size_t size_bytes, unsigned int shift_count);

#endif //BSTR_H
