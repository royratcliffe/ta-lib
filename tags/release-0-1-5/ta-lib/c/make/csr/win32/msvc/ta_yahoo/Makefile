#############################################################################
# Makefile for building ta_yahoo
# Generated by tmake;
#     Project: ta_yahoo/ta_yahoo
#    Template: app
#############################################################################

####### Compiler, tools and options

CC	=	cl
CXX	=	cl
CFLAGS	=	-nologo -W3 -O1 -DTA_SINGLE_THREAD -DWIN32 -D_MBCS -D_LIB
CXXFLAGS=	-nologo -W3 -O1 -DTA_SINGLE_THREAD -DWIN32 -D_MBCS -D_LIB
INCPATH	=	-I"..\..\..\..\..\src\ta_common" -I"..\..\..\..\..\include" -I"..\..\..\..\..\src\ta_common\imatix\sfl"
LINK	=	link
LFLAGS	=	/NOLOGO /SUBSYSTEM:console
LIBS	=	..\..\..\..\..\lib\ta_libc_csr.lib wininet.lib odbc32.lib odbccp32.lib
MOC	=	moc
UIC	=	uic

ZIP	=	zip -r -9

####### Files

HEADERS =	
SOURCES =	..\..\..\..\..\src\demo\ta_yahoo\ta_yahoo.c
OBJECTS =	..\..\..\..\..\temp\csr\ta_yahoo\ta_yahoo.obj
INTERFACES =	
UICDECLS =	
UICIMPLS =	
SRCMOC	=	
OBJMOC	=	
DIST	=	
TARGET	=	..\..\..\..\..\bin\ta_yahoo.exe
INTERFACE_DECL_PATH = .

####### Implicit rules

.SUFFIXES: .cpp .cxx .cc .c

.cpp.obj:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -Fo$@ $<

.cxx.obj:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -Fo$@ $<

.cc.obj:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -Fo$@ $<

.c.obj:
	$(CC) -c $(CFLAGS) $(INCPATH) -Fo$@ $<

####### Build rules

all: $(TARGET)

$(TARGET): $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	$(LINK) $(LFLAGS) /OUT:$(TARGET) @<<
	    $(OBJECTS) $(OBJMOC) $(LIBS)
<<

moc: $(SRCMOC)

tmake: ../csr/win32/msvc/ta_yahoo/Makefile

../csr/win32/msvc/ta_yahoo/Makefile: ta_yahoo/ta_yahoo.pro
	tmake ta_yahoo/ta_yahoo.pro -o ../csr/win32/msvc/ta_yahoo/Makefile

dist:
	$(ZIP) ta_yahoo/ta_yahoo.zip ta_yahoo/ta_yahoo.pro $(SOURCES) $(HEADERS) $(DIST) $(INTERFACES)

clean:
        -del ..\..\..\..\..\temp\csr\ta_yahoo\ta_yahoo.obj
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
	-del ../../../../../temp/csr/ta_yahoo/*.pch
	-del ../../../../../temp/csr/ta_yahoo/*.idb
	-del ../../../../../temp/csr/ta_yahoo/*.obj

####### Compile

..\..\..\..\..\temp\csr\ta_yahoo\ta_yahoo.obj: ..\..\..\..\..\src\demo\ta_yahoo\ta_yahoo.c
	$(CC) -c $(CFLAGS) $(INCPATH) -Fo..\..\..\..\..\temp\csr\ta_yahoo\ta_yahoo.obj ..\..\..\..\..\src\demo\ta_yahoo\ta_yahoo.c

