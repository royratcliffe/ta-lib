#############################################################################
# Makefile for building ta_sql
# Generated by tmake;
#     Project: ta_sql/ta_sql
#    Template: app
#############################################################################

####### Compiler, tools and options

CC	=	wcl386
CXX	=	wcl386
CFLAGS	=	-zq -w2 -ox -d=TA_SINGLE_THREAD -d=WIN32
CXXFLAGS=	-zq -w2 -ox -d=TA_SINGLE_THREAD -d=WIN32
INCPATH	=	-i="..\..\..\..\..\src\ta_common" -i="..\..\..\..\..\include" -i="..\..\..\..\..\src\ta_common\imatix\sfl"
LINK	=	wlink
LFLAGS	=	op quiet op c sys nt
LIBS	=	..\..\..\..\..\lib\ta_libc_csr.lib wininet.lib odbc32.lib
MOC	=	moc

ZIP	=	zip -r -9

####### Files

HEADERS =	
SOURCES =	..\..\..\..\..\src\demo\ta_sql\ta_sql.c
OBJECTS =	..\..\..\..\..\temp\csr\ta_sql\ta_sql.obj
SRCMOC	=	
OBJMOC	=	
DIST	=	
TARGET	=	..\..\..\..\..\bin\ta_sql.exe
TMPLIST =	ta_sql.lst

####### Build rules

all: $(TARGET)

$(TARGET): $(OBJECTS) $(OBJMOC) 
	@%create $(TMPLIST)
	@%append $(TMPLIST) NAME ta_sql
	@%append $(TMPLIST) FIL ..\..\..\..\..\temp\csr\ta_sql\ta_sql.obj
	@%append $(TMPLIST) LIBR ..\..\..\..\..\lib\ta_libc_csr.lib,wininet.lib,odbc32.lib
	$(LINK) $(LFLAGS) @$(TMPLIST)
	del $(TMPLIST)

moc: $(SRCMOC)

tmake: ../csr/win32/watcom/ta_sql/Makefile

../csr/win32/watcom/ta_sql/Makefile: ta_sql/ta_sql.pro
	tmake ta_sql/ta_sql.pro -o ../csr/win32/watcom/ta_sql/Makefile

dist:
	$(ZIP) ta_sql/ta_sql.zip ta_sql/ta_sql.pro $(SOURCES) $(HEADERS) $(DIST)

clean:
	-del ..\..\..\..\..\temp\csr\ta_sql\ta_sql.obj
	-del $(TARGET)
	-del ../../../../../bin/*.map
	-del ../../../../../bin/*._xe
	-del ../../../../../bin/*.tds
	-del ../../../../../bin/*.pdb
	-del ../../../../../bin/*.pbo
	-del ../../../../../bin/*.pbi
	-del ../../../../../bin/*.pbt
	-del ../../../../../temp/csr/*.pch
	-del ../../../../../temp/csr/*.idb
	-del ../../../../../temp/csr/ta_sql/*.pch
	-del ../../../../../temp/csr/ta_sql/*.idb
	-del ../../../../../temp/csr/ta_sql/*.obj

####### Compile

..\..\..\..\..\temp\csr\ta_sql\ta_sql.obj: ..\..\..\..\..\src\demo\ta_sql\ta_sql.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\csr\ta_sql\ta_sql.obj ..\..\..\..\..\src\demo\ta_sql\ta_sql.c

