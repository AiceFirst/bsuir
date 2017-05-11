.MODEL tiny
.STACK 100h
.DATA
String db 5 dup (?),'$' ; ����������� 5 ���� ��� ������
StringEnd = $-1 ; ��������� �� ������ '$'
Number = 6219
Mes_1 db 0dh, 0ah, "Chislo 6219 v 16-y sisiteme schisleniya - ", "$" 
Mes_2 db 0dh, 0ah, "Chislo 6219 v 8-y sisiteme schisleniya - ", "$" 
Mes_3 db 0dh, 0ah, "Chislo 6219 v 2-y sisiteme schisleniya - ", "$" 

Flag db 01h
.CODE
ORG 100h

Start:
push ax
push bx
push cx
push dx 

mov ax,@data
mov ds,ax
mov es,ax 

lea dx,Mes_1
mov ah,09h
int 21h

mov bl,Flag

;------------------������� ����� � 16-� �.�.-----------------------------

std ; ������������� �������� ������� ������
lea di,StringEnd-1 ; ESI = ��������� ������ ������ String
mov ax,Number ; ������� � AX ����� ��� ��������
mov cx,16 ; �������� ��������� CX = 16
_16_System:
xor dx,dx ; �������� DX (��� �������)
div cx ; ����� DX:AX �� CX (16),
; �������� � AX �������, � DX �������
xchg ax,dx ; ������ �� ������� (��� ���������� �������)
add al,'0' ; �������� � AL ������ �����
cmp al,'9' ; ��������� ���� �����
jbe zapis ; ��������� �� ������

add al,'A'-('9'+1) ; ���� ������, ������������
jmp zapis

zapis: 
stosb ; � ���������� �� � ������

cmp bl,04h
jge zap_2
jmp zap_16_8
zap_2: 
inc di
; dec ch
cmp ch,0Fh
jne Met
jmp vivod

zap_16_8: xchg ax,dx ; ��������������� AX (�������)
or ax,ax ; ���������� AX � 0
jne _16_System ; ���� �� ����, �� ���������
jmp vivod

;------------------������� ����� � 8-� �.�.-----------------------------

_8_System: 
lea dx,Mes_2
mov ah,09h
int 21h 

std ; ������������� �������� ������� ������
lea di,StringEnd-1 ; ESI = ��������� ������ ������ String
mov ax,Number ; ������� � AX ����� ��� ��������
mov cx,8 ; �������� ��������� CX = 8
jmp _16_System

;-----------------������� ����� � 2-� �.�.-------------------------------

_2_System: 
lea dx,Mes_3
mov ah,09h
int 21h
std ; ������������� �������� ������� ������
lea di,StringEnd-1 ; ESI = ��������� ������ ������ String
mov ax,Number ; ������� � AX ����� ��� ��������
mov cl,16-1 ; 16-������ �������, ����� �������� �� 4 ���� (0..F)
xchg dx,ax ; ��������� ����� � DX

mov ch,0

Met:
mov ax,dx ; ��������������� ����� � AX
shr ax,cl ; �������� �� CL ��� ������
and al,1 ; �������� � AL ����� 0..15
add al,'0' ; �������� � AL ������ �����
sub cl,1 ; ��������� CL �� 1 ��� ��������� �����
inc ch 
jnc zapis ; ���� �������� CL >= 0, �� ��������� 
; � ���������� �� � ������
jmp zapis

;z1: 
; inc di
; dec ch
; cmp ch,0
; jne z1
; jmp vivod

;-----------------����� ������ �� �����----------------------------------
vivod:
mov ah,09h
; lea dx,[di+1] ; ������� � DX ����� ������ ������
lea dx,String ; ������� � DX ����� ������ ������
int 21h ; ������� �� �� �����
add bl,01h
cmp bl,02h
je _8_System

add bl,01h
cmp bl,04h
je _2_System

mov ax,4c00h
int 21h ; ������� �� ���������

push ax
push bx
push cx
push dx 

END Start