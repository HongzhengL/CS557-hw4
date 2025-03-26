CXX = icc

MATRIX_SIZE ?= 2048
BLOCK_SIZE  ?= 32
PARAM_DEFS  = -DMATRIX_SIZE=$(MATRIX_SIZE) -DBLOCK_SIZE=$(BLOCK_SIZE)

MKLROOT ?= $(shell echo $$MKLROOT)

MKL_LIBS = -Wl,--start-group \
           $(MKLROOT)/lib/intel64/libmkl_intel_lp64.a \
           $(MKLROOT)/lib/intel64/libmkl_core.a \
           $(MKLROOT)/lib/intel64/libmkl_intel_thread.a \
           -Wl,--end-group \
           -liomp5 -lpthread -lm -ldl

CXXFLAGS = -Wall -O2 -qopenmp $(PARAM_DEFS)
CXXFLAGS_MKL = $(CXXFLAGS) $(MKL_LIBS)

SRC = main.cpp MatMatMultiply.cpp Utilities.cpp
OBJ = $(SRC:%.cpp=build/%.o)

TARGET = build/main_$(MATRIX_SIZE)_$(BLOCK_SIZE)

all: $(TARGET)

build/%.o: %.cpp | build/obj
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(TARGET): $(OBJ) | build
	$(CXX) $^ -o $@ $(CXXFLAGS_MKL)

build:
	mkdir -p build

build/obj:
	mkdir -p build/obj

clean:
	rm -rf build

