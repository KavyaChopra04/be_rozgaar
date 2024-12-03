Executables in Linux consists of assembly instructions and an ELF (Executable and Link Format)

SECTIONS of an ELF header
1. .text -> code
2. .rodata -> read onyl data. any attempt to write causes a fault
3. .data -> read/write data
4. .bss -> zero-initialised data (block started by symbol). Doesn't have to be stored in the executable, can indicate somehow that we need a space with XKB worth of 0s.


