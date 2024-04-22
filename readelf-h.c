///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 6 - Readelf - SRE - Spring 2024
//
/// readelf - reads executable files to display the headers, section headers, sybol tables, etc.
///
/// @see     https://github.com/Trusted-Execution/.github/blob/main/documentation/elf.pdf
///
/// @file    readelf-h.c
/// @author  Kobe Uyeda <kobek@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////


#include <stdio.h>     // For printf()
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "readelf-h.h"

int GetMagic (FILE* ELF_File, struct ELF_Header* Header) {
    fread(Header->c_magic, 1, 16, ELF_File);
    if ( Header->c_magic[0] != 0x75 ) {
        return -1;
    }
    return 0;
}
int GetClass (struct ELF_Header* Header) {
    Header->e_class = (enum ELF_Classes) Header->c_magic[4];
    return 0;
}
int GetData (struct ELF_Header* Header) {
    Header->e_data = (enum ELF_Datas) Header->c_magic[5];
    return 0;
}
int GetOs (struct ELF_Header* Header) {
    Header->e_os = (enum ELF_OSs) Header->c_magic[7];
    return 0;
}
int GetABIVersion (struct ELF_Header* Header) {
    Header->i_abiVersion = (int) Header->c_magic[8];
    return 0;
}
int GetType (FILE* ELF_File, struct ELF_Header* Header) {
    char data[2];
    fread(data, 1, 2, ELF_File);
    int number = data[1] << 8 | data[0];
    Header->e_type = (enum ELF_Types) number;
    return 0;
}
int GetMachine (FILE* ELF_File, struct ELF_Header* Header) {
    char data[2];
    fread(data, 1, 2, ELF_File);
    int number = data[1] << 8 | data[0];
    Header->e_machine = (enum ELF_Machines) number;
    return 0;
}
int GetVersion (FILE* ELF_File, struct ELF_Header* Header) {
    char data[4];
    fread(data, 1, 4, ELF_File);
    uint32_t number = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
    Header->e_version = (enum ELF_Versions) number;
    return 0;
}
int GetEntry (FILE* ELF_File, struct ELF_Header* Header) {
    unsigned char data[8];
    fread(data, 1, 8, ELF_File);
    uint64_t entry = ((uint64_t)data[0])
                   | ((uint64_t)data[1] << 8)
                   | ((uint64_t)data[2] << 16)
                   | ((uint64_t)data[3] << 24)
                   | ((uint64_t)data[4] << 32)
                   | ((uint64_t)data[5] << 40)
                   | ((uint64_t)data[6] << 48)
                   | ((uint64_t)data[7] << 56);
    Header->i_entry = (int) entry;
    return 0;
}
int GetProgramStartHeader (FILE* ELF_File, struct ELF_Header* Header) {
    unsigned char data[8];
    fread(data, 1, 8, ELF_File);
    uint64_t entry = ((uint64_t)data[0])
                   | ((uint64_t)data[1] << 8)
                   | ((uint64_t)data[2] << 16)
                   | ((uint64_t)data[3] << 24)
                   | ((uint64_t)data[4] << 32)
                   | ((uint64_t)data[5] << 40)
                   | ((uint64_t)data[6] << 48)
                   | ((uint64_t)data[7] << 56);
    Header->i_startOfProgramHeader = (int) entry;
    return 0;
}
int GetSectionStartHeader (FILE* ELF_File, struct ELF_Header* Header) {
    unsigned char data[8];
    fread(data, 1, 8, ELF_File);
    uint64_t entry = ((uint64_t)data[0])
                   | ((uint64_t)data[1] << 8)
                   | ((uint64_t)data[2] << 16)
                   | ((uint64_t)data[3] << 24)
                   | ((uint64_t)data[4] << 32)
                   | ((uint64_t)data[5] << 40)
                   | ((uint64_t)data[6] << 48)
                   | ((uint64_t)data[7] << 56);
    Header->i_startOfSectionHeader = (int) entry;
    return 0;
}
int GetFlags (FILE* ELF_File, struct ELF_Header* Header) {
    unsigned char data[4];
    fread(data, 1, 4, ELF_File);
    uint32_t entry = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
    Header->i_flags = (int) entry;
    return 0;
}
int GetSizeOfHeader (FILE* ELF_File, struct ELF_Header* Header) {
    unsigned char data[2];
    fread(data, 1, 2, ELF_File);
    uint32_t entry = data[1] << 8 | data[0];
    Header->i_sizeOfHeader = (int) entry;
    return 0;
}
int GetSizeOfSingleProgramHeader (FILE* ELF_File, struct ELF_Header* Header) {
    unsigned char data[2];
    fread(data, 1, 2, ELF_File);
    uint32_t entry = data[1] << 8 | data[0];
    Header->i_sizeOfProgramHeader = (int) entry;
    return 0;
}
int GetCountOfProgramHeader (FILE* ELF_File, struct ELF_Header* Header) {
    unsigned char data[2];
    fread(data, 1, 2, ELF_File);
    uint32_t entry = data[1] << 8 | data[0];
    Header->i_numberOfProgramHeaders = (int) entry;
    return 0;
}
int GetSizeOfSectionHeader (FILE* ELF_File, struct ELF_Header* Header) {
    unsigned char data[2];
    fread(data, 1, 2, ELF_File);
    uint32_t entry = data[1] << 8 | data[0];
    Header->i_sizeOfSectionHeader = (int) entry;
    return 0;
}
int GetCountOfSectionHeader (FILE* ELF_File, struct ELF_Header* Header) {
    unsigned char data[2];
    fread(data, 1, 2, ELF_File);
    uint32_t entry = data[1] << 8 | data[0];
    Header->i_numberOfSectionHeaders = (int) entry;
    return 0;
}
int GetSectionHeaderStringTableIndex (FILE* ELF_File, struct ELF_Header* Header) {
    unsigned char data[2];
    fread(data, 1, 2, ELF_File);
    uint32_t entry = data[1] << 8 | data[0];
    Header->i_sectionHeaderStringTableIndex = (int) entry;
    return 0;
}

void PrintMagic (struct ELF_Header* Header) {
    printf("  Magic:   ");
    int i = 0;
    while ( i < 16 ) {
        printf("%02x ", (unsigned char) Header->c_magic[i]);
        i++;
    }
    printf("\n");
}
void PrintClass (struct ELF_Header* Header) {
    if (Header->e_class == ELFCLASSNONE) {
        printf("  Class:                             Invalid\n");
    } else if (Header->e_class == ELFCLASS32) {
        printf("  Class:                             ELF32\n");
    } else if (Header->e_class == ELFCLASS64) {
        printf("  Class:                             ELF64\n");
    } else {
        printf("  Class:                             Not Valids\n");
    }
}
void PrintData (struct ELF_Header* Header) {
    if (Header->e_data == ELFDATANONE) {
        printf("  Data:                              Unknown\n");
    } else if (Header->e_data == ELFDATA2LSB) {
        printf("  Data:                              2's complement, little endian\n");
    } else if (Header->e_data == ELFDATA2MSB) {
        printf("  Data:                              2's complement, big endian\n");
    } else {
        printf("  Data:                              Not Valids\n");
    }
}
void PrintOs (struct ELF_Header* Header) {
    printf("  OS/ABI:                            ");
    switch (Header->e_os) {
        case ELFOSABI_NONE:
            printf("UNIX System V ABI\n");
            break;
        case ELFOSABI_SYSV:
            printf("UNIX System V ABI\n");
            break;
        case ELFOSABI_HPUX:
            printf("HP-UX ABI\n");
            break;
        case ELFOSABI_NETBSD:
            printf("NetBSD ABI\n");
            break;
        case ELFOSABI_LINUX:
            printf("Linux ABI\n");
            break;
        case ELFOSABI_SOLARIS:
            printf("Solaris ABI\n");
            break;
        case ELFOSABI_IRIX:
            printf("IRIX ABI\n");
            break;
        case ELFOSABI_FREEBSD:
            printf("FreeBSD ABI\n");
            break;
        case ELFOSABI_TRU64:
            printf("TRU64 UNIX ABI\n");
            break;
        case ELFOSABI_ARM:
            printf("ARM architecture ABI\n");
            break;
        case ELFOSABI_STANDALONE:
            printf("Stand-alone (embedded) ABI\n");
            break;
        default:
            printf("Unknown\n");
            break;
    }
}
void PrintABIVersion(struct ELF_Header* Header) {
    printf("  ABI Version:                       %d\n", Header->i_abiVersion);
}
void PrintType (struct ELF_Header* Header) {
    if (Header->e_type == ET_NONE) {
        printf("  Type:                              NONE (No file Type)\n");
    } else if (Header->e_type == ET_REL) {
        printf("  Type:                              REL (Relocatable file )\n");
    } else if (Header->e_type == ET_EXEC) {
        printf("  Type:                              EXEC (Executable file)\n");
    } else if (Header->e_type == ET_DYN) {
        printf("  Type:                              DYN (Position-Independent Executable file)\n");
    } else if (Header->e_type == ET_CORE) {
        printf("  Type:                              CORE (Core file)\n");
    } else {
        printf("  Type:                              Not Valids\n");
    }
}
void PrintMachine (struct ELF_Header* Header) {
    printf("  Machine:                           ");
    switch (Header->e_machine) {
        case EM_NONE:
            printf("Unknown\n");
            break;
        case EM_M32:
            printf("AT&T WE 32100\n");
            break;
        case EM_SPARC:
            printf("SPARC\n");
            break;
        case EM_386:
            printf("Intel 80386\n");
            break;
        case EM_68K:
            printf("Motorola 68000\n");
            break;
        case EM_88K:
            printf("Motorola 88000\n");
            break;
        case EM_860:
            printf("Intel 80860\n");
            break;
        case EM_MIPS:
            printf("MIPS I Architecture\n");
            break;
        case EM_PARISC:
            printf("Hewlett-Packard PA-RISC\n");
            break;
        case EM_SPARC32PLUS:
            printf("Enhanced instruction set SPARC\n");
            break;
        case EM_PPC:
            printf("PowerPC\n");
            break;
        case EM_PPC64:
            printf("64-bit PowerPC\n");
            break;
        case EM_S390:
            printf("IBM System/390 Processor\n");
            break;
        case EM_ARM:
            printf("ARM 32-bit architecture (AARCH32)\n");
            break;
        case EM_SH:
            printf("Hitachi SH\n");
            break;
        case EM_SPARCV9:
            printf("SPARC Version 9\n");
            break;
        case EM_IA_64:
            printf("Intel IA-64 processor architecture\n");
            break;
        case EM_X86_64:
            printf("Advanced Micro Devices X86-64\n");
            break;
        case EM_VAX:
            printf("Digital VAX\n");
            break;
        default:
            printf("Other\n");
            break;
    }
}
void PrintVersionEnum (struct ELF_Header* Header) {
    if (Header->e_version == EV_NONE) {
        printf("  Version:                           0 (none)\n");
    } else if (Header->e_version == EV_Current) {
        printf("  Version:                           1 (current)\n");
    } else {
        printf("  Version:                           Error\n");
    }
}

void PrintVersionHex (struct ELF_Header* Header) {
    printf("  Version:                           0x%01x\n", (unsigned char) Header->e_version);
}

void PrintFlags (struct ELF_Header* Header) {
    printf("  Flags:                             0x%01x\n", (unsigned char) Header->i_flags);
}

void PrintEntryPoint (struct ELF_Header* Header) {
    printf("  Entry point address:               0x%x\n", Header->i_entry);
}
void PrintProgramStartHeader (struct ELF_Header* Header) {
    printf("  Start of program headers:          %d (bytes into file)\n", Header->i_startOfProgramHeader);
}
void PrintSectionStartHeader (struct ELF_Header* Header) {
    printf("  Start of section headers:          %d (bytes into file)\n", Header->i_startOfSectionHeader);
}
void PrintSizeOfHeader (struct ELF_Header* Header) {
    printf("  Size of this header:               %d (bytes)\n", Header->i_sizeOfHeader);
}
void PrintSizeOfProgramHeader (struct ELF_Header* Header) {
    printf("  Size of program headers:           %d (bytes)\n", Header->i_sizeOfProgramHeader);
}
void PrintCountOfProgramHeader (struct ELF_Header* Header) {
    printf("  Number of program headers:         %d\n", Header->i_numberOfProgramHeaders);
}
void PrintSizeOfSectionHeader (struct ELF_Header* Header) {
    printf("  Size of section headers:           %d (bytes)\n", Header->i_sizeOfSectionHeader);
}
void PrintCountOfSectionHeader (struct ELF_Header* Header) {
    printf("  Number of section headers:         %d\n", Header->i_numberOfSectionHeaders);
}
void PrintSectionHeaderStringTableIndex (struct ELF_Header* Header) {
    printf("  Section header string table index: %d\n", Header->i_sectionHeaderStringTableIndex);
}

struct ELF_Header* InitElfHeader (FILE* ELF_File) {
    struct ELF_Header* elfHeader = (struct ELF_Header*)malloc(sizeof(struct ELF_Header));       

    GetMagic(ELF_File, elfHeader);
    GetClass(elfHeader);
    GetData(elfHeader);
    GetOs(elfHeader);
    GetABIVersion(elfHeader);
    GetType(ELF_File, elfHeader);
    GetMachine(ELF_File, elfHeader);
    GetVersion(ELF_File, elfHeader);
    GetEntry(ELF_File, elfHeader);
    GetProgramStartHeader(ELF_File, elfHeader);
    GetSectionStartHeader(ELF_File, elfHeader);
    GetFlags(ELF_File, elfHeader);
    GetSizeOfHeader(ELF_File, elfHeader);
    GetSizeOfSingleProgramHeader(ELF_File, elfHeader);
    GetCountOfProgramHeader(ELF_File, elfHeader);
    GetSizeOfSectionHeader(ELF_File, elfHeader);
    GetCountOfSectionHeader(ELF_File, elfHeader);
    GetSectionHeaderStringTableIndex(ELF_File, elfHeader);

    return elfHeader;
}

void PrintHeaderOutput (struct ELF_Header* ELF_Header) {
    printf("ELF Header:\n");
    PrintMagic(ELF_Header);
    PrintClass(ELF_Header);
    PrintData(ELF_Header);
    PrintVersionEnum(ELF_Header);
    PrintOs(ELF_Header);
    PrintABIVersion(ELF_Header);
    PrintType(ELF_Header);
    PrintMachine(ELF_Header);
    PrintVersionHex(ELF_Header);
    PrintEntryPoint(ELF_Header);
    PrintProgramStartHeader(ELF_Header);
    PrintSectionStartHeader(ELF_Header);
    PrintFlags(ELF_Header);
    PrintSizeOfHeader(ELF_Header);
    PrintSizeOfProgramHeader(ELF_Header);
    PrintCountOfProgramHeader(ELF_Header);
    PrintSizeOfSectionHeader(ELF_Header);
    PrintCountOfSectionHeader(ELF_Header);
    PrintSectionHeaderStringTableIndex(ELF_Header);
}