#############################################################################
# Makefile for building webfetch
# Generated by tmake at 23:39, 2003/09/23
#     Project: webfetch/webfetch
#    Template: app
#############################################################################

####### Compiler, tools and options

CC	=	g++
CXX	=	gcc
CFLAGS	=	-fvtable-thunks -O -DTA_SINGLE_THREAD -DWIN32
CXXFLAGS=	-fvtable-thunks -O -DTA_SINGLE_THREAD -DWIN32
INCPATH	=	-I"../../../../../src/ta_common" -I"../../../../../include" -I"../../../../../src/ta_common/imatix/sfl"
LINK	=	g++
LFLAGS	=	-Wl,-subsystem,console
LIBS	=	../../../../../lib/ta_libc_csr.lib wininet.lib
MOC	=	moc
UIC	=	

ZIP	=	zip -r -9

####### Files

HEADERS =	
SOURCES =	../../../../../src/demo/webfetch/webfetch.c
OBJECTS =	../../../../../temp/csr/webfetch/webfetch.o
INTERFACES =	
UICDECLS =	
UICIMPLS =	
SRCMOC	=	
OBJMOC	=	
DIST	=	
TARGET	=	../../../../../bin/webfetch.exe
INTERFACE_DECL_PATH = .

####### Implicit rules

.SUFFIXES: .cpp .cxx .cc .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: $(TARGET)

$(TARGET): $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(LIBS)

moc: $(SRCMOC)

tmake: ../csr/win32/g++/webfetch/Makefile

../csr/win32/g++/webfetch/Makefile: webfetch/webfetch.pro
	tmake webfetch/webfetch.pro -o ../csr/win32/g++/webfetch/Makefile

dist:
	$(ZIP) webfetch/webfetch.zip webfetch/webfetch.pro $(SOURCES) $(HEADERS) $(DIST)

clean:
	-rm -f $(OBJECTS) $(OBJMOC) $(SRCMOC) $(TARGET)
	-rm -f *~ core
	-rm -f ../../../../../bin/*.map ../../../../../bin/*._xe ../../../../../bin/*.tds ../../../../../bin/*.pdb ../../../../../bin/*.pbo ../../../../../bin/*.pbi ../../../../../bin/*.pbt ../../../../../temp/csr/*.pch ../../../../../temp/csr/*.idb ../../../../../temp/csr/webfetch/*.pch ../../../../../temp/csr/webfetch/*.idb ../../../../../temp/csr/webfetch/*.obj

####### Compile

../../../../../temp/csr/webfetch/webfetch.o: ../../../../../src/demo/webfetch/webfetch.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o ../../../../../temp/csr/webfetch/webfetch.o ../../../../../src/demo/webfetch/webfetch.c

