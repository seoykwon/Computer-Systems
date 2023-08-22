.pos 0x100
                 ld   $n, r0            # r0 = address of n
                 ld   (r0), r0          # r0 = n
                 not  r0                # r0 = -6
                 inc  r0                # r0 = -5
                 ld   $0, r1            # r1 = temp_i = 0
                 ld   $a, r2            # r2 = address of a
                 ld   $b, r3            # r3 = address of b
                 ld   $c, r7            # r7 = address of c
                 ld   (r7), r7          # r7 = temp_c
loop:            mov  r1, r4            # r4 = temp_i
                 add  r0, r4            # r4 = temp_i - 5
                 beq  r4, end_loop      # if temp_i=10 goto +12
                 ld   (r2, r1, 4), r5   # r5 = a[i]
                 ld   (r3, r1, 4), r6   # r6 = b[i]
                 not  r6                # r6 = - b[i]
                 inc  r6
                 add  r6, r5            # r5 = a[i] - b[i]
                 bgt  r5, then          # if (a[i]>b[i]) goto +2
else:            inc  r1                # temp_i + 1
                 br   loop              # goto -10
then:            inc r7                 # r7 = temp_c + 1
                 inc r1                 # temp_i + 1
                 br   loop              # goto -13
end_loop:        ld   $c, r0            # r0 = address of c
                 st   r7, (r0)          # c = temp_c
                 ld   $i, r0            # r0 = address of i
                 st   r1, (r0)          # i = temp_i
                 halt



.pos 0x1000
i:               .long 0xffffffff         # i
n:               .long 0x00000005         # n
a:               .long 0x0000000a         # a[0]
                 .long 0x00000014         # a[1]
                 .long 0x0000001e         # a[2]
                 .long 0x00000028         # a[3]
                 .long 0x00000032         # a[4]
b:               .long 0x0000000b         # b[0]
                 .long 0x00000014         # b[1]
                 .long 0x0000001c         # b[2]
                 .long 0x0000002c         # b[3]
                 .long 0x00000030         # b[4]
c:               .long 0x0                # c