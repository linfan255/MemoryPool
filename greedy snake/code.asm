assume cs:code

data segment 		;
	dw 1960, 1962
	dw 200 dup(0)
data ends

code segment 			
start:
	jmp short startProg
	len dw 2
	speed dw 00ffh
startProg:
	call paintUI
	
gameLp:
	call clearScreen
	call move
	mov ax,len
	cmp ax,0
	je gameOver

	mov ax,data
	mov ds,ax
	mov bx,len
	add bx,bx
	sub bx,2
	mov si,ds:[bx]

	mov ax,0b800h
	mov es,ax
	mov ax,es:[si]
	cmp al,'-'
	je gameOver
	cmp al,'|'
	je gameOver
	call drawBody

	call sleep
	jmp gameLp

gameOver:
	mov ax,4c00h
	int 21h


move:  			;dl--方向：0123对应上下左右
	push ax
	push ds
	push bx

	mov ah,1
	int 16h
	;je noinput

	cmp al,'w'
	je moveUp
	cmp al,'s'
	je moveDown
	cmp al,'a'
	je moveLeft
	cmp al,'d'
	je moveRight
	cmp al,'j'
	je addLen
	cmp al,'k'
	je subLen
	cmp al,'u'
	je speedUp
	cmp al,'i'
	je speedReduc

	jmp goOn
moveUp:
	cmp dl,1
	je goOn
	mov dl,0
	jmp goOn
moveDown:
	cmp dl,0
	je goOn
	mov dl,1
	jmp goOn
moveLeft:
	cmp dl,3
	je goOn
	mov dl,2
	jmp short goOn
moveRight:
	cmp dl,2
	je goOn
	mov dl,3
	jmp short goOn
addLen:
	mov ax,data
	mov ds,ax
	mov bx,len
	dec bx
	add bx,bx

	mov ax,ds:[bx]
	cmp dl,0
	je appendUp
	cmp dl,1
	je appendDown
	cmp dl,2
	je appendLeft
	cmp dl,3
	je appendRight

appendUp:
	sub ax,160
	jmp short append
appendDown:
	add ax,160
	jmp short append
appendLeft:
	sub ax,2
	jmp short append
appendRight:
	add ax,2

append:
	mov ds:[bx + 2],ax
	inc len
	jmp short goOn
subLen:
	dec len
	jmp short goOn

speedUp:
	mov ax,speed
	sub ax,10h
	mov speed,ax
	jmp short goOn
speedReduc:
	mov ax,speed
	add ax,10h
	mov speed,ax

goOn:
	mov ax,speed
	cmp ax,10h
	jb tooFast
	cmp ax,0fffh
	ja tooSlow
	jmp short clsInputCache

tooFast:
	mov ax,10h
	mov speed,ax
	jmp short clsInputCache
tooSlow:
	mov ax,0fffh
	mov speed,ax
clsInputCache:
	mov ah,0ch
	int 21h
noinput:
	call walk
	pop bx
	pop ds
	pop ax	
	ret

walk:
	jmp short walkSt
	pos dw 0
walkSt:
	push ax
	push ds
	push bx
	push cx
	push di

	mov ah,0ch
	int 21h

	mov di,dx
	mov ax,data
	mov ds,ax
	mov ax,len
	dec ax
	add ax,ax
	mov bx,ax

	mov ax,[bx]
	mov pos,ax
	mov bx,0

	mov dx,di
	cmp dl,0
	je walkUp
	cmp dl,1
	je walkDown
	cmp dl,2
	je walkLeft
	cmp dl,3
	je walkRight

walkUp:
	sub pos,160
	jmp walkEd

walkDown:
	add pos,160
	jmp walkEd

walkLeft:
	sub pos,2
	jmp walkEd

walkRight:
	add pos,2

walkEd:
	mov cx,len
	cmp cx,0
	je endWalkProg
	sub cx,1
	cmp cx,0
	je walkLpEd
walkLp:
	mov ax,[bx + 2]
	mov [bx],ax
	add bx,2
	loop walkLp
walkLpEd:
	mov ax,pos
	mov [bx],ax
endWalkProg:
	pop di
	pop cx
	pop bx
	pop ds
	pop ax
	ret

clearScreen:
	push ax
	push es
	push si
	push cx

	mov ax,0b800h
	mov es,ax
	mov si,502
	mov cx,20
clsLp0:
	push cx
	mov cx,58
clsLp1:
	mov word ptr es:[si],0
	add si,2
	loop clsLp1
	add si,160
	sub si,116
	pop cx
	loop clsLp0

	pop cx
	pop si
	pop es
	pop ax
	ret

drawBody:
	push ax
	push es
	push ds
	push bx
	push cx
	push si

	mov ax,0b800h
	mov es,ax

	mov ax,data
	mov ds,ax
	mov bx,0
	mov cx,len
	mov al,'*'
	mov ah,00000001b
drawLp:
	mov si,ds:[bx]
	mov es:[si],ax
	add bx,2
	loop drawLp

	pop si
	pop cx
	pop bx
	pop ds
	pop es
	pop ax
	ret

paintUI:
	push ax
	push es
	push si
	push cx

	mov ax,0b800h
	mov es,ax
	mov si,2 * 160

	mov cx,60
	mov al,'-'
	mov ah,00010011b
paintUILp0:
	mov es:[si + 20],ax
	add si,2
	loop paintUILp0

	mov cx,20
	mov si,3 * 160
	mov al,'|'
paintUILp1:
	mov es:[si + 20],ax
	mov es:[si + 138],ax
	add si,160
	loop paintUILp1

	mov cx,60
	mov al,'-'
paintUILp2:
	mov es:[si + 20],ax
	add si,2
	loop paintUILp2

	pop cx
	pop si
	pop es
	pop ax
	ret

sleep:
	push cx
 	mov cx,speed  ;注意：改变此cx值可改变延时的时间长短
s0:	push cx
    mov cx,00fffh
s1:	loop s1
    pop cx
    loop s0
    pop cx
    ret
code ends
end start
