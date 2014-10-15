// CS410 Advanced Software Systems
// Masaya Ando
// September 28, 2014
//
// getsyms.c
// C program that prints the symbols of a section in a given BFD *abfd

#include <bfd.h>
#include <libobjdata.h>
#include <stdio.h>

int main(int argc, const char* argv[])
{
	const char* filename = argv[1];
	const char *target = "elf64-x86-64";
	
	bfd *abfd;
	bfd_init();
	abfd = bfd_openr(filename, target);
	if (abfd == NULL) { fprintf(stderr, "getsyms: '%s' : No such file", filename); return 0;  }
	bfd_check_format(abfd, bfd_object);
	dump_symbols(abfd);	
	return 0;
}
