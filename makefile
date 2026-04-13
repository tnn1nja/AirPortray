APPNAME = main

MAINSRC = src/main.cpp
MAINOBJ = build/main.o
TESTSRC = src/test.cpp
TESTOBJ = build/test.o

$(APPNAME): $(MAINOBJ) $(TESTOBJ)
	$(CXX) $(MAINOBJ) $(TESTOBJ) -o $(APPNAME)

$(MAINOBJ): $(MAINSRC)
	$(CXX) -c $(MAINSRC) -o $(MAINOBJ)

$(TESTOBJ): $(TESTSRC)
	$(CXX) -c $(TESTSRC) -o $(TESTOBJ)