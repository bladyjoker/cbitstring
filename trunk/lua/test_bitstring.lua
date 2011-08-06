require("bitstring")

ORD_NONE = 2;
ORD_BE = 1;
ORD_LE = 0;

SZ_BYTE = 8
SZ_LONG  = SZ_BYTE*4
SZ_SHORT  = SZ_BYTE*2
SZ_CHAR  = SZ_BYTE*1

FP_IEEE754 = 0
FP_IBM  = 1
FP_CRAY = 2
FP_VAX  = 3

--INT TEST, BYTE/BIT ORDERING*/
print("INT TEST, BYTE/BIT ORDERING");

for i=20,32,1 do
	pbs1 = bitstring.new_uint(0x12345, i, ORD_NONE, ORD_BE);
	print(pbs1);
end

for i=20,32,1 do
	pbs1 = bitstring.new_uint(0x12345, i, ORD_NONE, ORD_LE);
	print(pbs1);
end

pbs1 = bitstring.new_uint(-2, 13, ORD_NONE, ORD_BE);
print(pbs1);

pbs1 = bitstring.new_uint(-2, 13, ORD_NONE, ORD_LE);
print(pbs1);

pbs1 = bitstring.new_uint(0x1234, SZ_SHORT, ORD_LE, ORD_BE);
print(pbs1);
pbs1 = bitstring.new_uint(0x1234, SZ_SHORT, ORD_BE, ORD_BE);
print(pbs1);
pbs1 = bitstring.new_uint(0x1234, SZ_SHORT, ORD_LE, ORD_LE);
print(pbs1);
pbs1 = bitstring.new_uint(0x1234, SZ_SHORT, ORD_BE, ORD_LE);
print(pbs1);

--FLOATING POINT TEST
print("FP TEST:");
pbs1 = bitstring.new_fp(3.14, SZ_LONG, FP_IEEE754, ORD_LE, ORD_BE);
print(pbs1);

pbs1 = bitstring.new_fp(3.14, SZ_LONG, FP_IEEE754, ORD_BE, ORD_BE);
print(pbs1);

pbs1 = bitstring.new_fp(3.14, SZ_LONG, FP_IEEE754, ORD_LE, ORD_LE);
print(pbs1);

pbs1 = bitstring.new_fp(3.14, SZ_LONG, FP_IEEE754, ORD_BE, ORD_LE);
print(pbs1);

--APPEND, CONCAT, ALLOC TEST
print("APPEND AND ALLOC TEST");
pbs1 = bitstring.new_uint(1, 13, ORD_NONE, ORD_BE);
pbs2 = bitstring.new_sint(-2, 13, ORD_NONE, ORD_BE);
for i=1,10,1 do
	print(pbs1);
	pbs1:append(pbs2);
end

--APPEND BIT
pbs1 = bitstring.new_uint(255, 8, ORD_LE, ORD_LE);
for i=1,8,1 do
	print(pbs1);
	pbs1:append_bit(0);
end

pbs1 = bitstring.new_uint(0, 8, ORD_LE, ORD_BE);
pbs2 = bitstring.new_uint(255, 8, ORD_LE, ORD_BE);
pbs3 = pbs1 .. pbs2;
print(pbs3);

