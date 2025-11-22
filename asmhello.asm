section .data
msg db "z[%d] = %f", 10, 0

section .text
bits 64
default rel
global asmhello
extern printf

asmhello:
    push rbp
    mov rbp, rsp
    ;sub rsp, 32+8*16
    sub rsp, 32
    
    mov r10, [rbp+32] ;input
    
    ; Load addresses
    mov r11, rcx        ; x1 pointer
    mov r12, rdx        ; x2 pointer
    mov r13, r8         ; y1 pointer
    mov r14, r9         ; y2 pointer
    
    xor r15, r15        ; counter i = 0
    
L1:
    cmp r15, 4
    je end
    ; Load to float registers
    movss xmm2, [r11 + r15*4]       
    movss xmm3, [r12 + r15*4]         
    movss xmm4, [r13 + r15*4]         
    movss xmm5, [r14 + r15*4]           
    
     
    ;perform operations
    vsubss xmm6, xmm3, xmm2
    vmulss xmm6, xmm6, xmm6
    vsubss xmm7, xmm5, xmm4
    vmulss xmm7, xmm7, xmm7
    addss xmm6, xmm7
    sqrtss xmm6, xmm6
     ; Convert to double
    cvtss2sd xmm6, xmm6
    
    
    ; Setup printf - the key is getting double into RDX/XMM1 properly
    lea rdi, [msg]             ; Format string
    mov esi, r15d            ; Move double bits to RDX (integer register)
    movsd xmm0, xmm6          ; Also in XMM1
    xor eax, eax
    call printf
    
    inc r15
    jmp L1
end:
    add rsp, 32
    pop rbp
    ret