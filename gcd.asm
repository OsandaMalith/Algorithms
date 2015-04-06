%if 0
Euclid's GCD Algorithm in x86 Assembly
- Osanda Malith Jayathissa 

int gcd(int x, int y) {
	while(x!=0) {
		if(x < y) {
			temp = x;
			x = y;
			y = temp;
		} x %= y;
	} return y;
}
%endif 
segment text
    global gcd
	
gcd:
    push ebp
    mov  ebp,esp
    mov  eax,[ebp+8]        ; load x from stack frame
    mov  ebx,[ebp+12]       ; load y from stack	frame
	
looptop:
    cmp  eax,0              ; if (x == 0) we're done
    je   goback
    cmp  eax,ebx            ; if(x < y)
    jge  modulo
    xchg eax,ebx     		; swap x and y
	
modulo:
    cdq                    ; set up for division
    idiv ebx               ; divide the contents of EDX:EAX by the contents of EBX
    mov  eax,edx           ; the remainder is in edx
    jmp  looptop
	
goback:
    mov  eax,ebx           ; return y
    mov  esp,ebp
    pop  ebp
    ret
