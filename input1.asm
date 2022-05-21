     addi r1,r1,1      ;set r1=1
     addi r10,r10,10   ;set r10=10, r10 is counter
loop addi r1,r1,3      ;r1 += 3
     addi r10,r10,-1   ;counter --
     beqz r10,end      ;loop
     j loop
end halt