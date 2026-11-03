CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2 -D_DEFAULT_SOURCE
LDFLAGS ?=
LDLIBS ?= -pthread

TARGET = sync_car
SOURCES = sync_car.c test_sync_car.c
HEADERS = sync_car.h

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o
