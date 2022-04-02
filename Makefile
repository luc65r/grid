CC := cc
SCANNER := wayland-scanner
PREFIX := /usr/local

CFLAGS := -std=c99 -O2
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

install: all
	install -m 755 -D grid $(DESTDIR)$(PREFIX)/bin/grid

clean:
	rm -f *.o grid

.PHONY: all install clean
