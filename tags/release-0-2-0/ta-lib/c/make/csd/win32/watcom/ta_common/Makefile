#############################################################################
# Makefile for building ta_common_csd
# Generated by tmake;
#     Project: ta_common/ta_common
#    Template: lib
#############################################################################

####### Compiler, tools and options

CC	=	wcl386
CXX	=	wcl386
CFLAGS	=	-zq -w2 -d2 -d=TA_DEBUG -d=_DEBUG -d=TA_SINGLE_THREAD -d=WIN32
CXXFLAGS=	-zq -w2 -d2 -d=TA_DEBUG -d=_DEBUG -d=TA_SINGLE_THREAD -d=WIN32
INCPATH	=	-i="..\..\..\..\..\src\ta_common" -i="..\..\..\..\..\src\ta_common\mt" -i="..\..\..\..\..\include"
LIB	=	wlib -b -c -n -q -p=512
MOC	=	moc

ZIP	=	zip -r -9

####### Files

HEADERS =	
SOURCES =	..\..\..\..\..\src\ta_common\trio\trionan.c &
		..\..\..\..\..\src\ta_common\ta_global.c &
		..\..\..\..\..\src\ta_common\ta_retcode.c &
		..\..\..\..\..\src\ta_common\ta_version.c &
		..\..\..\..\..\src\ta_common\ta_random.c &
		..\..\..\..\..\src\ta_common\mt\mt19937ar.c
OBJECTS =	..\..\..\..\..\temp\csd\trionan.obj &
		..\..\..\..\..\temp\csd\ta_global.obj &
		..\..\..\..\..\temp\csd\ta_retcode.obj &
		..\..\..\..\..\temp\csd\ta_version.obj &
		..\..\..\..\..\temp\csd\ta_random.obj &
		..\..\..\..\..\temp\csd\mt19937ar.obj
SRCMOC	=	
OBJMOC	=	
DIST	=	
TARGET	=	..\..\..\..\..\lib\ta_common_csd.lib
TMPLIST =	ta_common_csd.lst

####### Build rules

all: $(TARGET)

$(TARGET): $(OBJECTS) $(OBJMOC) 
	@%create $(TMPLIST)
	@for %i in ( $(OBJECTS) $(OBJMOC) ) do @%append $(TMPLIST) +'%i'
	$(LIB) $(TARGET) @$(TMPLIST)
	del $(TMPLIST)

moc: $(SRCMOC)

tmake: ../csd/win32/watcom/ta_common/Makefile

../csd/win32/watcom/ta_common/Makefile: ta_common/ta_common.pro
	tmake ta_common/ta_common.pro -o ../csd/win32/watcom/ta_common/Makefile

dist:
	$(ZIP) ta_common/ta_common.zip ta_common/ta_common.pro $(SOURCES) $(HEADERS) $(DIST)

clean:
	-del ..\..\..\..\..\temp\csd\trionan.obj
	-del ..\..\..\..\..\temp\csd\ta_global.obj
	-del ..\..\..\..\..\temp\csd\ta_retcode.obj
	-del ..\..\..\..\..\temp\csd\ta_version.obj
	-del ..\..\..\..\..\temp\csd\ta_random.obj
	-del ..\..\..\..\..\temp\csd\mt19937ar.obj
	-del $(TARGET)
	-del ../../../../../bin/*.map
	-del ../../../../../bin/*._xe
	-del ../../../../../bin/*.tds
	-del ../../../../../bin/*.pdb
	-del ../../../../../bin/*.pbo
	-del ../../../../../bin/*.pbi
	-del ../../../../../bin/*.pbt
	-del ../../../../../temp/csd/*.pch
	-del ../../../../../temp/csd/*.idb
	-del ../../../../../temp/csd/ta_common_csd/*.pch
	-del ../../../../../temp/csd/ta_common_csd/*.idb
	-del ../../../../../temp/csd/ta_common_csd/*.obj

####### Compile

..\..\..\..\..\temp\csd\trionan.obj: ..\..\..\..\..\src\ta_common\trio\trionan.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\csd\trionan.obj ..\..\..\..\..\src\ta_common\trio\trionan.c

..\..\..\..\..\temp\csd\ta_global.obj: ..\..\..\..\..\src\ta_common\ta_global.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\csd\ta_global.obj ..\..\..\..\..\src\ta_common\ta_global.c

..\..\..\..\..\temp\csd\ta_retcode.obj: ..\..\..\..\..\src\ta_common\ta_retcode.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\csd\ta_retcode.obj ..\..\..\..\..\src\ta_common\ta_retcode.c

..\..\..\..\..\temp\csd\ta_version.obj: ..\..\..\..\..\src\ta_common\ta_version.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\csd\ta_version.obj ..\..\..\..\..\src\ta_common\ta_version.c

..\..\..\..\..\temp\csd\ta_random.obj: ..\..\..\..\..\src\ta_common\ta_random.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\csd\ta_random.obj ..\..\..\..\..\src\ta_common\ta_random.c

..\..\..\..\..\temp\csd\mt19937ar.obj: ..\..\..\..\..\src\ta_common\mt\mt19937ar.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\csd\mt19937ar.obj ..\..\..\..\..\src\ta_common\mt\mt19937ar.c

