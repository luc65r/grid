CC := cc
SCANNER := wayland-scanner

CFLAGS := -std=c99 -Og -ggdb
CFLAGS += -Wall -Wextra -Wpedantic -Wconversion
LDFLAGS := -lwayland-client

OBJS := grid.o river-layout-v3.o
HGEN := river-layout-v3.h

all: grid

grid: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

grid.o: $(HGEN)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.c: %.xml
	$(SCANNER) private-code < $< > $@

%.h: %.xml
	$(SCANNER) client-header < $< > $@

clean:
	rm -f *.o grid

.PHONY: clean
