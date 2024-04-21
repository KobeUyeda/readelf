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
    EM_NONE,            // unknown machine
    EM_M32,             // AT&T WE 32100
    EM_SPARC,           // Sun Microsystems SPARC
    EM_386,             // Intel 80386
    EM_68K,             // Motorola 68000
    EM_88K,             // Motorola 88000
    EM_860,             // Intel 80860
    EM_MIPS,            // MIPS RS3000
    EM_PARISC,          // HP/PA
    EM_SPARC32PLUS,     // SPARC with enhanced instruction set
    EM_PPC,             // PowerPC
    EM_PPC64,           // PowerPC 64-bit
    EM_S390,            // IBM S/390
    EM_ARM,             // Advanced RISC Machines
    EM_SH,              // Renesas SuperH
    EM_SPARCV9,         // SPARC v9 64-bit
    EM_IA_64,           // Intel Intanium
    EM_X86_64,          // AMD x86-64
    EM_VAX              // DEC Vax
};

struct ELF_Header {
    char             c_magic [16];
    enum ELF_Classes  e_class;
    enum ELF_Datas    e_data;
    enum ELF_Versions e_version;
    enum ELF_OSs      e_os;
    enum ELF_Types    e_type;
    enum ELF_Machines e_machine;
    double            d_abiVersion;
    void*             p_entry;
    int               i_startOfProgramHeader;
    int               i_startOfSectionHeader;
    int               i_flags;
    int               i_sizeOfHeader;
    int               i_numberOfProgramHeaders;
    int               i_numberOfSectionHeaders;
    int               i_sectionHeaderStringTableIndex;
};

struct ELF_Header InitElfHeader (FILE* ELF_File);
void PrintHeaderOutput (struct ELF_Header ELF_Header);