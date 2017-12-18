CC = nvcc
CFLAGS = -g
SRCS = main.cpp sobel.cu
PROG = CountingCoin_CU

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV)

$(PROG):$(SRCS)
		$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
