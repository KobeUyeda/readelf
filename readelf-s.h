///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 6 - Readelf - SRE - Spring 2024
//
/// readelf - reads executable files to display the headers, section headers, sybol tables, etc.
///
/// @see     https://github.com/Trusted-Execution/.github/blob/main/documentation/elf.pdf
///
/// @file    readelf-s.h
/// @author  Kobe Uyeda <kobek@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include "readelf-h.h"
#include <stdint.h>

enum types {
    SHT_NULL,
    SHT_PROGBITS,
    SHT_SYMTAB,
    SHT_STRTAB,	
    SHT_RELA,
    SHT_HASH,	
    SHT_DYNAMIC,
    SHT_NOTE,
    SHT_NOBITS,
    SHT_REL,
    SHT_SHLIB,
    SHT_DYNSYM,
    SHT_INIT_ARRAY,
    SHT_FINI_ARRAY,
    SHT_PREINIT_ARRAY,
    SHT_GROUP,
    SHT_SYMTAB_SHNDX,
    SHT_NUM,
    SHT_LOOS,
    SHT_HIOS,
    SHT_LOPROC,
    SHT_HIPROC,
    SHT_LOUSER,	
    SHT_HIUSER
};

enum flags {
    SHF_WRITE,
    SHF_ALLOC,
    SHF_EXECINSTR,
    SHF_MERGE,
    SHF_STRINGS,
    SHF_INFO_LINK,
    SHF_LINK_ORDER,
    SHF_OS_NONCONFORMING,
    SHF_GROUP,
    SHF_TLS,
    SHF_MASKOS,
    SHF_MASKPROC
};

struct Symbol {
    uint32_t name;         // Offset to the symbol name in the string table
    uint8_t  info;         // Type and binding attributes
    uint8_t  other;        // Reserved (includes visibility)
    uint16_t shndx;        // Section index
    uint64_t value;        // Symbol value (address)
    uint64_t size;         // Size of the symbol
};

struct SectionHeader {
    uint32_t name;
    uint32_t type;
    uint64_t flags;
    uint64_t addr;
    uint64_t offset;
    uint64_t size;
    uint32_t link;
    uint32_t info;
    uint64_t addralign;
    uint64_t entrySize;
};

void PrintSymbolTable ( FILE* File, struct ELF_Header* ELF_Header );