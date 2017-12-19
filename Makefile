CC = nvcc
CFLAGS = -g
SRCS = main.cpp sobel.cu hough.cpp
PROG = CountingCoin_CU
PROG_LLVM = CountingCoin_CU_LLVM
# For GeForce GTX 660M
LLVM_FLAG= -L/usr/local/cuda-9.0/lib64 \
		   -lcudart_static -ldl -lrt -pthread


OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV)

all: $(PROG)

$(PROG):$(SRCS)
		$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

LLVM: $(PROG_LLVM)

$(PROG_LLVM): $(SRCS)
	clang++ -x cuda --cuda-gpu-arch=sm_30 -o $@ $^ $(LIBS) $(LLVM_FLAG) 

clean:
	rm -f $(PROG)
