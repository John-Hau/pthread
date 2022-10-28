
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define DEBUG 1
#define debug(...) \
            do { if (DEBUG) printf("<debug>:"__VA_ARGS__); } while (0)

typedef uint32_t Elf32_Off;
typedef uint32_t Elf32_Addr;

typedef struct {
   uint32_t   sh_name;
   uint32_t   sh_type;
   uint32_t   sh_flags;
   Elf32_Addr sh_addr;
   Elf32_Off  sh_offset;
   uint32_t   sh_size;
   uint32_t   sh_link;
   uint32_t   sh_info;
   uint32_t   sh_addralign;
   uint32_t   sh_entsize;
} Elf32_Shdr;

#define EI_NIDENT 16

typedef struct {
   unsigned char e_ident[EI_NIDENT];
   uint16_t      e_type;
   uint16_t      e_machine;
   uint32_t      e_version;
   Elf32_Addr     e_entry;
   Elf32_Off      e_phoff;
   Elf32_Off      e_shoff;
   uint32_t      e_flags;
   uint16_t      e_ehsize;
   uint16_t      e_phentsize;
   uint16_t      e_phnum;
   uint16_t      e_shentsize;
   uint16_t      e_shnum;
   uint16_t      e_shstrndx;
} Elf32_Ehdr;



char * read_section(FILE* fp, Elf32_Shdr sh);
bool   read_section2buf(FILE* fp, Elf32_Shdr sh, uint8_t* buf);
void read_elf_header(FILE* fp, Elf32_Ehdr *elf_header);
void print_elf_header(Elf32_Ehdr elf_header);
void read_section_header_table(FILE* fp, Elf32_Ehdr eh, Elf32_Shdr sh_table[]);
void print_section_headers(FILE* fp, Elf32_Ehdr eh, Elf32_Shdr sh_table[]);
int get_section_header_index_by_name(FILE* fp, Elf32_Ehdr eh, Elf32_Shdr sh_table[], const char* name);






