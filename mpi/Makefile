MPICC:=mpiicc
CFLAGS:=-g -O0
BINS:=nullref deadlock ring

all: $(BINS)

nullref: nullref.c
	$(MPICC) $(CFLAGS) -o $@ $^ -Wno-int-conversion

deadlock: deadlock.c
	$(MPICC) $(CFLAGS) -o $@ $^

ring: ring.c
	$(MPICC) $(CFLAGS) -o $@ $^

clear:
	rm -rf $(BINS)
