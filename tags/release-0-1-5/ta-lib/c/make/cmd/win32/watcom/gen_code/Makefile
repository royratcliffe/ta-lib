#############################################################################
# Makefile for building gen_code
# Generated by tmake;
#     Project: gen_code/gen_code
#    Template: app
#############################################################################

####### Compiler, tools and options

CC	=	wcl386
CXX	=	wcl386
CFLAGS	=	-zq -w2 -d2 -d=TA_GEN_CODE -d=TA_DEBUG -d=_DEBUG -d=WIN32
CXXFLAGS=	-zq -w2 -d2 -d=TA_GEN_CODE -d=TA_DEBUG -d=_DEBUG -d=WIN32
INCPATH	=	-i="..\..\..\..\..\include" -i="..\..\..\..\..\src\ta_common" -i="..\..\..\..\..\src\ta_common\imatix\sfl" -i="..\..\..\..\..\src\ta_common\kazlib" -i="..\..\..\..\..\src\ta_abstract" -i="..\..\..\..\..\src\ta_abstract\tables" -i="..\..\..\..\..\src\ta_abstract\frames"
LINK	=	wlink
LFLAGS	=	op quiet op c d all sys nt
LIBS	=	..\..\..\..\..\lib\ta_common_cmd.lib wininet.lib odbc32.lib
MOC	=	moc

ZIP	=	zip -r -9

####### Files

HEADERS =	
SOURCES =	..\..\..\..\..\src\tools\gen_code\gen_code.c &
		..\..\..\..\..\src\ta_abstract\ta_abstract.c &
		..\..\..\..\..\src\ta_abstract\ta_def_ui.c &
		..\..\..\..\..\src\ta_abstract\tables\table_a.c &
		..\..\..\..\..\src\ta_abstract\tables\table_b.c &
		..\..\..\..\..\src\ta_abstract\tables\table_c.c &
		..\..\..\..\..\src\ta_abstract\tables\table_d.c &
		..\..\..\..\..\src\ta_abstract\tables\table_e.c &
		..\..\..\..\..\src\ta_abstract\tables\table_f.c &
		..\..\..\..\..\src\ta_abstract\tables\table_g.c &
		..\..\..\..\..\src\ta_abstract\tables\table_h.c &
		..\..\..\..\..\src\ta_abstract\tables\table_i.c &
		..\..\..\..\..\src\ta_abstract\tables\table_j.c &
		..\..\..\..\..\src\ta_abstract\tables\table_k.c &
		..\..\..\..\..\src\ta_abstract\tables\table_l.c &
		..\..\..\..\..\src\ta_abstract\tables\table_m.c &
		..\..\..\..\..\src\ta_abstract\tables\table_n.c &
		..\..\..\..\..\src\ta_abstract\tables\table_o.c &
		..\..\..\..\..\src\ta_abstract\tables\table_p.c &
		..\..\..\..\..\src\ta_abstract\tables\table_q.c &
		..\..\..\..\..\src\ta_abstract\tables\table_r.c &
		..\..\..\..\..\src\ta_abstract\tables\table_s.c &
		..\..\..\..\..\src\ta_abstract\tables\table_t.c &
		..\..\..\..\..\src\ta_abstract\tables\table_u.c &
		..\..\..\..\..\src\ta_abstract\tables\table_v.c &
		..\..\..\..\..\src\ta_abstract\tables\table_w.c &
		..\..\..\..\..\src\ta_abstract\tables\table_x.c &
		..\..\..\..\..\src\ta_abstract\tables\table_y.c &
		..\..\..\..\..\src\ta_abstract\tables\table_z.c
OBJECTS =	..\..\..\..\..\temp\cmd\gen_code\gen_code.obj &
		..\..\..\..\..\temp\cmd\gen_code\ta_abstract.obj &
		..\..\..\..\..\temp\cmd\gen_code\ta_def_ui.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_a.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_b.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_c.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_d.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_e.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_f.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_g.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_h.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_i.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_j.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_k.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_l.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_m.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_n.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_o.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_p.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_q.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_r.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_s.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_t.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_u.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_v.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_w.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_x.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_y.obj &
		..\..\..\..\..\temp\cmd\gen_code\table_z.obj
SRCMOC	=	
OBJMOC	=	
DIST	=	
TARGET	=	..\..\..\..\..\bin\gen_code.exe
TMPLIST =	gen_code.lst

####### Build rules

all: $(TARGET)

$(TARGET): $(OBJECTS) $(OBJMOC) 
	@%create $(TMPLIST)
	@%append $(TMPLIST) NAME gen_code
	@%append $(TMPLIST) FIL ..\..\..\..\..\temp\cmd\gen_code\gen_code.obj,..\..\..\..\..\temp\cmd\gen_code\ta_abstract.obj,..\..\..\..\..\temp\cmd\gen_code\ta_def_ui.obj,..\..\..\..\..\temp\cmd\gen_code\table_a.obj,..\..\..\..\..\temp\cmd\gen_code\table_b.obj,..\..\..\..\..\temp\cmd\gen_code\table_c.obj,..\..\..\..\..\temp\cmd\gen_code\table_d.obj,..\..\..\..\..\temp\cmd\gen_code\table_e.obj,..\..\..\..\..\temp\cmd\gen_code\table_f.obj,..\..\..\..\..\temp\cmd\gen_code\table_g.obj,..\..\..\..\..\temp\cmd\gen_code\table_h.obj,..\..\..\..\..\temp\cmd\gen_code\table_i.obj,..\..\..\..\..\temp\cmd\gen_code\table_j.obj,..\..\..\..\..\temp\cmd\gen_code\table_k.obj,..\..\..\..\..\temp\cmd\gen_code\table_l.obj,..\..\..\..\..\temp\cmd\gen_code\table_m.obj,..\..\..\..\..\temp\cmd\gen_code\table_n.obj,..\..\..\..\..\temp\cmd\gen_code\table_o.obj,..\..\..\..\..\temp\cmd\gen_code\table_p.obj,..\..\..\..\..\temp\cmd\gen_code\table_q.obj,..\..\..\..\..\temp\cmd\gen_code\table_r.obj,..\..\..\..\..\temp\cmd\gen_code\table_s.obj,..\..\..\..\..\temp\cmd\gen_code\table_t.obj,..\..\..\..\..\temp\cmd\gen_code\table_u.obj,..\..\..\..\..\temp\cmd\gen_code\table_v.obj,..\..\..\..\..\temp\cmd\gen_code\table_w.obj,..\..\..\..\..\temp\cmd\gen_code\table_x.obj,..\..\..\..\..\temp\cmd\gen_code\table_y.obj,..\..\..\..\..\temp\cmd\gen_code\table_z.obj
	@%append $(TMPLIST) LIBR ..\..\..\..\..\lib\ta_common_cmd.lib,wininet.lib,odbc32.lib
	$(LINK) $(LFLAGS) @$(TMPLIST)
	del $(TMPLIST)

moc: $(SRCMOC)

tmake: ../cmd/win32/watcom/gen_code/Makefile

../cmd/win32/watcom/gen_code/Makefile: gen_code/gen_code.pro
	tmake gen_code/gen_code.pro -o ../cmd/win32/watcom/gen_code/Makefile

dist:
	$(ZIP) gen_code/gen_code.zip gen_code/gen_code.pro $(SOURCES) $(HEADERS) $(DIST)

clean:
	-del ..\..\..\..\..\temp\cmd\gen_code\gen_code.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\ta_abstract.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\ta_def_ui.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_a.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_b.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_c.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_d.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_e.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_f.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_g.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_h.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_i.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_j.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_k.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_l.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_m.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_n.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_o.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_p.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_q.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_r.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_s.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_t.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_u.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_v.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_w.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_x.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_y.obj
	-del ..\..\..\..\..\temp\cmd\gen_code\table_z.obj
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
	-del ../../../../../temp/cmd/gen_code/*.pch
	-del ../../../../../temp/cmd/gen_code/*.idb
	-del ../../../../../temp/cmd/gen_code/*.obj

####### Compile

..\..\..\..\..\temp\cmd\gen_code\gen_code.obj: ..\..\..\..\..\src\tools\gen_code\gen_code.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\gen_code.obj ..\..\..\..\..\src\tools\gen_code\gen_code.c

..\..\..\..\..\temp\cmd\gen_code\ta_abstract.obj: ..\..\..\..\..\src\ta_abstract\ta_abstract.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\ta_abstract.obj ..\..\..\..\..\src\ta_abstract\ta_abstract.c

..\..\..\..\..\temp\cmd\gen_code\ta_def_ui.obj: ..\..\..\..\..\src\ta_abstract\ta_def_ui.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\ta_def_ui.obj ..\..\..\..\..\src\ta_abstract\ta_def_ui.c

..\..\..\..\..\temp\cmd\gen_code\table_a.obj: ..\..\..\..\..\src\ta_abstract\tables\table_a.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_a.obj ..\..\..\..\..\src\ta_abstract\tables\table_a.c

..\..\..\..\..\temp\cmd\gen_code\table_b.obj: ..\..\..\..\..\src\ta_abstract\tables\table_b.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_b.obj ..\..\..\..\..\src\ta_abstract\tables\table_b.c

..\..\..\..\..\temp\cmd\gen_code\table_c.obj: ..\..\..\..\..\src\ta_abstract\tables\table_c.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_c.obj ..\..\..\..\..\src\ta_abstract\tables\table_c.c

..\..\..\..\..\temp\cmd\gen_code\table_d.obj: ..\..\..\..\..\src\ta_abstract\tables\table_d.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_d.obj ..\..\..\..\..\src\ta_abstract\tables\table_d.c

..\..\..\..\..\temp\cmd\gen_code\table_e.obj: ..\..\..\..\..\src\ta_abstract\tables\table_e.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_e.obj ..\..\..\..\..\src\ta_abstract\tables\table_e.c

..\..\..\..\..\temp\cmd\gen_code\table_f.obj: ..\..\..\..\..\src\ta_abstract\tables\table_f.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_f.obj ..\..\..\..\..\src\ta_abstract\tables\table_f.c

..\..\..\..\..\temp\cmd\gen_code\table_g.obj: ..\..\..\..\..\src\ta_abstract\tables\table_g.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_g.obj ..\..\..\..\..\src\ta_abstract\tables\table_g.c

..\..\..\..\..\temp\cmd\gen_code\table_h.obj: ..\..\..\..\..\src\ta_abstract\tables\table_h.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_h.obj ..\..\..\..\..\src\ta_abstract\tables\table_h.c

..\..\..\..\..\temp\cmd\gen_code\table_i.obj: ..\..\..\..\..\src\ta_abstract\tables\table_i.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_i.obj ..\..\..\..\..\src\ta_abstract\tables\table_i.c

..\..\..\..\..\temp\cmd\gen_code\table_j.obj: ..\..\..\..\..\src\ta_abstract\tables\table_j.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_j.obj ..\..\..\..\..\src\ta_abstract\tables\table_j.c

..\..\..\..\..\temp\cmd\gen_code\table_k.obj: ..\..\..\..\..\src\ta_abstract\tables\table_k.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_k.obj ..\..\..\..\..\src\ta_abstract\tables\table_k.c

..\..\..\..\..\temp\cmd\gen_code\table_l.obj: ..\..\..\..\..\src\ta_abstract\tables\table_l.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_l.obj ..\..\..\..\..\src\ta_abstract\tables\table_l.c

..\..\..\..\..\temp\cmd\gen_code\table_m.obj: ..\..\..\..\..\src\ta_abstract\tables\table_m.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_m.obj ..\..\..\..\..\src\ta_abstract\tables\table_m.c

..\..\..\..\..\temp\cmd\gen_code\table_n.obj: ..\..\..\..\..\src\ta_abstract\tables\table_n.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_n.obj ..\..\..\..\..\src\ta_abstract\tables\table_n.c

..\..\..\..\..\temp\cmd\gen_code\table_o.obj: ..\..\..\..\..\src\ta_abstract\tables\table_o.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_o.obj ..\..\..\..\..\src\ta_abstract\tables\table_o.c

..\..\..\..\..\temp\cmd\gen_code\table_p.obj: ..\..\..\..\..\src\ta_abstract\tables\table_p.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_p.obj ..\..\..\..\..\src\ta_abstract\tables\table_p.c

..\..\..\..\..\temp\cmd\gen_code\table_q.obj: ..\..\..\..\..\src\ta_abstract\tables\table_q.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_q.obj ..\..\..\..\..\src\ta_abstract\tables\table_q.c

..\..\..\..\..\temp\cmd\gen_code\table_r.obj: ..\..\..\..\..\src\ta_abstract\tables\table_r.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_r.obj ..\..\..\..\..\src\ta_abstract\tables\table_r.c

..\..\..\..\..\temp\cmd\gen_code\table_s.obj: ..\..\..\..\..\src\ta_abstract\tables\table_s.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_s.obj ..\..\..\..\..\src\ta_abstract\tables\table_s.c

..\..\..\..\..\temp\cmd\gen_code\table_t.obj: ..\..\..\..\..\src\ta_abstract\tables\table_t.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_t.obj ..\..\..\..\..\src\ta_abstract\tables\table_t.c

..\..\..\..\..\temp\cmd\gen_code\table_u.obj: ..\..\..\..\..\src\ta_abstract\tables\table_u.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_u.obj ..\..\..\..\..\src\ta_abstract\tables\table_u.c

..\..\..\..\..\temp\cmd\gen_code\table_v.obj: ..\..\..\..\..\src\ta_abstract\tables\table_v.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_v.obj ..\..\..\..\..\src\ta_abstract\tables\table_v.c

..\..\..\..\..\temp\cmd\gen_code\table_w.obj: ..\..\..\..\..\src\ta_abstract\tables\table_w.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_w.obj ..\..\..\..\..\src\ta_abstract\tables\table_w.c

..\..\..\..\..\temp\cmd\gen_code\table_x.obj: ..\..\..\..\..\src\ta_abstract\tables\table_x.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_x.obj ..\..\..\..\..\src\ta_abstract\tables\table_x.c

..\..\..\..\..\temp\cmd\gen_code\table_y.obj: ..\..\..\..\..\src\ta_abstract\tables\table_y.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_y.obj ..\..\..\..\..\src\ta_abstract\tables\table_y.c

..\..\..\..\..\temp\cmd\gen_code\table_z.obj: ..\..\..\..\..\src\ta_abstract\tables\table_z.c
	$(CC) -c $(CFLAGS) $(INCPATH) -fo=..\..\..\..\..\temp\cmd\gen_code\table_z.obj ..\..\..\..\..\src\ta_abstract\tables\table_z.c

