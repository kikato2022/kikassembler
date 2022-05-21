     addi r1,r1,1      ;set r1=1
     addi r10,r10,10   ;set r10=10, r10 is counter
loop sw r1,r2,0        ;store r1, use r2 as address offset
     addi r2,r2,1      ;offset ++
     mult r1,r1,r2     ;r1 = r1*r2
     addi r10,r10,-1   ;counter --
     beqz r10,end      ;loop
     j loop
end halt