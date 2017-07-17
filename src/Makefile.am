SUBDIRS = enet imgfun openal
if USE_CURL
SUBDIRS += curl
endif
SUBDIRS += core res gamedata ai graf rmsg ui

TESTS = 7kaaTestApp
check_PROGRAMS = $(TESTS)

bin_PROGRAMS = 7kaa
7kaa_base_SOURCES = \
	OGFILE.cpp \
	OGFILE2.cpp \
	OGFILE3.cpp \
	OGFILEA.cpp \
	OGF_V1.cpp \
	OGJSON.cpp 

CXXFLAGS += $(SDL_CFLAGS) -DDEBUG -DENABLE_LOG

7kaa_LDADD =

#7kaa_LDADD += ./ai/lib7kaaAI.a
7kaa_LDADD += ./gamedata/lib7kaaGameData.a
7kaa_LDADD += ./core/lib7kaaCore.a
7kaa_LDADD += ./graf/lib7kaaGraf.a
7kaa_LDADD += ./res/lib7kaaRes.a
7kaa_LDADD += ./ui/lib7kaaUI.a
7kaa_LDADD += ./rmsg/lib7kaaRmsg.a

if AUDIO_OPENAL
7kaa_LDADD += ./openal/libaudio_openal.a
endif

7kaa_LDADD += ./enet/libmultiplayer.a

if USE_ASM
7kaa_LDADD += ./imgfun/x86/libimgfun_x86.a
else
7kaa_LDADD += ./imgfun/generic/libimgfun_generic.a
endif

7kaa_LDADD += @LIBINTL@

if USE_CURL
7kaa_LDADD += ./curl/libWebService.a
7kaa_LDADD += @LIBCURL@
endif

if USE_WINDOWS
7kaa_base_SOURCES += ico.rc
SUFFIXES = .rc
.rc.o:
	windres -I "$(top_srcdir)/include" -i $< $@
ico.o: $(top_srcdir)/include/version.h 7k.ico
endif

7kaaTestApp_SOURCES = \
	$(7kaa_base_SOURCES) \
	OGAMESTATETest.cpp \
	OCONFIGTest.cpp \
	OGJSONTest.cpp \
	7kaaTestApp.cpp

7kaa_SOURCES = $(7kaa_base_SOURCES) AM.cpp

7kaaTestApp_CXXFLAGS = $(CXXFLAGS) $(CPPUNIT_CFLAGS) -fPIC

7kaaTestApp_LDADD = $(7kaa_LDADD) $(CPPUNIT_LIBS) -LLIBDIR -lrestclient-cpp

#7kaaTestApp_LDFLAGS = -RLIBDIR

EXTRA_DIST = 7k.ico ico.rc
