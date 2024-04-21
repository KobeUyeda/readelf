## Recreating "readelf"

## Description 

This project we will be creating two programs. One called readelf_h and readelf_s, each one will reproduce the functionality of readelf. Readelf_h will recreate the functionality of `readelf -h <executable>` and Readelf_s will recreate the functionality of `readelf-s <executable>`.

## Build, Test and Clean Commands

- `make` will build the executable
- `make clean` will delete the executable and remove all the *.o files
- `make test` will build all the files in debug mode and run tests stored in the test directory

## Hints & Details Given By Assignment Readme

- [ ] There are 19 headers, starting with `Magic:` and ending with `Section header string table index:`. You need to do them all, exactly as `readelf` does it. This will be good practice in formatting output.
- [ ] After you do the header, then start the symbol table dump.
- [ ] Symbol table entries refer to entries in a string table (they are different tables!) so you'll likely need to find the string table before finding the symbol table
- [ ] To do symbol tables, you'll likely have to find the section table to find the `SHT_DYNSYM` and `SHT_SYMTAB` sections. You'll also need to find the string table. Only then will you be able to start dumping symbols.
- [ ] Don't underestimate how long it will take to parse this... The trick is to keep your code (in particular, your function & variable names) organized. Try to use Object Oriented techniques (writing simple "getters" that are experts in delivering some critical piece of information).
- [ ] I'm only going to ask you to implement a 64-bit, Little Endian ELF parser. You'll thank me later.
- [ ] Make sure you write a durable parser for processing the section table. You'll need it for `Ndx` or `st_shndx`.
- [ ] I'm leaving it to you to find ELF files to test. There are hundreds of them in `/bin`. Don't pick anything that's too big or too small.