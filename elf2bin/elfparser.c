
#include "elfparser.h"


char * read_section(FILE* fp, Elf32_Shdr sh)
{
	char* buff = malloc(sh.sh_size);
	if(!buff) {
		printf("%s:Failed to allocate %dbytes\n",
				__func__, sh.sh_size);
	}

	assert(buff != NULL);
	assert(fseek(fp, sh.sh_offset, SEEK_SET) == 0);
	assert(fread((void *)buff, sh.sh_size, 1, fp) == 1);

	return buff;
}


bool read_section2buf(FILE* fp, Elf32_Shdr sh, uint8_t* buf)
{
	assert(buf != NULL);
	assert(fseek(fp, sh.sh_offset, SEEK_SET) == 0);
	assert(fread((void *)buf, sh.sh_size, 1, fp) == 1);

	return true;
}

void print_section_headers(FILE* fp, Elf32_Ehdr eh, Elf32_Shdr sh_table[])
{
	uint32_t i;
	char* sh_str;	/* section-header string-table is also a section. */

	/* Read section-header string-table */
	debug("eh.e_shstrndx = 0x%x\n", eh.e_shstrndx);
	sh_str = read_section(fp, sh_table[eh.e_shstrndx]);

	printf("========================================");
	printf("========================================\n");
	printf(" idx offset     load-addr  size       algn"
			" flags      type       section\n");
	printf("========================================");
	printf("========================================\n");

	for(i=0; i<eh.e_shnum; i++) {
		printf(" %03d ", i);
		printf("0x%08x ", sh_table[i].sh_offset);
		printf("0x%08x ", sh_table[i].sh_addr);
		printf("0x%08x ", sh_table[i].sh_size);
		printf("%4d ", sh_table[i].sh_addralign);
		printf("0x%08x ", sh_table[i].sh_flags);
		printf("0x%08x ", sh_table[i].sh_type);
		printf("%s\t", (sh_str + sh_table[i].sh_name));
		printf("\n");
	}
	printf("========================================");
	printf("========================================\n");
	printf("\n");	/* end of section header table */

	free(sh_str);
}

void read_elf_header(FILE* fp, Elf32_Ehdr *elf_header)
{
	assert(elf_header != NULL);
	assert(fseek(fp, 0, SEEK_SET) == 0);
	assert(fread((void *)elf_header, sizeof(Elf32_Ehdr), 1, fp) == 1);
}


void print_elf_header(Elf32_Ehdr elf_header)
{


	/* Entry point */
	printf("Entry point\t= 0x%08x\n", elf_header.e_entry);

	/* ELF header size in bytes */
	printf("ELF header size\t= 0x%08x\n", elf_header.e_ehsize);

	/* Program Header */
	printf("\nProgram Header\t= ");
	printf("0x%08x\n", elf_header.e_phoff);		/* start */
	printf("\t\t  %d entries\n", elf_header.e_phnum);	/* num entry */
	printf("\t\t  %d bytes\n", elf_header.e_phentsize);	/* size/entry */

	/* Section header starts at */
	printf("\nSection Header\t= ");
	printf("0x%08x\n", elf_header.e_shoff);		/* start */
	printf("\t\t  %d entries\n", elf_header.e_shnum);	/* num entry */
	printf("\t\t  %d bytes\n", elf_header.e_shentsize);	/* size/entry */
	printf("\t\t  0x%08x (string table offset)\n", elf_header.e_shstrndx);

	/* File flags (Machine specific)*/
	printf("\nFile flags \t= 0x%08x\n", elf_header.e_flags);
}


void read_section_header_table(FILE* fp, Elf32_Ehdr eh, Elf32_Shdr sh_table[])
{

	assert(fseek(fp, eh.e_shoff, SEEK_SET) == 0);

    assert(fread((void *)sh_table, eh.e_shentsize, eh.e_shnum, fp) == eh.e_shnum);

}



int get_section_header_index_by_name(FILE* fp, Elf32_Ehdr eh, Elf32_Shdr sh_table[], const char* name)
{
    char* sh_str;
    int ret = -1;
    int i;

	sh_str = read_section(fp, sh_table[eh.e_shstrndx]);

    for(i=0; i<eh.e_shnum; i++)
    {
        if( 0 == strncmp(name, sh_str + sh_table[i].sh_name, strlen(name) ) )
        {
            ret = i;
            break;
        }
    }

    free(sh_str);

    return ret;
}





