randmain: randmain.c randcpuid.c
	$(CC) $(CFLAGS) -o $@ randmain.c randcpuid.c -ldl -Wl,-rpath=$$PWD
randlibhw.so: randlibhw.c
	$(CC) $(CFLAGS) -c -fPIC randlibhw.c -o randlibhw.o
	$(CC) -shared -o randlibhw.so randlibhw.o  
randlibsw.so: randlibsw.c
	$(CC) $(CFLAGS) -c -fPIC randlibsw.c -o randlibsw.o
	$(CC) -shared -o randlibsw.so randlibsw.o 
