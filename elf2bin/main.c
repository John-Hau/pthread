#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#include "elfparser.h"


//--------------------------------------
//#define FLASH_START_ADDRESS_FW  0x60E00000
#define FLASH_START_ADDRESS_FW  0x000500A0

#define RAW_FW_BIN_SIZE (0x400000)



//---- output buffer, should large than flash size ----
uint8_t RawBinBuf[RAW_FW_BIN_SIZE];
uint8_t* wp = RawBinBuf;

//--------------------------------------
FILE* fpELF;

Elf32_Ehdr eh;
Elf32_Shdr* sh_tbl;	/* section-header table is variable size */

//--- the section name must be ordered from low address to high address !!! ----
//const char section_A0[] = "A0";
//const char section_ABS[] = "Absolute sections";
//const char section_P1[] = "P1";



const char section_A0[] = "A0";
const char section_P1[] = "P1";
const char section_P25[] = "P25";




const char* FWsections[] = {section_A0, section_P1, section_P25};
//-------------------------------------
//const char section_LIB[] = "P6";
const char section_FONT[] = "P6";
//-------------------------------------



//---- define output bin file name ----
const char FWfileName[]   = "firmware.bin";
const char LIBfileName[]  = "library.bin";
const char FONTfileName[] = "font.bin";


//--------------------------------------

bool generateFWbin(const char** sections)
{
    int index;
    int offset;


    memset(RawBinBuf, 0, RAW_FW_BIN_SIZE);

    for( int i = 0; i < sizeof(FWsections)/sizeof(FWsections[0]); i++ )
    {
        index = get_section_header_index_by_name(fpELF, eh, sh_tbl, FWsections[i]);
        if( index < 0 )
        {
            printf("[Error] ELF file don't contain %s section !\n", FWsections[i]);
            exit(1);
        }
        else
        {
            debug("section %s index found at: %d \n", FWsections[i], index);
        }

        offset = sh_tbl[index].sh_addr - FLASH_START_ADDRESS_FW;

        if( read_section2buf(fpELF, sh_tbl[index], &RawBinBuf[offset]) )
        {
            wp = RawBinBuf + (offset + sh_tbl[index].sh_size);
        }
    }

    //------------------------------------------

    FILE* fpBin;

    if( NULL == ( fpBin = fopen(FWfileName,"wb") ) )   // read binary file built from eclipse
    {
        printf("[Error] Can not open %s !\n", FWfileName);
        exit(1);
    }
    //fwrite(RawBinBuf, sh_tbl[index].sh_size, 1, fpBin);
    fwrite(RawBinBuf, wp-RawBinBuf, 1, fpBin);

    fclose(fpBin);

    return true;

}


bool generateLIBbin(const char* secName)
{
    int index;

    if( NULL == secName )
    {
        return false;
    }

    memset(RawBinBuf, 0, RAW_FW_BIN_SIZE);

    index = get_section_header_index_by_name(fpELF, eh, sh_tbl, secName);
    if( index < 0 )
    {
        printf("[Error] ELF file don't contain %s section !\n", secName);
        exit(1);
    }
    else
    {
        debug("section %s index found at: %d \n", secName, index);
    }


    if( read_section2buf(fpELF, sh_tbl[index], &RawBinBuf[0]) )
    {
        wp = RawBinBuf + sh_tbl[index].sh_size;
    }


    //------------------------------------------

    FILE* fpBin;

    if( NULL == ( fpBin = fopen(LIBfileName,"wb") ) )   // read binary file built from eclipse
    {
        printf("[Error] Can not open %s !\n", LIBfileName);
        exit(1);
    }

    fwrite(RawBinBuf, wp-RawBinBuf, 1, fpBin);

    fclose(fpBin);

    return true;

}

bool generateFONTbin(const char* secName)
{
    int index;

    if( NULL == secName )
    {
        return false;
    }

    memset(RawBinBuf, 0, RAW_FW_BIN_SIZE);

    index = get_section_header_index_by_name(fpELF, eh, sh_tbl, secName);
    if( index < 0 )
    {
        printf("[Error] ELF file don't contain %s section !\n", secName);
        exit(1);
    }
    else
    {
        debug("section %s index found at: %d \n", secName, index);
    }


    if( read_section2buf(fpELF, sh_tbl[index], &RawBinBuf[0]) )
    {
        wp = RawBinBuf + sh_tbl[index].sh_size;
    }


    //------------------------------------------

    FILE* fpBin;

    if( NULL == ( fpBin = fopen(FONTfileName,"wb") ) )   // read binary file built from eclipse
    {
        printf("[Error] Can not open %s !\n", FONTfileName);
        exit(1);
    }

    fwrite(RawBinBuf, wp-RawBinBuf, 1, fpBin);

    fclose(fpBin);

    return true;

}

int main(int argc, char  *argv[])
{
    printf("\n----------- elf splitter -----------\n");




    printf("Load elf file... \n");
    //if( NULL == ( fpELF = fopen(argv[1],"rb") ) )   // read ELF file built from eclipse
    if( NULL == ( fpELF = fopen("cpo.out","rb") ) )   // read ELF file built from eclipse
    {
        printf("[Error] Can not open %s !\n", argv[1]);
        exit(1);
    }
    //------------------------------------------------

    remove(FWfileName);
    //remove(LIBfileName);
    remove(FONTfileName);
    printf("Old generated bin files removed \n");

    //------------------------------------------------

    read_elf_header(fpELF, &eh);
    sh_tbl = malloc(eh.e_shentsize * eh.e_shnum);
    print_elf_header(eh);

    read_section_header_table(fpELF, eh, sh_tbl);   // load section header table
    print_section_headers(fpELF, eh, sh_tbl);

    //--------------------------------------------------------------------


    generateFWbin(FWsections);
    //generateLIBbin(section_LIB);
   // generateFONTbin(section_FONT);
    //--------------------------------------------------------------------

    return 0;
}


