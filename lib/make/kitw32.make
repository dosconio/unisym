# GBK Makefile TAB4 CRLF
# Attribute: 
# LastCheck: RFZ18
# AllAuthor: @dosconio
# ModuTitle: Makefile for utilities of UniSym
# Copyright: ArinaMgk UniSym, Apache License Version 2.0

INCC_DIR=../../inc/c/
LIBC_DIR=../../lib/c/
DEST_BIN=../../../_bin/
LIBC_DIR=../../lib/c/
DEMO_DIR=../../demo/utilities/
OPT=-O3 -s -D_WinNT -L../../../_bin/ -lw32d

CSC4=C:/Windows/Microsoft.NET/Framework64/v4.0.30319/csc.exe

all:\
args\
cal\
clear\
fdump\
ffset\
\
segsel\


args:
	# args
	gcc ${DEMO_DIR}args.c -I${INCC_DIR} -o ${DEST_BIN}args.exe ${OPT}
cal:
	# cal
	gcc ${DEMO_DIR}calendar/calendar.c ${LIBC_DIR}datime/weekday.c -I${INCC_DIR} -o ${DEST_BIN}cal.exe ${OPT}
clear:
	# clear
	gcc ${DEMO_DIR}clear.c -I${INCC_DIR} -o ${DEST_BIN}clear.exe ${OPT}
fdump:
	# fdump
	gcc ${DEMO_DIR}filedump.c ${LIBC_DIR}consio.c -I${INCC_DIR} -o ${DEST_BIN}fdump.exe ${OPT}
ffset:
	# ffset
	gcc ${DEMO_DIR}VirtualDiskCopier/ffset.c -I${INCC_DIR} -o ${DEST_BIN}ffset.exe ${OPT}


outdated:
	# cmd /c move cal.exe ${DEST_BIN}

segsel:
	# OSDEV/SegmentSelector powered by DotNetFrameworkCS4
	cd ${DEMO_DIR}SegmentSelector && ${CSC4} /nologo /t:winexe /out:SegSel.exe *.cs
	mv ${DEMO_DIR}SegmentSelector/SegSel.exe ${DEST_BIN}SegSel.exe

elf: # readelf
	# readelf
	gcc ${DEMO_DIR}readelf.c ${LIBC_DIR}format/ELF.c -I${INCC_DIR} -o ${DEST_BIN}readelf.exe ${OPT}
