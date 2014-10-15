// CS410 Advanced Software Systems
// Masaya Ando
// September 28, 2014
//
// getsyms_dl.c
// Simple version of nm that dynamically loads library

#include <bfd.h>
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

#define rdtsc(x)      __asm__ __volatile__("rdtsc \n\t" : "=A" (*(x)))

int main(int argc, char *argv[])
{
	char *error;
	void (*func)(bfd *);
	void *handle;
	int option;
	unsigned long long start, end; 

	const char *filename = argv[1];
	const char *target = "elf64-x86-64";

	// RTLD_LAZY (0x1) or RTLD_NOW (0x2)
	option = (strcmp(argv[2], "RTLD_LAZY") != 0) ? 0x1 : 0x2; 
	
	// Load library dynamically and start timer
	rdtsc(&start);
	handle = dlopen("./lib/libobjdata.so", option);
	if (!handle) { fprintf(stderr, "Couldnt open /lib/libobjdata.so\n"); return 0; }
	rdtsc(&end);
	// printf("CPU\t%11u\n", (end-start)/1600); //CPU MHz = 1600.0	- Used for stats

	// BFD initialization
	bfd *abfd;
	bfd_init();
	abfd = bfd_openr(filename, target);
	if (abfd == NULL) { fprintf(stderr, "getsyms_dl: '%s': No such file", filename); return 0; }
	bfd_check_format(abfd, bfd_object);
	
	// Load dump_symbols() and execute
	func = dlsym(handle, "dump_symbols");
	if ((error = dlerror()) != NULL) { fprintf(stderr, error); return 0; }
	(*func)(abfd);
	dlclose(handle);
	return 0;
}
