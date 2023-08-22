.pos 0x100
            ld $s, r0           # r0 = address of s
            ld $0, r2           # r2 = temp_i
i_loop:     ld $n, r1           # r1 = address of n
            ld (r1), r1         # r1 = n
            not r1              # ~r1
            inc r1              # r1 = -n
            mov r2, r3
            add r1, r3          # r3 = temp_i - n
            beq r3, i_end       # if temp_i = 0, goto

            # average loop
else:       ld $-5, r1          # r1 = -5
            ld $1, r4           # r4 = i = 1
            mov r0, r7          # r7 = address of s
            ld (r7), r7         # r7 = address of base
            mov r2, r3          # r3 = i
            shl $3, r3
            add r3, r7
            shl $1, r3
            add r3, r7          # r7 = i * 8 + i * 16
            ld $0, r3           # r3 = temp_a
loop:       mov r4, r5          # r5 = temp_i
            add r1, r5          # temp_i - 5
            beq r5, a_end       # if r5 = 0, goto
else:       ld (r7, r4, 4), r6  # r4 = base[temp_i]
            add r6, r3          # temp_a = temp_a + base[temp_i]
            inc r4              # temp_i + 1
            br loop             # goto
a_end:      shr $2, r3          # r3 = temp_a / 4
            st r3, (r7, r4, 4)  # b[5] = temp_a / 4

            inc r2
            br i_loop

i_end:
            # for (int i=n-1; i>0; i--)
            ld $n, r5           # r5 = address of n
            ld (r5), r5         # r5 = n
            dec r5              # r5 = n - 1 = i
b_loop:     beq r5, end_b       # if n - 1 = 0, goto end_b
else:
            # for (int j=1; j<=i; j++)
            ld $0x1, r1         # r1 = 1 = j
inner_loop: mov r5,  r2         # r2 = i
            not r2              # ~i
            inc r2              # r2 = - i
            add r1, r2          # r2 = j - i
            bgt r2, end_inner   # j - i > 0, goto end_inner

            # do if (a[j-1] > a[j])
else:       mov r1, r3          # r3 = r1 = j
            mov r1, r2          # r2 = r1 = j
            dec r3              # r3 = j - 1
if:         mov r0, r6          # r6 = r0
            mov r0, r7          # r7 = r0 (address of s)
            ld (r7), r7
            ld (r6), r6         # address of base
            shl $3, r2
            add r2, r6
            shl $1, r2
            add r2, r6          # r6 = i * 8 + i * 16 r1 > r3
            shl $3, r3
            add r3, r7
            shl $1, r3
            add r3, r7          # r7 = i * 8 + i * 16 address of base + 24 * (j - 1)
            ld 0x14(r6), r2     # r2 = s[j]
            ld 0x14(r7), r4     # r4 = s[j - 1]
            not r2              # ~r2
            inc r2              # -r2
            add r2, r4          # s[r3] - s[r1]
            bgt r4, swap        # if s[r3] > s[r1], goto swap

            # else, no swap, goes back to inner loop, j++
else:       inc r1              # r1 = j + 1
            br inner_loop

swap:       ld (r6), r2         # r2 = r6[student.id]
            ld (r7), r3         # r3 = r7[student.id]
            st r3, (r6)         # r6[student.id] = r7[student.id]
            st r2, (r7)
            ld 0x4(r6), r2      # r2 = r6[grade0]
            ld 0x4(r7), r3      # r3 = r7[grade0]
            st r3, 0x4(r6)      # r6[grade0] = r7[grade0]
            st r2, 0x4(r7)
            ld 0x8(r6), r2      # r2 = r6[grade1]
            ld 0x8(r7), r3      # r3 = r7[grade1]
            st r3, 0x8(r6)      # r6[grade1] = r7[grade1]
            st r2, 0x8(r7)
            ld 0xc(r6), r2      # r2 = r6[grade2]
            ld 0xc(r7), r3      # r3 = r7[grade2]
            st r3, 0xc(r6)      # r6[grade2] = r7[grade2]
            st r2, 0xc(r7)
            ld 0x10(r6), r2      # r2 = r6[grade3]
            ld 0x10(r7), r3      # r3 = r7[grade3]
            st r3, 0x10(r6)      # r6[grade3] = r7[grade3]
            st r2, 0x10(r7)
            ld 0x14(r6), r2      # r2 = r6[average]
            ld 0x14(r7), r3      # r3 = r7[average]
            st r3, 0x14(r6)      # r6[grade4] = r7[average]
            st r2, 0x14(r7)

            # go back to inner loop
            inc r1              # r1 = j + 1
            br inner_loop
end_inner:  dec r5              # r5 = n - 1
            br b_loop           # goto b_loop
end_b:      ld $n, r1           # r1 = address of n
            ld (r1), r1         # r1 = n
            shr $1, r1          # r1 = n / 2 (floor)
            ld (r0), r0         # r0 = address of base
            shl $3, r1
            add r1, r0
            shl $1, r1
            add r1, r0
            ld (r0), r2         # r2 = s[n/2] student number
            ld $m, r3           # r3 = address of m
            st r2, (r3)         # m = s[n/2]
            halt



.pos 0x1000
n:      .long 5       # just one student
m:      .long 0       # put the answer here
s:      .long base    # address of the array
base:   .long 1234    # student ID
        .long 80      # grade 0
        .long 60      # grade 1
        .long 78      # grade 2
        .long 90      # grade 3
        .long 0       # computed average
base2:  .long 4444    # student ID
        .long 95      # grade 0
        .long 71      # grade 1
        .long 52      # grade 2
        .long 60      # grade 3
        .long 0       # computed average
base3:  .long 1245    # student ID
        .long 100     # grade 0
        .long 100      # grade 1
        .long 75      # grade 2
        .long 100      # grade 3
        .long 0       # computed average
base4:  .long 1275    # student ID
        .long 100     # grade 0
        .long 90      # grade 1
        .long 75      # grade 2
        .long 0       # grade 3
        .long 0       # computed average
base5:  .long 1345    # student ID
        .long 100     # grade 0
        .long 50      # grade 1
        .long 100     # grade 2
        .long 75      # grade 3
        .long 0       # computed average