#############################################################################
# Makefile for building ta_yahoo
# Generated by tmake;
#     Project: ta_yahoo/ta_yahoo
#    Template: app
#############################################################################

####### Compiler, tools and options

CC	=	sc
CXX	=	sc
CFLAGS	=	-mn -w2 -g -DTA_DEBUG -D_DEBUG -DWIN32
CXXFLAGS=	-mn -w2 -g -DTA_DEBUG -D_DEBUG -DWIN32
INCPATH	=	-I"..\..\..\..\..\src\ta_common" -I"..\..\..\..\..\include" -I"..\..\..\..\..\src\ta_common\imatix\sfl"
LINK	=	link
LFLAGS	=	/NOLOGO /NOI /DEBUG /SUBSYSTEM:console
LIBS	=	..\..\..\..\..\lib\ta_libc_cmd.lib wininet.lib odbc32.lib
MOC	=	moc

ZIP	=	zip -r -9

####### Files

HEADERS =	
SOURCES =	..\..\..\..\..\src\demo\ta_yahoo\ta_yahoo.c
OBJECTS =	..\..\..\..\..\temp\cmd\ta_yahoo\ta_yahoo.obj
SRCMOC	=	
OBJMOC	=	
DIST	=	
TARGET	=	..\..\..\..\..\bin\ta_yahoo.exe

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
	$(LINK) $(LFLAGS) $(OBJECTS) $(OBJMOC), $(TARGET),, $(LIBS)

moc: $(SRCMOC)

tmake: ../cmd/win32/symantec/ta_yahoo/Makefile

../cmd/win32/symantec/ta_yahoo/Makefile: ta_yahoo/ta_yahoo.pro
	tmake ta_yahoo/ta_yahoo.pro -o ../cmd/win32/symantec/ta_yahoo/Makefile

dist:
	$(ZIP) ta_yahoo/ta_yahoo.zip ta_yahoo/ta_yahoo.pro $(SOURCES) $(HEADERS) $(DIST)

clean:
	-del ..\..\..\..\..\temp\cmd\ta_yahoo\ta_yahoo.obj
	-del $(TARGET)
	-del ../../../../../bin/*.map
	-del ../../../../../bin/*._xe
	-del ../../../../../bin/*.tds
	-del ../../../../../bin/*.pdb
	-del ../../../../../bin/*.pbo
	-del ../../../../../bin/*.pbi
	-del ../../../../../bin/*.pbt
	-del ../../../../../temp/cmd/*.pch
	-del ../../../../../temp/cmd/*.idb
	-del ../../../../../temp/cmd/ta_yahoo/*.pch
	-del ../../../../../temp/cmd/ta_yahoo/*.idb
	-del ../../../../../temp/cmd/ta_yahoo/*.obj

####### Compile

..\..\..\..\..\temp\cmd\ta_yahoo\ta_yahoo.obj: ..\..\..\..\..\src\demo\ta_yahoo\ta_yahoo.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o..\..\..\..\..\temp\cmd\ta_yahoo\ta_yahoo.obj ..\..\..\..\..\src\demo\ta_yahoo\ta_yahoo.c

