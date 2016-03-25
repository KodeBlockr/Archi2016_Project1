0x00000008
      . lw   $2 0($0)
      . lw   $3 4($0)
      . add  $4 ,$2 ,$3
      . sub  $5 ,$2 ,$3
      . and  $6 ,$2 ,$3
      . or   $7 ,$2 ,$3
      . xor  $8 ,$2 ,$3
      . nor  $9 ,$2 ,$3
      . nand $10,$2 ,$3
      . slt  $11,$3 ,$2
      . lw   $2 8($0)
      . srl  $12 $3 12
      . srl  $13 $2 12
      . sra  $14 $3 12
      . sra  $15 $2 12
      . beq  $12 $14 there
   this  addi $0  $4 0
      . j KKK
   there  bne  $13 $15 this
   KKK  addi $4 $4 -323
      . sh   $9 12($16)
      . lw   $9 12($0)
      . bne  $13 $15 AAA
   AAA  halt
