CXX = icc

MKLROOT ?= $(shell echo $$MKLROOT)

MKL_LIBS = -Wl,--start-group \
           $(MKLROOT)/lib/intel64/libmkl_intel_lp64.a \
           $(MKLROOT)/lib/intel64/libmkl_core.a \
           $(MKLROOT)/lib/intel64/libmkl_intel_thread.a \
           -Wl,--end-group \
           -liomp5 -lpthread -lm -ldl

CXXFLAGS = -Wall -O2 -qopenmp
CXXFLAGS_MKL = $(CXXFLAGS) $(MKL_LIBS)

SRC = main.cpp  MatMatMultiply.cpp  Utilities.cpp

TARGET = main

all: $(TARGET)

$(TARGET):
	$(CXX) $(SRC) $(CXXFLAGS_MKL) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o

