Input Conversion to ASCII
Author: Bobby Bose

Instructions on compiling: Type "make" or "make run" to compile and run program.
                           OR just type "make transform" to only compile.
                           Can also use "make clean" to remove transform executable program.

Tested with file myinput.txt. Output is in myoutput.txt.
./transform < myinput.txt > myoutput.txt

This program runs with no arguments. Reads from the standard input and prints to standard output unless otherwise specified. "Ctrl-D" indicates end of input.
Input lines can either be empty or consist of tokens separated by space.
Tokens can be:
                 a decimal number from 0 to 255
                 a hex value in the form 0xzz or 0Xzz, where z can be any valid hex value (0-9 or A-F or a-f).
                 a string inside two quotation marks (")
                 a comment indicated by "//".
Decimals and hex values are converted to their corresponding ASCII values.
Strings are left as is, without converting anything inside the quotation marks.
Comments are left out of the output.

No input line can contain more than 1024 characters.
All input lines are combined together into one output line (unless a decimal or hex value is used to indicate newline [\n]).
If a malformed decimal or hex value is given in the input, the program will inform the user and then exit.
