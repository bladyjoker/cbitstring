all:
	gcc -std=c99 -shared -o bitstring.so ../libbitstring.so -I.. lua_bitstring.c
	
	lua -i ./test_bitstring.lua

clean:
	rm -f *.so *.o *~
