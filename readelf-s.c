///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 6 - Readelf - SRE - Spring 2024
//
/// readelf - reads executable files to display the headers, section headers, sybol tables, etc.
///
/// @see     https://github.com/Trusted-Execution/.github/blob/main/documentation/elf.pdf
///
/// @file    readelf-s.c
/// @author  Kobe Uyeda <kobek@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include "readelf-s.h"

void PrintSymbolTable ( FILE* File, struct ELF_Header* ELF_Header ) {
    fseek(File, 0, SEEK_SET);
    fseek(File, ELF_Header->i_startOfSectionHeader, SEEK_SET);

    struct SectionHeader section;

    for (int i = 0; i < ELF_Header->i_numberOfSectionHeaders; i++) {
        fread(&section, sizeof(struct SectionHeader), 1, File);
        if (section == SHT_SYMTAB) {
            read_symbol_table(file, shdr);
            break;
        }
    }
}