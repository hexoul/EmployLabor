XENO_CONFIG := /usr/xenomai/bin/xeno-config
CFLAGS := $(shell $(XENO_CONFIG) --posix --alchemy --cflags)
LDFLAGS := $(shell $(XENO_CONFIG) --posix --alchemy --ldflags)
CC := $(shell $(XENO_CONFIG) --cc)

EXECUTABLE := preemption


all: $(EXECUTABLE)

%: %.c
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

