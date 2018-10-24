    .data
newline:    .asciiz "\n" 
    .text
    .globl main
main:
    li $fp 0x7ffffffc 

B1:
    li $t0, 0 
    sw $t0, 0($fp) 

    li $t0, 0 
    sw $t0, -4($fp) 

    li $t0, 0 
    sw $t0, -8($fp) 

    li $t0, 5 
    sw $t0, -12($fp) 

    lw $t1, -12($fp) 
    add $t0, $t1, $zero 
    sw $t0, -4($fp) 

    li $t0, 10 
    sw $t0, -16($fp) 

    lw $t1, -16($fp) 
    add $t0, $t1, $zero 
    sw $t0, -8($fp) 

    li $t0, 8 
    sw $t0, -20($fp) 

    lw $t1, -20($fp) 
    add $t0, $t1, $zero 
    sw $t0, 0($fp) 

    li $t0, 10 
    sw $t0, -24($fp) 

    li $v0, 1 
    lw $t1, -24($fp) 
    add $a0, $t1, $zero
    syscall 
    li $v0, 4 
    la $a0, newline 
    syscall 

    li $t0, 8 
    sw $t0, -28($fp) 

    li $v0, 1 
    lw $t1, -28($fp) 
    add $a0, $t1, $zero
    syscall 
    li $v0, 4 
    la $a0, newline 
    syscall 

    li $v0, 10 
    syscall 
