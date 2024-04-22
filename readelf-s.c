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

#include <stdlib.h>
#include "readelf-s.h"

char *TypeSymboleToValue(unsigned char type)
{
    switch (type)
    {
    case 0:
        return "NOTYPE";
    case 1:
        return ("OBJECT");
    case 2:
        return ("FUNC");
    case 3:
        return ("Section");
    case 4:
        return ("File");
    case 5:
        return ("Common");
    case 6:
        return ("TLS");
    default:
        return ("Unknown");
    }
}

char *BindSymboleToValue(unsigned char type)
{
    switch (type)
    {
    case 0:
        return "LOCAL";
    case 1:
        return ("GLOBAL");
    case 2:
        return ("WEAK");
    case 3:
        return ("NUM");
    case 4:
        return ("LOOS");
    case 5:
        return ("LOPROC");
    default:
        return ("Unknown");
    }
}

char *VisSymboleToValue(unsigned char type)
{
    switch (type)
    {
    case 0:
        return "DEFAULT";
    case 1:
        return ("INTERNAL");
    case 2:
        return ("HIDDEN");
    case 3:
        return ("PROTECTED");
    default:
        return ("Unknown");
    }
}

char *NdxSymboleToValue(unsigned char type)
{
    switch (type)
    {
    case 0:
        return "UND";
    case 1:
        return ("ABS");
    case 2:
        return ("COM");
    case 3:
        return ("XIN");
    default:
        return ("Unknown");
    }
}

void PrintSymbolTable(FILE *File, struct ELF_Header *ELF_Header)
{
    fseek(File, ELF_Header->i_startOfSectionHeader, SEEK_SET);
    struct SectionHeader section;

    for (int i = 0; i < ELF_Header->i_numberOfSectionHeaders; i++)
    {
        unsigned char data[8];

        fread(data, 1, 4, File);
        section.name = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
        fread(data, 1, 4, File);
        section.type = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
        fread(data, 1, 8, File);
        section.flags = ((uint64_t)data[0]) |
                        ((uint64_t)data[1] << 8) |
                        ((uint64_t)data[2] << 16) |
                        ((uint64_t)data[3] << 24) |
                        ((uint64_t)data[4] << 32) |
                        ((uint64_t)data[5] << 40) |
                        ((uint64_t)data[6] << 48) |
                        ((uint64_t)data[7] << 56);
        fread(data, 1, 8, File);
        section.addr = ((uint64_t)data[0]) |
                       ((uint64_t)data[1] << 8) |
                       ((uint64_t)data[2] << 16) |
                       ((uint64_t)data[3] << 24) |
                       ((uint64_t)data[4] << 32) |
                       ((uint64_t)data[5] << 40) |
                       ((uint64_t)data[6] << 48) |
                       ((uint64_t)data[7] << 56);
        fread(data, 1, 8, File);
        section.offset = ((uint64_t)data[0]) |
                         ((uint64_t)data[1] << 8) |
                         ((uint64_t)data[2] << 16) |
                         ((uint64_t)data[3] << 24) |
                         ((uint64_t)data[4] << 32) |
                         ((uint64_t)data[5] << 40) |
                         ((uint64_t)data[6] << 48) |
                         ((uint64_t)data[7] << 56);
        fread(data, 1, 8, File);
        section.size = ((uint64_t)data[0]) |
                       ((uint64_t)data[1] << 8) |
                       ((uint64_t)data[2] << 16) |
                       ((uint64_t)data[3] << 24) |
                       ((uint64_t)data[4] << 32) |
                       ((uint64_t)data[5] << 40) |
                       ((uint64_t)data[6] << 48) |
                       ((uint64_t)data[7] << 56);
        fread(data, 1, 4, File);
        section.link = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
        fread(data, 1, 4, File);
        section.info = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
        fread(data, 1, 8, File);
        section.addralign = ((uint64_t)data[0]) |
                            ((uint64_t)data[1] << 8) |
                            ((uint64_t)data[2] << 16) |
                            ((uint64_t)data[3] << 24) |
                            ((uint64_t)data[4] << 32) |
                            ((uint64_t)data[5] << 40) |
                            ((uint64_t)data[6] << 48) |
                            ((uint64_t)data[7] << 56);
        fread(data, 1, 8, File);
        section.entrySize = ((uint64_t)data[0]) |
                            ((uint64_t)data[1] << 8) |
                            ((uint64_t)data[2] << 16) |
                            ((uint64_t)data[3] << 24) |
                            ((uint64_t)data[4] << 32) |
                            ((uint64_t)data[5] << 40) |
                            ((uint64_t)data[6] << 48) |
                            ((uint64_t)data[7] << 56);

        if (section.type == SHT_SYMTAB || section.type == SHT_DYNSYM)
        {
            fseek(File, section.offset, SEEK_SET);
            int numSymbols = section.size / sizeof(struct Symbol);
            struct Symbol *symbols = malloc(numSymbols * sizeof(struct Symbol));
            fread(symbols, sizeof(struct Symbol), numSymbols, File);

            struct SectionHeader strTabSection;
            fseek(File, section.link * sizeof(struct SectionHeader), SEEK_SET);
            fread(&strTabSection, sizeof(struct SectionHeader), 1, File);

            char *stringTable = malloc(strTabSection.size);
            fseek(File, strTabSection.offset, SEEK_SET);
            fread(stringTable, 1, strTabSection.size, File);

            printf("Symbol Table Section: \n");
            printf("   Num:    Value          Size Type    Bind   Vis      Ndx Name\n");
            for (int i = 0; i < numSymbols; i++)
            {
                struct Symbol sym = symbols[i];
                char *name = stringTable + sym.name;
                printf("% 6d: %016lx  % 4ld %-7s ", i, sym.value, sym.size, TypeSymboleToValue(sym.info & 0x0F));
                printf("%-6s %-8s %-2s %s\n", BindSymboleToValue(sym.info >> 4), VisSymboleToValue(sym.other), NdxSymboleToValue(sym.shndx), name);
            }

            free(symbols);
            free(stringTable);
        }
    }
}