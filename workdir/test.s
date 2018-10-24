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

    li $v0, 5 
    syscall 
    add $t0, $v0, $zero 
    sw $t0, 0($fp) 

    li $t0, 0 
    sw $t0, -8($fp) 

    lw $t1, -8($fp) 
    add $t0, $t1, $zero 
    sw $t0, -4($fp) 

    j B2 

B2:
    lw $t1, -4($fp) 
    lw $t2, -4($fp) 
    mul $t0, $t1, $t2 
    sw $t0, -12($fp) 

    lw $t1, -12($fp) 
    lw $t2, 0($fp) 
    sle $t0, $t1, $t2 
    sw $t0, -16($fp) 

    lw $t0, -16($fp) 
    bne $t0, $zero, B3 

    j B4 

B3:
    li $t0, 1 
    sw $t0, -20($fp) 

    lw $t1, -4($fp) 
    lw $t2, -20($fp) 
    addu $t0, $t1, $t2 
    sw $t0, -24($fp) 

    lw $t1, -24($fp) 
    add $t0, $t1, $zero 
    sw $t0, -4($fp) 

    j B2 

B4:
    li $t0, 18 
    sw $t0, -28($fp) 

    lw $t1, 0($fp) 
    lw $t2, -28($fp) 
    addu $t0, $t1, $t2 
    sw $t0, -32($fp) 

    lw $t1, -32($fp) 
    add $t0, $t1, $zero 
    sw $t0, 0($fp) 

    li $t0, 30 
    sw $t0, -40($fp) 

    lw $t1, -4($fp) 
    lw $t2, -40($fp) 
    addu $t0, $t1, $t2 
    sw $t0, -44($fp) 

    lw $t1, -44($fp) 
    add $t0, $t1, $zero 
    sw $t0, -4($fp) 

    j B5 

B5:
    li $t0, 3 
    sw $t0, -52($fp) 

    lw $t1, 0($fp) 
    lw $t2, -52($fp) 
    subu $t0, $t1, $t2 
    sw $t0, -56($fp) 

    lw $t1, -4($fp) 
    lw $t2, -56($fp) 
    slt $t0, $t1, $t2 
    sw $t0, -60($fp) 

    lw $t0, -60($fp) 
    bne $t0, $zero, B6 

    j B7 

B6:
    li $t0, 10 
    sw $t0, -64($fp) 

    lw $t1, 0($fp) 
    lw $t2, -64($fp) 
    addu $t0, $t1, $t2 
    sw $t0, -68($fp) 

    lw $t1, -68($fp) 
    add $t0, $t1, $zero 
    sw $t0, -4($fp) 

    j B8 

B7:
    li $t0, 5 
    sw $t0, -72($fp) 

    lw $t1, 0($fp) 
    lw $t2, -72($fp) 
    subu $t0, $t1, $t2 
    sw $t0, -76($fp) 

    lw $t1, -76($fp) 
    add $t0, $t1, $zero 
    sw $t0, -4($fp) 

    j B8 

B8:
    li $t0, 1 
    sw $t0, -80($fp) 

    lw $t1, -4($fp) 
    lw $t2, -80($fp) 
    subu $t0, $t1, $t2 
    sw $t0, -84($fp) 

    lw $t1, -84($fp) 
    add $t0, $t1, $zero 
    sw $t0, -4($fp) 

    li $v0, 1 
    lw $t1, -4($fp) 
    add $a0, $t1, $zero
    syscall 
    li $v0, 4 
    la $a0, newline 
    syscall 

    li $v0, 10 
    syscall 
