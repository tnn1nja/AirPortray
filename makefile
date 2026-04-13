APPNAME = main

BUILDDIR = build
SRCDIR = src

MAINSRC = $(SRCDIR)/main.cpp
MAINOBJ = $(BUILDDIR)/main.o
TESTSRC = $(SRCDIR)/test.cpp
TESTOBJ = $(BUILDDIR)/test.o


$(APPNAME): build $(MAINOBJ) $(TESTOBJ)
	$(CXX) $(MAINOBJ) $(TESTOBJ) -o $(APPNAME)

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(MAINOBJ): $(MAINSRC)
	$(CXX) -c $(MAINSRC) -o $(MAINOBJ)

$(TESTOBJ): $(TESTSRC)
	$(CXX) -c $(TESTSRC) -o $(TESTOBJ)