# @author Your Name Here {@literal pluf@wfu.edu}
# @date Nov. 26, 2020
# @assignment Lab 7
# @file sum_two.s
# @course CSC 250
#
# This program reads two integers and displays the sum
#
# Compile and run (Windows)
#   gcc -nostartfiles sum_two.s


.text
   .global _main               # use main if using C library


_main:
   push %ebp                  # save the old frame
   mov  %esp, %ebp            # create a new frame  

   # sub  $16, %esp             # make some space on the stack (stack alignment)

   # prompt the user
   mov  $prompt_format, %edi  # first printf argument, format string  
   xor  %eax, %eax            # zero out rax  
   call _printf                # printf

   # read the value
   mov  $read_format, %edi    # first scanf argument, format string
   lea  -4(%ebp), %esi        # second scanf argument, memory address
   xor  %eax, %eax            # zero out rax
   call _scanf                 # scanf

   # print to the screen
   mov  $write_format, %edi   # first printf argument, format string  
   mov -4(%ebp), %esi         # second printf argument, the integer  
   xor  %eax, %eax            # zero out rax  
   call _printf                # printf

   # add  $16, %esp             # release stack space
   pop  %ebp                  # restore old frame
   ret                        # return to C library to end


.data

read_format:
   .asciz  "%d"

prompt_format:
   .asciz  "Enter an integer -> "

write_format:
   .asciz  "You entered %d \n"


   