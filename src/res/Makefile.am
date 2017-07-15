CXXFLAGS += $(SDL_CFLAGS) -DDEBUG -DENABLE_LOG
noinst_LIBRARIES = lib7kaaRes.a
lib7kaaRes_a_SOURCES = \
	OFIRMRES.cpp \
	OGODRES.cpp \
	OHILLRES.cpp \
	OIMGRES.cpp \
	OMONSRES.cpp \
	ORACERES.cpp \
	ORAWRES.cpp \
	ORES.cpp \
	ORESDB.cpp \
	ORESX.cpp \
	OROCKRES.cpp \
	OSERES.cpp \
	OSFRMRES.cpp \
	OSNOWRES.cpp \
	OSPRTRES.cpp \
	OTALKRES.cpp \
	OTECHRES.cpp \
	OTOWNRES.cpp \
	OUNITRES.cpp \
	OWALLRES.cpp 

lib7kaaRes_a_LIBADD = 

if USE_ASM
lib7kaaRes_a_LIBADD += ../imgfun/x86/libimgfun_x86.a
else
lib7kaaRes_a_LIBADD += ../imgfun/generic/libimgfun_generic.a
endif
