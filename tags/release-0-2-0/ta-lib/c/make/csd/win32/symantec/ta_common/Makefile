#############################################################################
# Makefile for building ta_common_csd
# Generated by tmake;
#     Project: ta_common/ta_common
#    Template: lib
#############################################################################

####### Compiler, tools and options

CC	=	sc
CXX	=	sc
CFLAGS	=	-mn -w2 -g -DTA_DEBUG -D_DEBUG -DTA_SINGLE_THREAD -DWIN32
CXXFLAGS=	-mn -w2 -g -DTA_DEBUG -D_DEBUG -DTA_SINGLE_THREAD -DWIN32
INCPATH	=	-I"..\..\..\..\..\src\ta_common" -I"..\..\..\..\..\src\ta_common\mt" -I"..\..\..\..\..\include"
LIB	=	lib /C /N /NOI /P:32
MOC	=	moc

ZIP	=	zip -r -9

####### Files

HEADERS =	
SOURCES =	..\..\..\..\..\src\ta_common\trio\trionan.c \
		..\..\..\..\..\src\ta_common\ta_global.c \
		..\..\..\..\..\src\ta_common\ta_retcode.c \
		..\..\..\..\..\src\ta_common\ta_version.c \
		..\..\..\..\..\src\ta_common\ta_random.c \
		..\..\..\..\..\src\ta_common\mt\mt19937ar.c
OBJECTS =	..\..\..\..\..\temp\csd\trionan.obj \
		..\..\..\..\..\temp\csd\ta_global.obj \
		..\..\..\..\..\temp\csd\ta_retcode.obj \
		..\..\..\..\..\temp\csd\ta_version.obj \
		..\..\..\..\..\temp\csd\ta_random.obj \
		..\..\..\..\..\temp\csd\mt19937ar.obj
SRCMOC	=	
OBJMOC	=	
DIST	=	
TARGET	=	..\..\..\..\..\lib\ta_common_csd.lib

####### Implicit rules

.SUFFIXES: .cpp .cxx .cc .c

.cpp.obj:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o$@ $<

.cxx.obj:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o$@ $<

.cc.obj:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o$@ $<

.c.obj:
	$(CC) -c $(CFLAGS) $(INCPATH) -o$@ $<

####### Build rules

all: $(TARGET)

$(TARGET): $(OBJECTS) $(OBJMOC) 
	-del $(TARGET)
	$(LIB) $(TARGET) ..\..\..\..\..\temp\csd\trionan.obj \
+..\..\..\..\..\temp\csd\ta_global.obj \
+..\..\..\..\..\temp\csd\ta_retcode.obj \
+..\..\..\..\..\temp\csd\ta_version.obj \
+..\..\..\..\..\temp\csd\ta_random.obj \
+..\..\..\..\..\temp\csd\mt19937ar.obj \
+,;

moc: $(SRCMOC)

tmake: ../csd/win32/symantec/ta_common/Makefile

../csd/win32/symantec/ta_common/Makefile: ta_common/ta_common.pro
	tmake ta_common/ta_common.pro -o ../csd/win32/symantec/ta_common/Makefile

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
	$(CC) -c $(CFLAGS) $(INCPATH) -o..\..\..\..\..\temp\csd\trionan.obj ..\..\..\..\..\src\ta_common\trio\trionan.c

..\..\..\..\..\temp\csd\ta_global.obj: ..\..\..\..\..\src\ta_common\ta_global.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o..\..\..\..\..\temp\csd\ta_global.obj ..\..\..\..\..\src\ta_common\ta_global.c

..\..\..\..\..\temp\csd\ta_retcode.obj: ..\..\..\..\..\src\ta_common\ta_retcode.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o..\..\..\..\..\temp\csd\ta_retcode.obj ..\..\..\..\..\src\ta_common\ta_retcode.c

..\..\..\..\..\temp\csd\ta_version.obj: ..\..\..\..\..\src\ta_common\ta_version.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o..\..\..\..\..\temp\csd\ta_version.obj ..\..\..\..\..\src\ta_common\ta_version.c

..\..\..\..\..\temp\csd\ta_random.obj: ..\..\..\..\..\src\ta_common\ta_random.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o..\..\..\..\..\temp\csd\ta_random.obj ..\..\..\..\..\src\ta_common\ta_random.c

..\..\..\..\..\temp\csd\mt19937ar.obj: ..\..\..\..\..\src\ta_common\mt\mt19937ar.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o..\..\..\..\..\temp\csd\mt19937ar.obj ..\..\..\..\..\src\ta_common\mt\mt19937ar.c

