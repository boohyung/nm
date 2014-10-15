// CS410 Advanced Software Systems
// Masaya Ando
// September 28, 2014
//
// objsym.c
// Simple version of UNIX nm command
//
// Reference: Apple Open Source
// http://www.opensource.apple.com/source/cctools/cctools-698/misc/nm.c

#include <bfd.h>
#include <stdio.h>
#include <stdlib.h>

void dump_symbols(bfd *abfd) 
{
	unsigned int i;
	unsigned int symSize;
	unsigned int symCount;
	asymbol **symTable;
	symbol_info symInfo; 
	
	// Compute the bytes required to store a vector pointers for all symbols in BFD abfd
	symSize = bfd_get_symtab_upper_bound(abfd);
	if (symSize < 0) { printf("symSize is too small"); }

	// Allocate the bytes required by symSize 
	symTable = (asymbol **) malloc(symSize);

	// Fill in symTable with pointers to the symbols
	symCount = bfd_canonicalize_symtab(abfd, symTable); 
	
	// Loop through the symTable and print each symbol's name and value
	for (i = 0; i < symCount; i++) {
		bfd_symbol_info(symTable[i], &symInfo);
		fprintf(stdout, "%016x %c %s\n", (symInfo.value), bfd_decode_symclass(symTable[i]), symTable[i]->name);
	} 
}
