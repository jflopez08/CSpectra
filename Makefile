envelope: envelope.c /usr/lib/x86_64-linux-gnu/libm.a  
	gcc -std=c11 -Wall -fmax-errors=10 -Wextra envelope.c -lm -o envelope
