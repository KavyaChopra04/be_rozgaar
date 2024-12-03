
cpp_nothing:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	endbr64 
    1004:	sub    $0x8,%rsp
    1008:	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__@Base>
    100f:	test   %rax,%rax
    1012:	je     1016 <_init+0x16>
    1014:	call   *%rax
    1016:	add    $0x8,%rsp
    101a:	ret    

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	push   0x2fa2(%rip)        # 3fc8 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	bnd jmp *0x2fa3(%rip)        # 3fd0 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	nopl   (%rax)

Disassembly of section .plt.got:

0000000000001030 <__cxa_finalize@plt>:
    1030:	endbr64 
    1034:	bnd jmp *0x2fbd(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    103b:	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001040 <main>:
    1040:	endbr64 
    1044:	xor    %eax,%eax
    1046:	ret    
    1047:	nopw   0x0(%rax,%rax,1)

0000000000001050 <_start>:
    1050:	endbr64 
    1054:	xor    %ebp,%ebp
    1056:	mov    %rdx,%r9
    1059:	pop    %rsi
    105a:	mov    %rsp,%rdx
    105d:	and    $0xfffffffffffffff0,%rsp
    1061:	push   %rax
    1062:	push   %rsp
    1063:	xor    %r8d,%r8d
    1066:	xor    %ecx,%ecx
    1068:	lea    -0x2f(%rip),%rdi        # 1040 <main>
    106f:	call   *0x2f63(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    1075:	hlt    
    1076:	cs nopw 0x0(%rax,%rax,1)

0000000000001080 <deregister_tm_clones>:
    1080:	lea    0x2f89(%rip),%rdi        # 4010 <__TMC_END__>
    1087:	lea    0x2f82(%rip),%rax        # 4010 <__TMC_END__>
    108e:	cmp    %rdi,%rax
    1091:	je     10a8 <deregister_tm_clones+0x28>
    1093:	mov    0x2f46(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    109a:	test   %rax,%rax
    109d:	je     10a8 <deregister_tm_clones+0x28>
    109f:	jmp    *%rax
    10a1:	nopl   0x0(%rax)
    10a8:	ret    
    10a9:	nopl   0x0(%rax)

00000000000010b0 <register_tm_clones>:
    10b0:	lea    0x2f59(%rip),%rdi        # 4010 <__TMC_END__>
    10b7:	lea    0x2f52(%rip),%rsi        # 4010 <__TMC_END__>
    10be:	sub    %rdi,%rsi
    10c1:	mov    %rsi,%rax
    10c4:	shr    $0x3f,%rsi
    10c8:	sar    $0x3,%rax
    10cc:	add    %rax,%rsi
    10cf:	sar    %rsi
    10d2:	je     10e8 <register_tm_clones+0x38>
    10d4:	mov    0x2f15(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    10db:	test   %rax,%rax
    10de:	je     10e8 <register_tm_clones+0x38>
    10e0:	jmp    *%rax
    10e2:	nopw   0x0(%rax,%rax,1)
    10e8:	ret    
    10e9:	nopl   0x0(%rax)

00000000000010f0 <__do_global_dtors_aux>:
    10f0:	endbr64 
    10f4:	cmpb   $0x0,0x2f15(%rip)        # 4010 <__TMC_END__>
    10fb:	jne    1128 <__do_global_dtors_aux+0x38>
    10fd:	push   %rbp
    10fe:	cmpq   $0x0,0x2ef2(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1106:	mov    %rsp,%rbp
    1109:	je     1117 <__do_global_dtors_aux+0x27>
    110b:	mov    0x2ef6(%rip),%rdi        # 4008 <__dso_handle>
    1112:	call   1030 <__cxa_finalize@plt>
    1117:	call   1080 <deregister_tm_clones>
    111c:	movb   $0x1,0x2eed(%rip)        # 4010 <__TMC_END__>
    1123:	pop    %rbp
    1124:	ret    
    1125:	nopl   (%rax)
    1128:	ret    
    1129:	nopl   0x0(%rax)

0000000000001130 <frame_dummy>:
    1130:	endbr64 
    1134:	jmp    10b0 <register_tm_clones>

Disassembly of section .fini:

000000000000113c <_fini>:
    113c:	endbr64 
    1140:	sub    $0x8,%rsp
    1144:	add    $0x8,%rsp
    1148:	ret    
