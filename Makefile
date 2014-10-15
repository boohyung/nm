# CS410 Advanced Software Systems
# Masaya Ando
# September 28, 2014
#
# Makefile
# Instructions for specific project

all: getsyms_dl getsyms

getsyms_dl: getsyms_dl.c
	gcc -rdynamic -o getsyms_dl getsyms_dl.c -ldl -lbfd

getsyms: getsyms.c libobjdata.a
	gcc -I./include -L./lib -o getsyms getsyms.c ./lib/libobjdata.a -lbfd

libobjdata.so: objsym.o   
	gcc -shared -o libobjdata.so objsyms.o -lbfd
	mv libobjdata.so lib

libobjdata.a: objsym.o
	ar rs libobjdata.a objsym.o
	mv libobjdata.a lib

objsym.o: objsym.c
	gcc -c objsym.c

clean: 
	rm -rf getsyms objsym.o 
	rm -rf getsyms_dl 

