APPNAME = AirPortray

BUILDDIR = build
SRCDIR = src

M_SRC = $(SRCDIR)/main.cpp
M_OBJ = $(BUILDDIR)/main.o
A_SRC = $(SRCDIR)/Airport.cpp
A_OBJ = $(BUILDDIR)/Airport.o
ADF_SRC = $(SRCDIR)/AirportDataFile.cpp
ADF_OBJ = $(BUILDDIR)/AirportDataFile.o
AR_SRC = $(SRCDIR)/AirportRepository.cpp
AR_OBJ = $(BUILDDIR)/AirportRepository.o
AP_SRC = $(SRCDIR)/AirPortray.cpp
AP_OBJ = $(BUILDDIR)/AirPortray.o


$(APPNAME): $(BUILDDIR) $(M_OBJ) $(A_OBJ) $(ADF_OBJ) $(AR_OBJ) $(AP_OBJ)
	$(CXX) $(M_OBJ) $(A_OBJ) $(ADF_OBJ) $(AR_OBJ) $(AP_OBJ) -o $(APPNAME)

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(M_OBJ): $(M_SRC)
	$(CXX) -c $(M_SRC) -o $(M_OBJ)

$(A_OBJ): $(A_SRC)
	$(CXX) -c $(A_SRC) -o $(A_OBJ)

$(ADF_OBJ): $(ADF_SRC)
	$(CXX) -c $(ADF_SRC) -o $(ADF_OBJ)

$(AR_OBJ): $(AR_SRC)
	$(CXX) -c $(AR_SRC) -o $(AR_OBJ)

$(AP_OBJ): $(AP_SRC)
	$(CXX) -c $(AP_SRC) -o $(AP_OBJ)


clean:
	rd /s /q $(BUILDDIR)
	del ${APPNAME}.exe