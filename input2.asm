     addi r9,r9,1     ;set r9=1
     addi r1,r1,10    ;set r1=10, r1 is counter
loop add r10,r8,r9    ;r10 = r8+r9
     addi r8,r9,0     ;r8 = r9
     addi r9,r10,0    ;r9 = r10
     sw r10,r2,0      ;store r10, use r2 as offset
     addi r2,r2,1     ;offset ++
     addi r1,r1,-1    ;counter --
     beqz r1,end      ;loop
     j loop
end halt