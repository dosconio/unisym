# アリナ Assembler

Haruno toke over in Roadn-F.

The detail to see in Her-Note.

- [ ] First source of studying `Netwide Assembler 2.7`.

Principle: can run in Intel-8086 and bootable by *Arina-Real-Address*, aka ARA in *Kasha* Kernel, which is that, the first byte of which is the numbers of sectors (512 bytes), the second byte will be pointed by Instruction Pointer after the programs are all loaded in the memory.



## TODO Version ...

- [ ] inherit `arina` directive i.e. `dw 0xaa55`. 
- [ ] `BMK` directive (wo boot-mark), i.e. `times 510-$+$$` then `arina`.

## TODO Version 0x0101

- [ ] support and only support for `MOV dest, sors`, for instructions.  
- [ ] support and only support the binary (flat) format, for output formats. 
- [ ] support input from `File / Console-Input-by-line` and output to `File / Console-Output(Hex)`. 

## Special

```asm
self keyword:
- test eax,eax <=> test eax self
- test i via rax self <=> mov rax,i; test rax,rax
- JNS{A}else{B} <=> JS .a; A; jmp .end; .a:B .end:;


```

