; ASCII NASM TAB4 CRLF
; Attribute: CPU(x86) Format(ELF) Call(not fastcall but cdecl)
; LastCheck: 2024Feb18
; AllAuthor: @dosconio
; ModuTitle: Input and Output for the Port
; Copyright: ArinaMgk UniSym, Apache License Version 2.0

;{TODO} add `x86` in document name;

GLOBAL _OUT_b, _IN_b; out dx, al; in al, dx;
GLOBAL _OUT_w, _IN_w; out dx, ax; in ax, dx;

[CPU 386]

[BITS 32]

; __fastcall void OUT_b(word Port, word Data);
; VOID <<< _OUT_b <<< ECX(DX Port), EDX(AX Data)
_OUT_b:
;	XCHG CX, DX
;	XCHG CX, AX
;	OUT DX, AL
;	XCHG CX, AX
;	XCHG CX, DX
	;{TEMP} Linux did not accept __fastcall, so use CDECL
	; - [BP+4*0]=BP
	; - [BP+4*1]=Return Address
	; - [BP+4*2]=Port
	; - [BP+4*3]=Data
	PUSH EBP
	MOV BP, SP
	PUSH DX
	PUSH AX
	MOV DX, [BP+4*2]
	MOV AX, [BP+4*3]
	OUT DX, AL
	POP AX
	POP DX
	MOV SP, BP
	POP EBP
RET

; __fastcall word IN_b(word Port);
; BYTE <<< _IN_b <<< ECX(Port)
_IN_b:
;	XCHG CX, DX
;	IN AL, DX
;	MOVZX EAX, AL
;	XCHG CX, DX
	;{TEMP} Linux did not accept __fastcall, so use CDECL
	; - [BP+4*0]=BP
	; - [BP+4*1]=Return Address
	; - [BP+4*2]=Port
	PUSH EBP
	MOV BP, SP
	PUSH DX
	MOV DX, [BP+4*2]
	IN AL, DX
	MOVZX EAX, AL
	POP DX
	MOV SP, BP
	POP EBP
RET

; __fastcall void OUT_w(word Port, word Data);
; VOID <<< _OUT_w <<< ECX(Port), EDX(Data)
_OUT_w:
;	XCHG CX, DX
;	XCHG CX, AX
;	OUT DX, AX
;	XCHG CX, AX
;	XCHG CX, DX
	;{TEMP} Linux did not accept __fastcall, so use CDECL
	; - [BP+4*0]=BP
	; - [BP+4*1]=Return Address
	; - [BP+4*2]=Port
	; - [BP+4*3]=Data
	PUSH EBP
	MOV BP, SP
	PUSH DX
	PUSH AX
	MOV DX, [BP+4*2]
	MOV AX, [BP+4*3]
	OUT DX, AX
	POP AX
	POP DX
	MOV SP, BP
	POP EBP
RET

; __fastcall word IN_w(word Port);
; WORD <<< _IN_w <<< ECX(Port)
_IN_w:
;	XCHG CX, DX
;	IN AX, DX
;	XCHG CX, DX
	;{TEMP} Linux did not accept __fastcall, so use CDECL
	; - [BP+4*0]=BP
	; - [BP+4*1]=Return Address
	; - [BP+4*2]=Port
	PUSH EBP
	MOV BP, SP
	PUSH DX
	MOV DX, [BP+4*2]
	IN AX, DX
	POP DX
	MOV SP, BP
	POP EBP
RET
	