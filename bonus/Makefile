CXX = icc

MATRIX_A_ROWS ?= 1024
MATRIX_A_COLS ?= 2048
MATRIX_B_ROWS ?= 2048
MATRIX_B_COLS ?= 1024
BLOCK_SIZE    ?= 32
PARAM_DEFS    = -DMATRIX_A_ROWS=$(MATRIX_A_ROWS) -DMATRIX_A_COLS=$(MATRIX_A_COLS) \
                -DMATRIX_B_ROWS=$(MATRIX_B_ROWS) -DMATRIX_B_COLS=$(MATRIX_B_COLS) \
                -DBLOCK_SIZE=$(BLOCK_SIZE)

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

TARGET = build/main_$(MATRIX_A_ROWS)x$(MATRIX_A_COLS)_$(MATRIX_B_ROWS)x$(MATRIX_B_COLS)_$(BLOCK_SIZE)

all: $(TARGET)

$(TARGET): $(SRC) | build
	$(CXX) $^ -o $@ $(CXXFLAGS_MKL)

build:
	mkdir -p build

clean:
	rm -rf build
