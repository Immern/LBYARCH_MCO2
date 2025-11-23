section .data
msg db "z -> %f, %f, %f, %f, %f, %f, %f, %f, %f, %f", 10, 0

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
    sub rsp, 64
    
    mov rax, [rbp+48]   
    mov [rbp-32], rax        ; z pointer
    mov rax, [rbp+56]
    mov [rbp-56], rax             ; input pointer
    ; Load array addresses into non volatile registers
    mov r11, [rbp-32]
    mov r12, rcx             ; x1 pointer
    mov r13, rdx             ; x2 pointer
    mov r14, r8              ; y1 pointer
    mov r15, r9              ; y2 pointer
    
    xor rbx, rbx             ; loop counter 
L1:
    ; Load count from stack
    mov eax, [rbp-56]
    cmp rbx, rax
    jge L2
    
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
    ;cvtss2sd xmm1, xmm6
    movss [r11 + rbx*4], xmm6      ; store float result

    ;movss xmm8, [r11 + rbx * 4]
    ;movss xmm8, xmm1
    
    ; increase counter
    inc rbx
    jmp L1

L2:
    xor rbx, rbx
    jmp L3
L3:
    ; Setup printf
    lea rcx, [msg]           ; Format string
    
    movss xmm0, [r11 + 0]
    cvtss2sd xmm1, xmm0
    movq rdx, xmm1            ; Double value
    
    movss xmm0, [r11 + 4]
    cvtss2sd xmm1, xmm0
    movq r8, xmm1            ; Double value
    
    movss xmm0, [r11 + 8]
    cvtss2sd xmm1, xmm0
    movq r9, xmm1            ; Double value
    
    
    movss xmm0, [r11 + 12]
    cvtss2sd xmm1, xmm0
    movq [rsp+32], xmm1            ; Double value
    
    
    movss xmm0, [r11 + 16]
    cvtss2sd xmm1, xmm0
    movq [rsp+40], xmm1            ; Double value
    
    
    movss xmm0, [r11 + 20]
    cvtss2sd xmm1, xmm0
    movq [rsp+48], xmm1            ; Double value
    
    
    movss xmm0, [r11 + 24]
    cvtss2sd xmm1, xmm0
    movq [rsp+56], xmm1            ; Double value
    
    
    movss xmm0, [r11 + 28]
    cvtss2sd xmm1, xmm0
    movq [rsp+64], xmm1            ; Double value
    
    
    movss xmm0, [r11 + 32]
    cvtss2sd xmm1, xmm0
    movq [rsp+72], xmm1            ; Double value
    
    
    movss xmm0, [r11 + 36]
    cvtss2sd xmm1, xmm0
    movq [rsp+80], xmm1            ; Double value
    
    
    call printf
    
   

end:
    add rsp, 64
    
    ; pop non volatile registers
    pop r15
    pop r14
    pop r13
    pop r12
    
    pop rbp
    ret