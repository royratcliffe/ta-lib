#############################################################################
# Makefile for building gen_rdata
# Generated by tmake;
#     Project: gen_rdata/gen_rdata
#    Template: app
#############################################################################

####### Compiler, tools and options

CC	=	cl
CXX	=	cl
CFLAGS	=	-nologo -W3 -MD -O1 -DWIN32 -D_MBCS -D_LIB -DQT_THREAD_SUPPORT
CXXFLAGS=	-nologo -W3 -MD -O1 -DWIN32 -D_MBCS -D_LIB -DQT_THREAD_SUPPORT
INCPATH	=	-I"..\..\..\..\..\src\ta_common" -I"..\..\..\..\..\src\ta_data\ta_source\ta_yahoo" -I"..\..\..\..\..\include" -I"..\..\..\..\..\src\ta_data\ta_source" -I"..\..\..\..\..\src\ta_data"
LINK	=	link
LFLAGS	=	/NOLOGO /SUBSYSTEM:console
LIBS	=	..\..\..\..\..\lib\ta_data_cdr.lib ..\..\..\..\..\lib\ta_common_cdr.lib wininet.lib odbc32.lib odbccp32.lib
MOC	=	moc
UIC	=	uic

ZIP	=	zip -r -9

####### Files

HEADERS =	
SOURCES =	..\..\..\..\..\src\tools\gen_rdata\gen_rdata.c
OBJECTS =	..\..\..\..\..\temp\cdr\gen_rdata.obj
INTERFACES =	
UICDECLS =	
UICIMPLS =	
SRCMOC	=	
OBJMOC	=	
DIST	=	
TARGET	=	..\..\..\..\..\bin\gen_rdata.exe
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

tmake: ../cdr/win32/msvc/gen_rdata/Makefile

../cdr/win32/msvc/gen_rdata/Makefile: gen_rdata/gen_rdata.pro
	tmake gen_rdata/gen_rdata.pro -o ../cdr/win32/msvc/gen_rdata/Makefile

dist:
	$(ZIP) gen_rdata/gen_rdata.zip gen_rdata/gen_rdata.pro $(SOURCES) $(HEADERS) $(DIST) $(INTERFACES)

clean:
        -del ..\..\..\..\..\temp\cdr\gen_rdata.obj
	-del $(TARGET)
	-del ../../../../../bin/*.map
	-del ../../../../../bin/*._xe
	-del ../../../../../bin/*.tds
	-del ../../../../../bin/*.pdb
	-del ../../../../../bin/*.pbo
	-del ../../../../../bin/*.pbi
	-del ../../../../../bin/*.pbt
	-del ../../../../../temp/cdr/*.pch
	-del ../../../../../temp/cdr/*.idb
	-del ../../../../../temp/cdr/gen_rdata/*.pch
	-del ../../../../../temp/cdr/gen_rdata/*.idb
	-del ../../../../../temp/cdr/gen_rdata/*.obj

####### Compile

..\..\..\..\..\temp\cdr\gen_rdata.obj: ..\..\..\..\..\src\tools\gen_rdata\gen_rdata.c
	$(CC) -c $(CFLAGS) $(INCPATH) -Fo..\..\..\..\..\temp\cdr\gen_rdata.obj ..\..\..\..\..\src\tools\gen_rdata\gen_rdata.c

