#############################################################################
# Makefile for building webfetch
# Generated by tmake;
#     Project: webfetch/webfetch
#    Template: app
#############################################################################

!if !$d(BCB)
BCB = $(MAKEDIR)\..
!endif

####### Compiler, tools and options

CC	=	bcc32
CXX	=	bcc32
CFLAGS	=	-x- -RT- -tWR -w -w-8004 -w-8071 -w-8057 -w-8080 -v -DTA_DEBUG -D_DEBUG -DTA_SINGLE_THREAD -DWIN32
CXXFLAGS=	-x- -RT- -tWR -w -w-8004 -w-8071 -w-8057 -w-8080 -v -DTA_DEBUG -D_DEBUG -DTA_SINGLE_THREAD -DWIN32
INCPATH	=	-I"..\..\..\..\..\src\ta_common" -I"..\..\..\..\..\include" -I"..\..\..\..\..\src\ta_common\imatix\sfl"
LINK	=	ilink32
LFLAGS	=	-L$(BCB)\lib -L$(BCB)\lib\PSDK -c -x -Gn -v -ap -Tpe c0x32.obj
LIBS	=	import32.lib cw32i.lib ..\..\..\..\..\lib\ta_libc_csd.lib wininet.lib odbc32.lib
MOC	=	moc
UIC	=	uic

ZIP	=	zip -r -9
DEF_FILE =	
RES_FILE =	

####### Files

HEADERS =	
SOURCES =	..\..\..\..\..\src\demo\webfetch\webfetch.c
OBJECTS =	..\..\..\..\..\temp\csd\webfetch\webfetch.obj
INTERFACES =	
UICDECLS =	
UICIMPLS =	
SRCMOC	=	
OBJMOC	=	
DIST	=	
TARGET	=	..\..\..\..\..\bin\webfetch.exe
INTERFACE_DECL_PATH = .

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

$(TARGET): $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	$(LINK) @&&|
	    $(LFLAGS) $(OBJECTS) $(OBJMOC),$(TARGET),,$(LIBS),$(DEF_FILE),$(RES_FILE)
|

moc: $(SRCMOC)

tmake: ../csd/win32/borland/webfetch/Makefile

../csd/win32/borland/webfetch/Makefile: webfetch/webfetch.pro
	tmake webfetch/webfetch.pro -o ../csd/win32/borland/webfetch/Makefile

dist:
	$(ZIP) webfetch/webfetch.zip webfetch/webfetch.pro $(SOURCES) $(HEADERS) $(DIST)

clean:
	-del ..\..\..\..\..\temp\csd\webfetch\webfetch.obj
	-del $(TARGET)
	-del webfetch.tds
	-del ../../../../../bin/*.map
	-del ../../../../../bin/*._xe
	-del ../../../../../bin/*.tds
	-del ../../../../../bin/*.pdb
	-del ../../../../../bin/*.pbo
	-del ../../../../../bin/*.pbi
	-del ../../../../../bin/*.pbt
	-del ../../../../../temp/csd/*.pch
	-del ../../../../../temp/csd/*.idb
	-del ../../../../../temp/csd/webfetch/*.pch
	-del ../../../../../temp/csd/webfetch/*.idb
	-del ../../../../../temp/csd/webfetch/*.obj

####### Compile

..\..\..\..\..\temp\csd\webfetch\webfetch.obj: ..\..\..\..\..\src\demo\webfetch\webfetch.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o..\..\..\..\..\temp\csd\webfetch\webfetch.obj ..\..\..\..\..\src\demo\webfetch\webfetch.c

