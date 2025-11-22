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
    
    ; push non volatile registers 
    push r12
    push r13
    push r14
    push r15
    
    ; Allocate
    sub rsp, 48
    
    mov rax, [rbp+48]    ; Store count 
    mov [rbp-40], rax    ; Save count to stack slot
    
    ; Load array addresses into non volatile registers
    mov r12, rcx             ; x1 pointer
    mov r13, rdx             ; x2 pointer
    mov r14, r8              ; y1 pointer
    mov r15, r9              ; y2 pointer
    
    xor rbx, rbx             ; loop counter 

L1:
    ; Load count from stack
    mov eax, [rbp-40]
    cmp rbx, rax
    jge end
    
    ; Load array elements
    movss xmm2, [r12 + rbx * 4]
    movss xmm3, [r13 + rbx * 4]
    movss xmm4, [r14 + rbx * 4]
    movss xmm5, [r15 + rbx * 4]
    
    ; Perform operations
    vsubss xmm6, xmm3, xmm2
    vmulss xmm6, xmm6, xmm6
    vsubss xmm7, xmm5, xmm4
    vmulss xmm7, xmm7, xmm7
    addss xmm6, xmm7
    sqrtss xmm6, xmm6
    ; Convert to double
    cvtss2sd xmm1, xmm6
    
    ; Setup printf
    lea rcx, [msg]           ; Format string
    mov edx, ebx             ; Index
    movq r8, xmm1            ; Double value
    call printf
    
    ; increase counter
    inc rbx
    jmp L1

end:
    add rsp, 48
    
    ; pop non volatile registers
    pop r15
    pop r14
    pop r13
    pop r12
    
    pop rbp
    ret