section .data
msg db "z[0] = %f", 10, 0

section .text
bits 64
default rel
global asmhello
extern printf

asmhello:
    push rbp
    mov rbp, rsp
    sub rsp, 32+8*16
    
    
    ; Load x1[0]
    movss xmm2, [rcx]       
    movss xmm3, [rdx]         
    movss xmm4, [r8]         
    movss xmm5, [r9]           
    
          
    
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
    lea rcx, [msg]             ; Format string
    movq rdx, xmm6            ; Move double bits to RDX (integer register)
    movsd xmm1, xmm6          ; Also in XMM1
    
    call printf
    
    add rsp, 32+8*16
    pop rbp
    ret