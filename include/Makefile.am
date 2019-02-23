include_HEADERS = \
	libvsgpt.h

pkginclude_HEADERS = \
	libvsgpt/codepage.h \
	libvsgpt/definitions.h \
	libvsgpt/error.h \
	libvsgpt/extern.h \
	libvsgpt/features.h \
	libvsgpt/types.h

EXTRA_DIST = \
	libvsgpt.h.in \
	libvsgpt/definitions.h.in \
	libvsgpt/features.h.in \
	libvsgpt/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libvsgpt.h
	/bin/rm -f libvsgpt/definitions.h
	/bin/rm -f libvsgpt/features.h
	/bin/rm -f libvsgpt/types.h
	/bin/rm -f Makefile

