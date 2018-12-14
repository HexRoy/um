CSC 411: UM
Liam Phelan and Geoffroy Penny

Compared to our design we have used less modules than
anticipated. The modules we have not used from our
design would be the loadUM.c, which we combined with
our execUm.c. We also made use of bitpack.c to work
with words.

Our system is split up between four c files:
um.c, execUM.c, segment.c, instruction.c, and
bitpack.c

um.c calls execUM.c to do all the heavy lifting and 
processing of the .um files.

execUM.c deals with all the memory, instantiating a
program, running a um program, reading opcodes to 
execute instructions, and freeing the UM from memory.

segment.c deals with all the memory segments

instruction.c contains all the code needed to work
with the instructions.

bitpack.c like previous assignments deals with decoding
and manipulating words.

we do not currently know how long it takes for the UM
to run 50 million instructions. 

When preparing our design, we worked for approximately 
2 or 3 hours

When preparing our implementation, we worked for 
approximately 25 hours.