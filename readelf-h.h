///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 6 - Readelf - SRE - Spring 2024
//
/// readelf - reads executable files to display the headers, section headers, sybol tables, etc.
///
/// @see     https://github.com/Trusted-Execution/.github/blob/main/documentation/elf.pdf
///
/// @file    readelf-h.h
/// @author  Kobe Uyeda <kobek@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>      // used to open a file

enum ELF_Classes  { 
    ELFCLASSNONE,       // Invalid Class
    ELFCLASS32,         // 32 bit architecture
    ELFCLASS64          // 64 bit architecture
};
enum ELF_Datas    { 
    ELFDATANONE,        // Unknown data format
    ELFDATA2LSB,        // Two's Complement little endian
    ELFDATA2MSB         // Two's Complement big endian
};
enum ELF_Versions { 
    EV_NONE,            // Invalid Version
    EV_Current          // Current Version
};
enum ELF_OSs      { 
    ELFOSABI_NONE,      // Same as ELFOSABI_SYSV
    ELFOSABI_SYSV,      // UNIX System V ABI
    ELFOSABI_HPUX,      // HP-UX ABI
    ELFOSABI_NETBSD,    // NETBSD ABI
    ELFOSABI_LINUX,     // Linux ABI
    ELFOSABI_SOLARIS,   // Solaris ABI
    ELFOSABI_IRIX,      // IRIX ABI
    ELFOSABI_FREEBSD,   // FreeBSD ABI
    ELFOSABI_TRU64,     // TRU64 UNIX ABI
    ELFOSABI_ARM,       // ARM architecture ABI
    ELFOSABI_STANDALONE // Stand-alone (embedded) ABI
};
enum ELF_Types    {
    ET_NONE,            // unknown type
    ET_REL,             // relocatable file
    ET_EXEC,            // executable file
    ET_DYN,             // shared object
    ET_CORE             // core file
};
enum ELF_Machines {
    EM_NONE = 0,          // No machine
    EM_M32 = 1,           // AT&T WE 32100
    EM_SPARC = 2,         // SPARC
    EM_386 = 3,           // Intel 80386
    EM_68K = 4,           // Motorola 68000
    EM_88K = 5,           // Motorola 88000
    EM_860 = 7,           // Intel 80860
    EM_MIPS = 8,          // MIPS I Architecture
    EM_PARISC = 15,       // Hewlett-Packard PA-RISC
    EM_SPARC32PLUS = 18,  // Enhanced instruction set SPARC
    EM_PPC = 20,          // PowerPC
    EM_PPC64 = 21,        // 64-bit PowerPC
    EM_S390 = 22,         // IBM System/390 Processor
    EM_ARM = 40,          // ARM 32-bit architecture (AARCH32)
    EM_SH = 42,           // Hitachi SH
    EM_SPARCV9 = 43,      // SPARC Version 9
    EM_IA_64 = 50,        // Intel IA-64 processor architecture
    EM_X86_64 = 62,       // AMD x86-64 architecture
    EM_VAX = 75,            // Digital VAX        
};

struct ELF_Header {
    char              c_magic [16];
    enum ELF_Classes  e_class;
    enum ELF_Datas    e_data;
    enum ELF_Versions e_version;
    enum ELF_OSs      e_os;
    enum ELF_Types    e_type;
    enum ELF_Machines e_machine;
    int               i_abiVersion;
    int               i_entry;
    int               i_startOfProgramHeader;
    int               i_startOfSectionHeader;
    int               i_flags;
    int               i_sizeOfHeader;
    int               i_sizeOfProgramHeader;
    int               i_numberOfProgramHeaders;
    int               i_sizeOfSectionHeader;
    int               i_numberOfSectionHeaders;
    int               i_sectionHeaderStringTableIndex;
};

struct ELF_Header* InitElfHeader (FILE* ELF_File);
void PrintHeaderOutput (struct ELF_Header* ELF_Header);